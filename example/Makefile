SRC := $(shell find . -name "*.tex")
PDFFILES := $(SRC:.tex=.pdf)

TEX = pdflatex
OPT = -interaction=nonstopmode

all: $(SRC)

clean:
	@rm -f *.aux *.log *.pdf

%.tex:
	$(TEX) $(OPT) $@
