[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/igor-krechetov/hsmcpp/blob/main/LICENSE)
[![Changelog](https://img.shields.io/badge/changelog-v1.0.2-green.svg)](https://github.com/igor-krechetov/hsmcpp/blob/main/CHANGELOG.md)
[![Documentation Status](https://readthedocs.org/projects/hsmcpp/badge/?version=latest)](https://hsmcpp.readthedocs.io/en/latest/?badge=latest)

# Releases
[![Latest Release](https://img.shields.io/github/v/tag/igor-krechetov/hsmcpp?label=latest%20release)](https://github.com/igor-krechetov/hsmcpp/tags)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/igor-krechetov/library/hsmcpp.svg)](https://registry.platformio.org/libraries/igor-krechetov/hsmcpp)
[![arduino-library-badge](https://www.ardu-badge.com/badge/hsmcpp.svg?)](https://www.ardu-badge.com/hsmcpp)


# Quality Status

[![Build Status](https://github.com/igor-krechetov/hsmcpp/actions/workflows/build.yml/badge.svg)](https://github.com/igor-krechetov/hsmcpp/actions/workflows/build.yml)

## Static Code Analysis

[![SCA: MISRA](https://github.com/igor-krechetov/hsmcpp/actions/workflows/sca_misra.yml/badge.svg)](https://github.com/igor-krechetov/hsmcpp/actions/workflows/sca_misra.yml)
[![SCA: CodeQL](https://github.com/igor-krechetov/hsmcpp/actions/workflows/sca_codeql.yml/badge.svg)](https://github.com/igor-krechetov/hsmcpp/actions/workflows/sca_codeql.yml)
[![SCA: Coverity](https://img.shields.io/coverity/scan/27361.svg)](https://scan.coverity.com/projects/igor-krechetov-hsmcpp)

## Unit Tests

[![Coverage Status](https://coveralls.io/repos/github/igor-krechetov/hsmcpp/badge.svg?branch=main)](https://coveralls.io/github/igor-krechetov/hsmcpp?branch=main)

[![Tests: STD](https://raw.githubusercontent.com/igor-krechetov/hsmcpp/build_artifacts/tests_result_std.svg)](https://github.com/igor-krechetov/hsmcpp/blob/build_artifacts/tests_result_std.log)
[![Tests: Glib](https://raw.githubusercontent.com/igor-krechetov/hsmcpp/build_artifacts/tests_result_glib.svg)](https://github.com/igor-krechetov/hsmcpp/blob/build_artifacts/tests_result_glib.log)
[![Tests: GLibmm](https://raw.githubusercontent.com/igor-krechetov/hsmcpp/build_artifacts/tests_result_glibmm.svg)](https://github.com/igor-krechetov/hsmcpp/blob/build_artifacts/tests_result_glibmm.log)
[![Tests: Qt](https://raw.githubusercontent.com/igor-krechetov/hsmcpp/build_artifacts/tests_result_qt.svg)](https://github.com/igor-krechetov/hsmcpp/blob/build_artifacts/tests_result_qt.log)


# Overview
HSMCPP is a C++ library providing implementation of state machine design pattern (also known as statecharts). It allows you to easily add hierarchical (HSM) or finite state machine (FSM) to your project. The main motivation behind creating it was the lack of suitable non-commercial alternatives which do not require the usage of large frameworks. And even existing commercial solutions couldn't satisfy all project needs that I usually have to deal with. This is in no way a "silver bullet" library, but it might be useful for you when dealing with RTOS systems, multi-threading or event-driven applications.

It's also applicable for single-threaded and synchronous applications, but it might not be the most efficient option.

If you are not familiar with HSM/FSM design concept and which problems it helps you solve, I recommend reading:
- [Welcome to the world of Statecharts](https://statecharts.dev)
- [Introduction to Hierarchical State Machines](https://barrgroup.com/embedded-systems/how-to/introduction-hierarchical-state-machines)
- [Hierarchical Finite State Machine for AI Acting Engine](https://towardsdatascience.com/hierarchical-finite-state-machine-for-ai-acting-engine-9b24efc66f2)

And if you just want to know if state machines are for you or not, here is a quick list (taken from [statecharts.dev](https://statecharts.dev))

## Why should you use Statecharts?

Statecharts offer a surprising array of benefits

- It's [easier to understand a statechart](https://statecharts.dev/benefit-easy-to-understand.html) than many other forms of code.
- The [behaviour is decoupled](https://statecharts.dev/benefit-decoupled-behaviour-component.html) from the component in question.
  - This makes it [easier to make changes to the behaviour](https://statecharts.dev/benefit-make-changes-to-the-behaviour.html).
  - It also makes it [easier to reason about the code](https://statecharts.dev/benefit-reason-about-code.html).
  - And the behaviour can be [tested independently](https://statecharts.dev/benefit-testable-behaviour.html) of the component.
- The process of building a statechart causes [all the states to be explored](https://statecharts.dev/benefit-all-states-explored.html).
- Studies have shown that statechart based code has [lower bug counts](https://statecharts.dev/benefit-low-bug-count.html) than traditional code.
- Statecharts lends itself to dealing with [exceptional situations](https://statecharts.dev/benefit-handle-anomalies.html) that might otherwise be overlooked.
- As complexity grows, statecharts [scale well](https://statecharts.dev/benefit-scales-with-complexity.html).
- A statechart is a great communicator: Non-developers can [understand the statecharts](https://statecharts.dev/benefit-non-developers-understanding.html), while QA can [use a statecharts as an exploratory tool](https://statecharts.dev/benefit-qa-exploration-tool.html).

It's worth noting that you're [already coding state machines](https://statecharts.dev/benefit-explicit.html), except that they're hidden in the code.

## Why should you not use statecharts?

There are a few downsides to using statecharts that you should be aware of.

- Programmers typically [need to learn something new](https://statecharts.dev/drawback-learn-new-technique.html), although the underpinnings (state machines) would be something that most programmers are familiar with.
- [It's usually a very foreign way of coding](https://statecharts.dev/drawback-foreign-paradigm.html), so teams might experience pushback based on how very different it is.
- There is an overhead to extracting the behaviour in that the [number of lines of code might increase](https://statecharts.dev/drawback-lines-of-code.html) with smaller statecharts.

## Why are they not used?

- [People don't know about them, and YAGNI](https://statecharts.dev/faq/why-statecharts-are-not-used.html).

## What are the main arguments against statecharts?

There are a few common arguments against statecharts in addition to the ones listed above:

- It's [simply not needed](https://statecharts.dev/faq/an-event-always-has-one-action.html).
- It [goes against the grain](https://statecharts.dev/faq/goes-against-grain.html) of _\[insert name of technology]_.
- It [increases the number of libraries](https://statecharts.dev/faq/increases-number-of-libraries.html), for web applications this means increased load time.

The benefits outlined above should make it clear that the introduction of statecharts is generally a _net positive_.


# Key Features
## Generic
- visual state machine editors (through [thirdparty editors](https://hsmcpp.readthedocs.io/en/latest/code-generation/editors/editors.html))
- [code generation](https://hsmcpp.readthedocs.io/en/latest/code-generation/code-generation.html) based on [W3C SCXML format](https://www.w3.org/TR/scxml/)
- PlantUML diagrams generation (from SCXML files)
- asynchronous / synchronous execution
- thread safety
- supported platforms:
  - POSIX compliant systems
  - Windows
  - Arduino
  - FreeRTOS
- [configurable event dispatchers](https://hsmcpp.readthedocs.io/en/latest/platforms/platforms.html#built-in-dispatchers):
  - std::thread based
  - glib based
  - glibmm based
  - Qt based
  - FreeRTOS based
  - Arduino based
  - possibility to [implement your own dispatcher](https://hsmcpp.readthedocs.io/en/latest/platforms/platforms.html#implementing-custom-dispatchers)
- [visual debugger](https://hsmcpp.readthedocs.io/en/latest/tools/hsmdebugger/hsmdebugger.html) to help analyze state machine behavior

## State machine related
- [states](https://hsmcpp.readthedocs.io/en/latest/features/states/states.html)
- [substates](https://hsmcpp.readthedocs.io/en/latest/features/substates/substates.html) (possible to define hierarchy)
- [transitions](https://hsmcpp.readthedocs.io/en/latest/features/transitions/transitions.html)
- [history](https://hsmcpp.readthedocs.io/en/latest/features/history/history.html)
- [timers](https://hsmcpp.readthedocs.io/en/latest/features/timers/timers.html)
- state and transition [callbacks](https://hsmcpp.readthedocs.io/en/latest/code-generation/scxml/scxml.html#callbacks-definition) (enter, exit, state changed, on transition)
- passing data to state and transition callbacks
- [parallel states](https://hsmcpp.readthedocs.io/en/latest/features/parallel/parallel.html)
- [final states](https://hsmcpp.readthedocs.io/en/latest/features/substates/substates.html#final-state)
- [conditional transitions](https://hsmcpp.readthedocs.io/en/latest/features/transitions/transitions.html#conditional-transitions)
- [conditional entry points](https://hsmcpp.readthedocs.io/en/latest/features/substates/substates.html#conditional-entry-points)
- [state actions](https://hsmcpp.readthedocs.io/en/latest/features/states/states.html#state-actions)
- [self transitions](https://hsmcpp.readthedocs.io/en/latest/features/transitions/transitions.html#self-transitions)
- transition cancelation
- support for std::function and lambdas as callbacks

# Documentation
Documentation is available [online](https://hsmcpp.readthedocs.io).

# HSM GUI Editors
Check out [documentation](https://hsmcpp.readthedocs.io/en/latest/code-generation/editors/editors.html) to learn more about available editors.

![Editing HSM in Qt Creator](https://hsmcpp.readthedocs.io/en/latest/_images/editor_qt.png)

![Editing HSM in scxmlgui](https://hsmcpp.readthedocs.io/en/latest/_images/editor_scxmlgui.png)


# hsmdebugger
[Read documentation](https://hsmcpp.readthedocs.io/en/latest/tools/hsmdebugger/hsmdebugger.html) for details on how to use debugger.

![hsmdebugger demo](https://hsmcpp.readthedocs.io/en/latest/_images/hsmdebugger_demo.gif)


# Installation
```bash
git clone https://github.com/igor-krechetov/hsmcpp.git
cd ./hsmcpp
./build.sh
cd ./build
make install
```
By default, it will build all included components, tests and examples. You can disable any of them using cmake build flags. For example you probably will not have glib or glibmm libraries available on Windows so you might want to exclude them.

See [detailed instructions in documentation](https://hsmcpp.readthedocs.io/en/latest/getting-started/getting-started.html#building-the-library).

# Dependencies
- For library:
  - C++11 or newer
  - glib (optional, for dispatcher)
  - glibmm (optional, for dispatcher)
  - Qt (optional, for dispatcher)
- For build:
  - cmake 3.16+
  - Visual Studio 2015+ (for Windows build)
- For code generator:
  - Python 3
- For hsmdebugger:
  - Python 3
  - PyYaml (pip3 install PyYaml)
  - PySide6 (pip3 install PySide6)
  - plantuml (minimal version: V1.2020.11)

# Creating a simple State Machine
HSM structure:

![Hello Wolrd HSM](https://hsmcpp.readthedocs.io/en/latest/_static/images/00_helloworld.png)

Implementation using HsmEventDispatcherSTD:
```C++
#include <chrono>
#include <thread>
#include <hsmcpp/hsm.hpp>
#include <hsmcpp/HsmEventDispatcherSTD.hpp>

enum class States
{
    OFF,
    ON
};

enum class Events
{
    SWITCH
};

int main(const int argc, const char**argv)
{
    std::shared_ptr<hsmcpp::HsmEventDispatcherSTD> dispatcher = hsmcpp::HsmEventDispatcherSTD::create();
    hsmcpp::HierarchicalStateMachine<States, Events> hsm(States::OFF);

    hsm.initialize(dispatcher);

    hsm.registerState(States::OFF, [&hsm](const VariantList_t& args)
    {
        printf("Off\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        hsm.transition(Events::SWITCH);
    });
    hsm.registerState(States::ON, [&hsm](const VariantList_t& args)
    {
        printf("On\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        hsm.transition(Events::SWITCH);
    });

    hsm.registerTransition(States::OFF, States::ON, Events::SWITCH);
    hsm.registerTransition(States::ON, States::OFF, Events::SWITCH);

    hsm.transition(Events::SWITCH);

    dispatcher->join();

    return 0;
}
```

See [/examples/07_build](https://github.com/igor-krechetov/hsmcpp/tree/main/examples/07_build) for CMake configuration examples.

For other examples see [Getting Started guide](https://hsmcpp.readthedocs.io/en/latest/getting-started/getting-started.html#) or [/examples](https://github.com/igor-krechetov/hsmcpp/tree/main/examples).


## Notable FSM/HSM libraries
There is no one-for-all library, so if hsmcpp doesn't fully suit your needs you can check out one of these alternatives:
- [Qt](https://github.com/qt/qtscxml) (using QStateMachine or QScxmlStateMachine)
- [QP/C++](https://github.com/QuantumLeaps/qpcpp)
- [TinyFSM](https://github.com/digint/tinyfsm)
- [Another Finite State Machine](https://github.com/zmij/afsm)
- [HFSM2](https://github.com/andrew-gresyk/HFSM2)
- [arduino-fsm](https://github.com/jonblack/arduino-fsm)