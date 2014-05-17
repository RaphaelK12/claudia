# claudia

Clang Universal Diagnostics Parser

Claudia parses Clang's -Weverything diagnostics and tries her best to polish the reults.


## Getting started

Required:
* recent clang (tested with 3.4) and libc++ (primarily for regex support)
* recent gcc/libstdc++ setups may work, too.

Build claudia using the ninja build system:

    ninja

If you don't have ninja, you may build claudia using:

    clang++ -stdlib=libc++ -std=c++11 src/*.cc -o claudia


## Usage

In your project environment set your compiler flags:

    -Weverything -fdiagnostics-show-category=name -fno-diagnostics-fixit-info

Or adapt the diagnostics pattern in config.h accordingly, but be sure to match regex groups to the parser's match extraction in parser.cc.

See: http://llvm.org/releases/3.4/tools/clang/docs/UsersManual.html#formatting-of-diagnostics

Create a file containing your project's diagnostics:

    make 2> diagnostics.txt

Let claudia parse them:

    claudia diagnostics.txt



## License

Copyright (C) 2014 Daniel J. H.

Distributed under the MIT License.
