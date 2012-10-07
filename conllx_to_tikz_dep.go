// Copyright 2012 Tetsuo Kiso. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"log"
	"os"
	"strconv"
	"strings"
)

const kInitSentLength = 256

var docOption = flag.String("doc-option", "standalone", "Option of the document class")
var depOption = flag.String("dep-option", "theme = simple", "Option for the dependency environment")
var depTxtOption = flag.String("deptxt-option", "column sep=1em", "Option for the deptext environment")

type Token struct {
	Id      int
	Form    string
	Lemma   string
	Cpos    string
	Pos     string
	Feat    string
	Head    int
	Deprel  string
	Phead   string
	Pdeprel string
}

// type Sentence []Token
type Sentence struct {
	Tokens []Token
	Length int
}

func NewToken(seq []string) *Token {
	if len(seq) != 10 {
		return nil
	}
	id, err := strconv.Atoi(seq[0])
	if err != nil {
		log.Printf("Invalid sequence: %s\n", seq[0])
		return nil
	}
	head, err := strconv.Atoi(seq[6])
	if err != nil {
		log.Printf("Invalid sequence: %s\n", seq[6])
		return nil
	}
	return &Token{
		id,
		seq[1],
		seq[2],
		seq[3],
		seq[4],
		seq[5],
		head,
		seq[7],
		seq[8],
		seq[9],
	}
}

func (t *Token) IsRoot() bool {
	return t.Head == 0
}

func NewSentence() *Sentence {
	return &Sentence{make([]Token, kInitSentLength), 0}
}

func (s *Sentence) Add(t Token) {
	if s.Length >= cap(s.Tokens) {
		newSlice := make([]Token, cap(s.Tokens)*2)
		copy(newSlice, s.Tokens)
		s.Tokens = newSlice
	}
	s.Tokens[s.Length] = t
	s.Length++
}

func (s *Sentence) Forms() []string {
	buf := make([]string, s.Length)
	for i := 0; i < s.Length; i++ {
		buf[i] = s.Tokens[i].Form
	}
	return buf
}

func (s *Sentence) String() string {
	res := ""
	for i := 0; i < s.Length; i++ {
		if i > 0 {
			res += " "
		}
		res += s.Tokens[i].Form
	}
	return res
}

func tokenize(l string) (seq []string) {
	return strings.Split(l, "\t")
}

func wrapDepText(s *Sentence) string {
	return strings.Join(s.Forms(), ` \& `) + " \\\\"
}

func wrapDepEdge(h, m int) string {
	return fmt.Sprintf(`\depedge{%d}{%d}{}`, h, m)
}

func printHeader() {
	fmt.Printf(`\documentclass{%s}
\usepackage{tikz-dependency}
\begin{document}
`, *docOption)
}

func printFooter() {
	fmt.Println(`\end{document}`)
}

func printDep(s *Sentence) {
	fmt.Printf(`\begin{dependency}[%s]
\begin{deptext}[%s]
`, *depOption, *depTxtOption)

	fmt.Println(wrapDepText(s))
	fmt.Println(`\end{deptext}`)

	for i := 0; i < s.Length; i++ {
		if s.Tokens[i].IsRoot() {
			continue
		}
		fmt.Println(wrapDepEdge(s.Tokens[i].Head, s.Tokens[i].Id))
	}

	fmt.Println(`\end{dependency}`)
}

func read(r io.Reader) {
	rd := bufio.NewReader(r)
	lineNum := 1

	s := NewSentence()
	for {
		line, err := rd.ReadString('\n')
		switch {
		case err == io.EOF:
			return
		case err != nil:
			log.Fatal(err)
		}

		if line[0] == '\n' {
			printDep(s)
			s = NewSentence()
			continue
		}

		seq := tokenize(strings.TrimRight(line, "\n"))
		if len(seq) == 0 {
			log.Fatalf("Error: Illegal line at %d\n", lineNum)
		}

		t := NewToken(seq)
		if t != nil {
			s.Add(*t)
		}

		lineNum++
	}
}

func open(file string) {
	if file == "-" {
		read(os.Stdin)
		return
	}
	f, err := os.Open(file)
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()
	read(f)
}

func main() {
	flag.Parse()

	var file string
	switch {
	case flag.NArg() == 0:
		file = "-"
	case flag.NArg() == 1:
		file = flag.Arg(0)
	case flag.NArg() > 2:
		fmt.Println("Usage: ./conllx_to_tikz_dep [options] file")
		flag.PrintDefaults()
		os.Exit(1)
	}

	printHeader()
	open(file)
	printFooter()
}
