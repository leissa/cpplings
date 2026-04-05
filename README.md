# cpplings

```
                                     _/  _/
        _/_/_/  _/_/_/    _/_/_/    _/      _/_/_/      _/_/_/    _/_/_/
     _/        _/    _/  _/    _/  _/  _/  _/    _/  _/    _/  _/_/
    _/        _/    _/  _/    _/  _/  _/  _/    _/  _/    _/      _/_/
     _/_/_/  _/_/_/    _/_/_/    _/  _/  _/    _/    _/_/_/  _/_/_/
            _/        _/                                _/
           _/        _/                            _/_/
```

[![Standard](https://img.shields.io/badge/c%2B%2B-23-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![download](https://img.shields.io/badge/download%20%20-link-blue.svg)](https://raw.githubusercontent.com/leissa/cpplings/refs/heads/master/tools/install.sh)

[Rustlings](https://rustlings.rust-lang.org/)-style exercises for C++ using:
* [CMake](https://cmake.org/)
* [doctest](https://github.com/doctest/doctest)
* Sanitizers by default:
    * [Address Sanitizer](https://clang.llvm.org/docs/AddressSanitizer.html)
    * [Leak Sanitizer](https://clang.llvm.org/docs/LeakSanitizer.html)
    * [Undefined Behavior Sanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html)

## Install

```sh
curl -fsSL https://raw.githubusercontent.com/leissa/cpplings/refs/heads/master/tools/install.sh | bash
```

## Start

```sh
cd cpplings
./cpplings
```

## Usage

```
usage: cpplings [-h] {list,run,verify,watch,watch-all} ...

positional arguments:
  {list,run,verify,watch,watch-all}
    list                List available exercises
    run                 Run a specific exercise
    verify              Verify all exercises
    watch               Watch a specific exercise
    watch-all           Watch all exercises (default)

options:
  -h, --help            show this help message and exit
```
