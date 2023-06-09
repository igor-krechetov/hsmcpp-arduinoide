// Copyright (C) 2023 Igor Krechetov
// Distributed under MIT license. See file LICENSE for details

#include "HsmImplTypes.hpp"

#include "hsmcpp/logging.hpp"

namespace hsmcpp {

// ============================================================================
// StateCallbacks
// ============================================================================
StateCallbacks::StateCallbacks(HsmStateChangedCallback_t&& cbStateChanged,
                               HsmStateEnterCallback_t&& cbEntering,
                               HsmStateExitCallback_t&& cbExiting)
    : onStateChanged(std::move(cbStateChanged))
    , onEntering(std::move(cbEntering))
    , onExiting(std::move(cbExiting)) {}

StateCallbacks::StateCallbacks(StateCallbacks&& src) noexcept {
    *this = std::move(src);
}

StateCallbacks& StateCallbacks::operator=(StateCallbacks&& src) noexcept {
    if (this != &src) {
        onStateChanged = std::move(src.onStateChanged);
        onEntering = std::move(src.onEntering);
        onExiting = std::move(src.onExiting);
    }

    return *this;
}

// ============================================================================
// TransitionInfo
// ============================================================================
TransitionInfo::TransitionInfo(const StateID_t from,
                               const StateID_t to,
                               const TransitionType type,
                               HsmTransitionCallback_t cbTransition,
                               HsmTransitionConditionCallback_t cbCondition)
    : fromState(from)
    , destinationState(to)
    , transitionType(type)
    , onTransition(std::move(cbTransition))
    , checkCondition(std::move(cbCondition)) {}

TransitionInfo::TransitionInfo(const StateID_t from,
                               const StateID_t to,
                               const TransitionType type,
                               HsmTransitionCallback_t cbTransition,
                               HsmTransitionConditionCallback_t cbCondition,
                               const bool conditionValue)
    : fromState(from)
    , destinationState(to)
    , transitionType(type)
    , onTransition(std::move(cbTransition))
    , checkCondition(std::move(cbCondition))
    , expectedConditionValue(conditionValue) {}

// ============================================================================
// HistoryInfo
// ============================================================================
HistoryInfo::HistoryInfo(const HistoryType newType,
                         const StateID_t newDefaultTarget,
                         HsmTransitionCallback_t newTransitionCallback)
    : type(newType)
    , defaultTarget(newDefaultTarget)
    , defaultTargetTransitionCallback(std::move(newTransitionCallback)) {}

HistoryInfo::HistoryInfo(HistoryInfo&& src) noexcept {
    *this = std::move(src);
}

HistoryInfo& HistoryInfo::operator=(HistoryInfo&& src) noexcept {
    if (this != &src) {
        type = src.type;
        defaultTarget = src.defaultTarget;
        defaultTargetTransitionCallback = std::move(src.defaultTargetTransitionCallback);
        previousActiveStates = std::move(src.previousActiveStates);

        src.type = HistoryType::SHALLOW;
        src.defaultTarget = INVALID_HSM_STATE_ID;
    }

    return *this;
}

// ============================================================================
// PendingEventInfo
// ============================================================================
constexpr const char* HSM_TRACE_CLASS = "PendingEventInfo";

PendingEventInfo::PendingEventInfo(PendingEventInfo&& src) noexcept {
    *this = std::move(src);
}

PendingEventInfo::~PendingEventInfo() {
    if (true == cvLock.unique()) {
        HSM_TRACE_CALL_DEBUG_ARGS("event=<%d> was deleted. releasing lock", SC2INT(id));
        unlock(HsmEventStatus::DONE_FAILED);
        cvLock.reset();
        syncProcessed.reset();
    }
}

PendingEventInfo& PendingEventInfo::operator=(PendingEventInfo&& src) noexcept {
    if (this != &src) {
        transitionType = src.transitionType;
        id = src.id;
        args = std::move(src.args);
        cvLock = std::move(src.cvLock);
        syncProcessed = std::move(src.syncProcessed);
        transitionStatus = std::move(src.transitionStatus);
        forcedTransitionsInfo = std::move(src.forcedTransitionsInfo);
        ignoreEntryPoints = src.ignoreEntryPoints;

        src.id = INVALID_HSM_EVENT_ID;
    }

    return *this;
}

void PendingEventInfo::initLock() {
    if (!cvLock) {
        cvLock = std::make_shared<Mutex>();
        syncProcessed = std::make_shared<ConditionVariable>();
        transitionStatus = std::make_shared<HsmEventStatus>();
        *transitionStatus = HsmEventStatus::PENDING;
    }
}

void PendingEventInfo::releaseLock() {
    if (true == isSync()) {
        HSM_TRACE_CALL_DEBUG_ARGS("releaseLock");
        unlock(HsmEventStatus::DONE_FAILED);
        cvLock.reset();
        syncProcessed.reset();
    }
}

bool PendingEventInfo::isSync() const {
    return (nullptr != cvLock);
}

void PendingEventInfo::wait(const int timeoutMs) {
    if (true == isSync()) {
        // NOTE: lock is needed only because we have to use cond variable
        UniqueLock lck(*cvLock);

        HSM_TRACE_CALL_DEBUG_ARGS("trying to wait... (current status=%d, %p)",
                                  SC2INT(*transitionStatus),
                                  transitionStatus.get());
        if (timeoutMs > 0) {
            // NOTE: false-positive. "return" statement belongs to lambda function, not parent function
            // cppcheck-suppress [misra-c2012-15.5, misra-c2012-17.7]
            syncProcessed->wait_for(lck, timeoutMs, [=]() { return (HsmEventStatus::PENDING != *transitionStatus); });
        } else {
            // NOTE: false-positive. "return" statement belongs to lambda function, not parent function
            // cppcheck-suppress [misra-c2012-15.5, misra-c2012-17.7]
            syncProcessed->wait(lck, [=]() { return (HsmEventStatus::PENDING != *transitionStatus); });
        }

        HSM_TRACE_DEBUG("unlocked! transitionStatus=%d", SC2INT(*transitionStatus));
    }
}

void PendingEventInfo::unlock(const HsmEventStatus status) {
    HSM_TRACE_CALL_DEBUG_ARGS("try to unlock with status=%d", SC2INT(status));

    if (true == isSync()) {
        HSM_TRACE_DEBUG("SYNC object (%p)", transitionStatus.get());
        *transitionStatus = status;

        if (status != HsmEventStatus::PENDING) {
            syncProcessed->notify();
        }
    } else {
        HSM_TRACE_DEBUG("ASYNC object");
    }
}

const VariantVector_t& PendingEventInfo::getArgs() const {
    static VariantVector_t empty;
    return (args ? *args : empty);
}

}  // namespace hsmcpp