# Copyright 2013 Tetsuo Kiso. All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.

SRC := $(shell find . -name "*.tex")
PDFFILES := $(SRC:.tex=.pdf)

TEX = pdflatex
OPT = -interaction=nonstopmode

all: $(SRC)

clean:
	@rm -f *.aux *.log *.pdf

%.tex:
	$(TEX) $(OPT) $@
