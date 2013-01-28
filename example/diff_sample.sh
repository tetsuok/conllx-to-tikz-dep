#!/bin/bash
../conllx_to_tikz_dep.py --diff example.conll predict.conll | pdflatex
