conllx-to-tikz-dep
==================

<img src="https://github.com/downloads/tetsuok/conllx-to-tikz-dep/image.jpg"
 alt="image" title="image" align="right"  width="500" height="450" />

A simple CoNLL-X to tikz-dependency converter.

This converter aims to provide a function to visualize a simple
dependency tree through converting from the CoNLL-X data format to the tikz-dependency.

Currently, I have implemented the converter in Python, C/C++ and
[Go](http://golang.org/).  The functionality of these implementations
is mostly same except that the C/C++ implementation does not provide
command line options.  The code is known to work on Linux and OS X.

### Software Requirements ###

Requirements depend on the type of implementations what you want to use:

- Go compilers if you want to use go code.
- C compiler if you want to use C compiled program.
- C/C++ compiler if you want to use C++ compiled program.
- Python if you want to run the python script.

Please note that [tikz-dependency](http://sourceforge.net/projects/tikz-dependency/) package is required when you want to
compile generated latex files with this converter.

## Usage ##

We will describe the usage for each implementation in the following sections.
Please see `-h` or `--help` for all possible options.
Again, note that the options is not available for the C/C++ implementation.

### Python ###

The python code just works. There are no need to install the code or additional packages.

    $ ./conllx_to_tikz_dep.py conllx_data [options]

#### Draw dependencies with edge labels ####

With the option `--with-label`, you can draw dependency trees with edge labels.

    $ ./conllx_to_tikz_dep.py conllx_data --with-label

They look like this:

![sample output](https://raw.github.com/tetsuok/conllx-to-tikz-dep/master/example/labeled_sample.png "Sample output")

#### Reversing of edge direction ####

By default, the direction of dependency edge is from a head word to its modifier.
With the option `--reverse-edge`, the direction of edges can be reversed.

    $ ./conllx_to_tikz_dep.py conllx_data --reverse-edge

### Diff mode [python code only] ###

You can compare predicted parse trees by your parser to gold parse
trees annotated by humans.

    $ ./conllx_to_tikz_dep.py --reverse-edge --diff gold_data predict_data

### C/C++ ###

    $ cd c
    $ make

To run C program

    $ ./conllx_to_tikz_dep conllx_data

To run C++ program

    $ ./conllx_to_tikz_dep_pp conllx_data

### Go ###

    $ go build conllx_to_tikz_dep.go
    $ ./conllx_to_tikz_dep conllx_data

or

    $ go run conllx_to_tikz_dep.go conllx_data

## Data format ##

For the details of the input data format, see the website:
[CoNLL-X Shared Task: Multi-lingual Dependency Parsing](http://ilk.uvt.nl/conll/#dataformat)

## License ##

This code is distributed under the New BSD License. See the file LICENSE.
