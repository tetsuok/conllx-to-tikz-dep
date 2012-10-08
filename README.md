conllx-to-tikz-dep
==================

<img src="https://github.com/downloads/tetsuok/conllx-to-tikz-dep/image.jpg"
 alt="image" title="image" align="right"  width="600" height="550" />

A simple CoNLL-X to tikz-dependency converter.

This converter aims to provide a function to visualize a simple
dependency tree through converting from the CoNLL-X data format to the tikz-dependency.

Currently, I have implemented the converter in Python, C and
[Go](http://golang.org/).  The functionality of these implementations
is mostly same except that the C implementation does not provide
command line options.  The code is known to work on Linux and OS X.

## Software Requirements ##

Requirements depend on the type of implementations what you want to use:

- Go compilers if you want to use go code.
- C compiler if you want to use C code.
- Python if you want to run the python script.

Please note that [tikz-dependency](http://sourceforge.net/projects/tikz-dependency/) package is required when you want to
compile generated latex files with this converter.

## Usage ##

We will describe the usage for each implementation in the following sections.
Please see `-h` or `--help` for all possible options.
Again, note that the options is not available for the C implementation.

### Python ###

The python code just works. There are no need to install the code or additional packages.

    $ ./conllx_to_tikz_dep.py conllx_data [options]

### C ###

    $ cd c
    $ make
    $ ./conllx_to_tikz_dep conllx_data

### Go ###

    $ go build
    $ ./conllx_to_tikz_dep conllx_data

or

    $ go run conllx_to_tikz_dep.go conllx_data

## Data format ##

For the details of the input data format, see the website:
[CoNLL-X Shared Task: Multi-lingual Dependency Parsing](http://ilk.uvt.nl/conll/#dataformat)
