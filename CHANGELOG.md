# Changelog
All notable changes to project will be documented in this file.

## [1.0.2] - 2024-05-31
### Fixed
- fixed handling of <xi:include> tags during code generation (transition targets were getting double prefix which was breaking the build)

## [1.0.1] - 2024-01-11
### Fixed
- STD dispatcher incorrectly schedules repeating timer event (https://github.com/igor-krechetov/hsmcpp/pull/8)
- Race condition when starting timers with Qt Dispatcher (used invalid context for lambda function)
- Add libc version check for test_memory_footprint test application

## [1.0.0] - 2023-05-25
### Updated
- add activeStates argument to failedTransition callback
- optimize HSM::impl::isSubstateOf()

### Fixed
- overriding HSM and dispatcher callbacks didn't work
- made logHsmAction() thread-safe

## [0.38.0] - 2023-05-18
### Updated
- added new constructors for Variant class (initialization from vector, list and map)
- signifficantly improved performance of Variant container by removing unnecesary memory copy/reallocations

### Fixed
- debug traces were not fully disabled by default

## [0.37.0] - 2023-05-12
### Added
- HierarchicalStateMachine::dispatcher() method
- support for enqued actions in dispatcher (see IHsmEventDispatcher::enqueueAction())

### Fixed
- deleting HSM instance while it still had pending events sometimes cased crash

## [0.36.0] - 2023-05-03
### Updated
- Fixed clang-tidy warnings
- Reduced complexity of some large methods in HsmImpl
- Moved private enums and structs from HsmImpl to a separate file
- Moved HistoryType, TransitionType, StateActionTrigger, StateAction enums from HierarchicalStateMachine class to HsmTypes.hpp (breaks interface)
- update Coverity tools to 2022.12.2

## [0.35.0] - 2023-04-26
### Added
- Support for custom types in Variant container
- New Variant::clear() method
- New Variant::isEmpty() method
- Implemented bool,string to number conversion in toInt64(), toUInt64(), toDouble()
- Implemented string to bool conversion in toBool()
- Implemented vector,list to bytearray conversion in toByteArray()
- New Variant's methods getByteArray(), getVector(), getList(), getMap(), getPair() for type-safe fast access to internal data

### Updated
- scxml2gen now generates timers if it finds events with "ON_TIMER_" prefix (before it generated timers only if they were used in state actions)
- Removed unsafe memory management in Variant class
- Variant's toByteArray(), toVector(), toList(), toMap(), toPair() methods replaced with type-safe versions
- Removed unsafe Variant::value() method
- Refactoring and coverage increase of unit tests for Variant class.
- VariantDict_t renamed to VariantMap_t
- Variant::Type::DICTIONARY renamed to Variant::Type::MAP
- Varaint::make() and constructor for PAIR type replaced with a template version

### Fixed
- Variant's logic for comparing double values
- Variant's logic for comparing numeric values of different types

## [0.34.0] - 2023-04-07
### Added
- added version.hpp with library version

### Updated
- improved behavior of Final States when working with Parallel states
- unit-tests refactoring (added BaseAsyncHsm class and removed AsyncHsm)
- improved async logic in unit-tests (multithreaded, parallel)

### Fixed
- Coverity issue in HierarchicalStateMachine::Impl::initialize (unhandled exception when calling shared_from_this(), but it was not possible due to Impl always being created as a shared pointer)
- rare dead-lock in HsmEventDispatcherSTD destructor
- wait_for() in std based ConditionVariable was not working correctly without stopWaiting callback

## [0.33.0] - 2023-03-23
### Added
- isTimerRunning API

### Fixed
- added thread safety for Dispatcher timer API

## [0.32.0] - 2023-03-22
### Fixed
- Deleting HSM before dispatcher was able to process all pending events resulted in a crash
- Deleting dispatcher resulted in undefined behavior

### Updated
- Enabled arduino-lint in CI
- HSM now does not take ownership of dispatcher instance

## [0.31.0] - 2023-03-16
### Added
- ArduinoIDE support

## [0.30.2] - 2023-03-15
### Updated
- scxml2gen: changed generated event, state, timer values from const to constexpr

### Fixed
- dispatcher timer APIs were not thread-safe


## [0.30.1] - 2023-03-14
### Added
- Variant::toPair() method
- Variant::isPair() method

### Fixed
- calling HsmEventDispatcherGLibmm::start() multiple times is now safe
- calling transition() or similar API before initialize() or after release() caused a crash

### Updated
- documentation for all public classes

## [0.30.0] - 2023-02-28
### Updated
- removed template from HierarchicalStateMachine and separated implementaion (BREAKS INTERFACE)
- state, event and timer enums were replaced with integer type (no extra work is needed if scxml generation is used)

## [0.29.1] - 2023-02-09
### Added
- Arudino examples

### Updated
- removed ArduinoLog dependency

### Fixed
- scxml2gen: generation of PlantUML diagrams was broken when state machine had conditional entry transition without event
- fixed FreeRTOS build

## [0.29.0] - 2023-02-03
### Added
- timers support for std, glib dispatchers
- interrupts safety for Arduino dispatcher

### Fixed
- std dispatcher didn't wake up when events were emited from interrupts

### Updated
- CriticalSection was renamed into InterruptsFreeSection
- added a new CriticalSection class

## [0.28.2] - 2023-02-02
### Fixed
- applied clang format to all code
- scxml2gen: fixed MISRA warnings in template code

## [0.28.1] - 2023-02-02
### Fixed
- scxml2gen: changed template to reduce stack consumption during HSM initialization on Arduino

## [0.28.0] - 2023-02-01
### Added
- interrupts support for std, glib, glibmm and qt dispatchers

### Updated
- updated build logic based on HSMBUILD_PLATFORM. "windows" and "posix" values added

## [0.27.3] - 2023-01-26

### Fixed
- MISRA warnings
- lock issue in async tests (01-30)

## [0.27.2] - 2023-01-25

### Fixed
- onEntry and onState callbacks of initial HSM state are not called

## [0.27.1] - 2023-01-22
### Added
- scxml2gen: new generate_code and generate_diagram API for usage from Python scripts

### Updated
- change getStateName, getEventName to be const

### Fixed
- scxml2gen: generation of entry transitions with condition but without an event

### Build
- CI scripts and github actions
- PlatformIO build integration

## [0.27.0] - 2023-01-20
### Added
- Arduino support
- upgraded gtest to 1.13.0
- unit tests description (states)

### Fixed
- scxml2gen: generation of self-transitions

## [0.26.0] - 2023-01-02
### Added
- support for internal/external self-transitions

## [0.25.0] - 2022-12-28

### Fixed
- improved handling of parent states:
  - parent states are now kept active when activating substates
  - parent state's enter/exit callbacks are called correctly during transitions
- hsmdebugger was not generating diagrams after update to scxml2gen api

## [0.24.6] - 2022-09-27
### Added
- support for final states in scxml2gen

## [0.24.5] - 2022-08-16

### Fixed
- install missing os headers after build

## [0.24.4] - 2022-07-03
### Added
- timers support for Qt dispatcher

## [0.24.3] - 2022-07-02
### Added
- support for Qt6

## [0.24.2] - 2022-06-12

### Fixed
- bool type support in hsmcpp::variant (for compilers where bool is treated as int)

## [0.24.1] - 2022-06-07

### Fixed
- build fix for hsm timers in FreeRTOS

## [0.24.0] - 2022-06-07
### Added
- FreeRTOS support
- abstraction layer for platform specific features (threading)
- support for transitions from signals/interrupts (FreeRTOS)
- unit tests bringup for FreeRTOS

### Fixed
- hsm initialization
- fixed dispatcher test for Qt platform

## [0.23.0] - 2022-05-24
### Added
- new API to interact with timers (start, stop, restart)

## [0.22.0] - 2022-02-25
### Added
- support for final states & exit points (library only)

## [0.21.2] - 2022-01-24
### Added
- scxml2gen is now correctly installed after build
- improved cmake and pkg-config usability
- added better CMake script examples

### Fixed
- fixed support for C++11

## [0.21.1] - 2021-11-10

### Fixed
- incorrect code generation from scxml

## [0.21.0] - 2021-11-04
### Added
- support for condition callbacks in entry transitions

### Fixed
- scxml2gen: multiple conditional entry transitions were not handled correctly

## [0.20.0] - 2021-09-30
### Added
- new state action: transition. It makes possible go initiate HSM transitions from within HSM.

## [0.19.2] - 2021-09-09
### Added
- new Variant constructors
- Variant unit-tests (basic)

## [0.19.1] - 2021-09-01

### Fixed
- recursive lock in GLib base dispatcher

## [0.19.0] - 2021-08-30
### Added
- support for vector and list types to Variant (VariantVector_t, VariantList_t)

### Fixed
- deadlock in GLib dispatcher
- fixed build with enabled traces

## [0.18.1] - 2021-08-20
### Added
- Variant::toMap()
- Variant::isMap()

### Updated
- improved dispatcher emit logic when used with multiple HSM instances

### Fixed
- fixed 05_timers_generated example

## [0.18.0] - 2021-08-19
### Added
- added posibility to set expected condition value for transitions

### Updated
- improved internal HSM traces

## [0.17.1] - 2021-08-19
### Added
- Variant::make to convert std::map to VariantMap_t

### Updated
- improve VariantMap_t to accept Variant as a key

## [0.17.0] - 2021-08-18
### Added
- callback for notifications about failed transitions

## [0.16.0] - 2021-08-13
### Added
- timers support to hsmcpp
- timers support in GLibmm dispatcher
- scxml2gen: support of timers
- scxml2gen: improve state description format when generating plantuml diagram
- hsmdebugger: support of timers

## [0.15.0] - 2021-08-06

### Fixed
- added namespace for hsmcpp

## [0.14.4] - 2021-08-04
### Added
- BYTEARRAY type to Variant

### Fixed
- fix build issue related with no default constructor for TransitionInfo

## [0.14.3] - 2021-08-03

### Fixed
- fix build warnings
- renamed trace macroses to avoid potential name conflicts

## [0.14.1] - 2021-06-13

### Updated
- memory footprint test
- add new template to use hsmcpp directly from GitHub
- diagrams for wiki (history)

### Fixed
- fix build script to explicitly use python 3
- fix variables export

## [0.14.1] - 2021-06-05
### Added
- support for history states in scxml2gen
- example for history usage
- generateHsmDiagram() CMake function

### Fixed
- hsmdebugger: selecting jar file for plantuml wasn't working on Ubuntu

## [0.14.0] - 2021-05-31
### Added
- support for history states (not supported in generator yet)

### Fixed
- handle scenario when initial state of HSM has substates (from now on initialize() API must be called after defining HSM structure)

## [0.13.4] - 2021-05-24
### Added
- HSMBUILD_DEBUGGING build option
- diagrams for wiki

## [0.13.3] - 2021-05-17

### Fixed
- crash in hsmdebugger while quickly switching frames

## [0.13.2] - 2021-05-16
### Added
- support for Windows build
- simple build scripts

### Fixed
- scxml2gen: added support of Python 3 versions before 3.8 (due to a bug in XML parser)

## [0.13.1] - 2021-05-03
### Added
- hsmdebugger: app icon
- hsmdebugger: setting to set plantuml path
- hsmdebugger: startup scripts for Windows and Linux

### Fixed
- hsmdebugger: Windows support

## [0.13.0] - 2021-04-30
### Added
- hsmdebugger: search frames feature
- hsmdebugger: settings
- hsmdebugger: caching of generated images

### Fixed
- crash caused by mistake in enableHsmDebugging()

## [0.12.1] - 2021-04-25
### Added
- add configurable hsm dump path
- scxml2gen: add support to blocks generation
- scxml2gen: update template
- scxml2gen: add generation of getStateName(), getEventName() functions
- hsmdebugger: add recent files
- examples: simplify 03_debugging

## [0.12.0] - 2021-04-19
### Added
- initial version of hsmdebugger

## [0.11.0] - 2021-04-14
### Added
- support for parallel states and transitions
- scxml2gen: support for parallel states and transitions

## [0.10.0] - 2021-04-04
### Added
- support for conditional entrypoints in states
## [0.9.0] - 2021-03-30
### Added
- scxml2gen: support for include of external files

## [0.8.0] - 2021-03-27
### Added
- scxml2gen: PlantUML state diagrams generator (from SCXML)
- scxml2gen: support for uppercase generator variables in templates

## [0.7.0] - 2021-03-26
### Added
- SCXML based code generator
- CMake function to use code generation from CMakeLists
- Example of generator usage (02_generated)

## [0.6.0] - 2021-03-23
### Added
- Qt based event dispatcher
- Qt based example

### Updated
- improve log macroses
- rename emit() -> emitEvent() in IHsmEventDispatcher (due to name collision with Qt)

## [0.5.1] - 2021-03-23
### Added
- cmake templates showing how to include hsmcpp in a project
- new examples
- HsmEventDispatcherSTD::join()
- HsmEventDispatcherSTD::stop()

### Updated
- improved build configuration
- rename build options: HSMBUILD_VERBOSE, HSMBUILD_STRUCTURE_VALIDATION, HSMBUILD_THREAD_SAFETY, HSMBUILD_DISPATCHER_GLIB, HSMBUILD_DISPATCHER_GLIBMM, HSMBUILD_DISPATCHER_STD, HSMBUILD_TESTS, HSMBUILD_EXAMPLES
- dispatchers are now compiled into separate modules (with own pkg-config files)
- examples and tests are compiled based on enabled dispatchers
- move pkg-config templates to a subfolder (/pkgconfig)

## [0.5.0] - 2021-03-17
### Added
- glib based event dispatcher

### Updated
- reduce output from gtests
- improve gtest CMakeLists

### Fixed
- improve thread safety in all available dispatchers
- assigning same Variant object to itself
- move dispatchers creation to main thread in gtests

### Build
- new CMake build option: DISPATCHER_GLIBMM
## [0.4.2] - 2021-03-10
### Added
- add timeout to sync transitions
- add transitionSync() API for convenience

### Updated
- remove HsmHandlerClass from HierarchicalStateMachine class template parameters
- rename HsmEventDispatcherGLib -> HsmEventDispatcherGLibmm

## [0.4.1] - 2021-03-08

### Updated
- thread safety for HSM

### Build
- New CMake build options: THREAD_SAFETY

## [0.4.0] - 2021-03-05
### Added
- std::thread based event dispatcher

### Updated
- Dispatchers should now be set using initialize() methond of HSM. If dispatcher is not running yet it will be automatically started.

### Fixed
- Fix a race-condition bug in AsyncHsm (unittests).

### Build
- New CMake build options: DISPATCHER_STD, BUILD_TESTS, BUILD_EXAMPLES
- Unittests are now compiled into two separate binaries: GLib and STD based.

## [0.3.0] - 2021-03-04
### Added
- Support for custom event dispatchers. Allows integration of HSM with any event dispatching mechanism used on the project.
- GLibmm event dispatcher

### Fixed
- Remov unnecessary event emit during transition

### Build
- CMake build options: VERBOSE, STRUCTURE_VALIDATION, DISPATCHER_GLIB

## [0.2.0] - 2021-03-02
### Added
- Support for substate entry points
- Conditional transitions
- Lambda functors can now be used as callbacks

## [0.1.0] - 2021-02-15
### Added

- Initial commit of HSMCPP. This version is usable, but requires some code cleanup.