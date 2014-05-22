# claudia

Clang Universal Diagnostics Parser

Claudia parses Clang's -Weverything diagnostics and tries her best to polish the reults.


## Getting started

Required:
* recent Clang compiler
* recent Boost libraries

Build claudia using the ninja build system:

    ninja

If you don't have ninja, you may build claudia using:

    clang++ -std=c++11 -O2 src/*.cc -lboost_program_options -lboost_regex -o claudia


## Usage

In your project environment set your compiler flags:

    -Weverything -fdiagnostics-show-category=name -fno-diagnostics-fixit-info

Or adapt the diagnostics pattern in config.h accordingly, but be sure to match regex groups to the parser's match extraction in parser.cc.

See: http://llvm.org/releases/3.4/tools/clang/docs/UsersManual.html#formatting-of-diagnostics

Create a file containing your project's diagnostics:

    make 2> diagnostics.txt

Let claudia parse them, e.g.:

    claudia -o out.json diagnostics.txt

See all options:

    claudia --help


## License

Copyright (C) 2014 Daniel J. H.

Distributed under the MIT License.
