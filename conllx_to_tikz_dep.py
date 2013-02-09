#!/usr/bin/env python

# Copyright 2012-2013 Tetsuo Kiso. All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.

"""
A simple CoNLL-X to tikz-dependency converter.

This converter aims to provide a funtion to visualize a simple
dependency tree through converting from the CoNLL-X data format to the tikz-dependency.

Usage:
  $ ./conllx_to_tikz_dep.py [options] conllx_data

or
  $ cat conllx_data | ./conllx_to_tikz_dep.py

For the details of the input data format, see the following link:

CoNLL-X Shared Task: Multi-lingual Dependency Parsing
http://ilk.uvt.nl/conll/#dataformat
"""

import optparse

matrix_separator = '\^'
special_chars = ['{', '}', '$', '&', '%']
correct_edge_color = 'red'
wrong_edge_color = 'blue!70!black'

class Token(object):

    def __init__(self):
        self.id = None
        self.form = None
        self.lemma = None
        self.cpos = None
        self.pos = None
        self.feat = None
        self.head = None
        self.deprel = None
        self.phead = None
        self.pdeprel = None

    def is_root(self):
        return self.head == 0 or self.head == -1

class Sentence(object):

    def __init__(self):
        self.tokens = []
        self.length = 0

    def __getitem__(self, i):
        return self.tokens[i]

    def __setitem__(self, i, t):
        self.tokens[i] = t

    def add(self, t):
        self.tokens.append(t)
        self.length += 1

    def length(self):
        return self.length

    def __str__(self):
        return ' '.join([v.form for v in self.tokens])

    def to_deptext(self):
      base = ' %s ' % matrix_separator
      s = base.join([v.form for v in self.tokens]) + ' \\\\'
      return s

    # returns a tuple of (head, dependent)
    def iterate_edges(self):
        for t in self.tokens:
            if t.is_root():
                continue
            yield (t.id, t.head)

    def iterate_labeled_edges(self):
        for t in self.tokens:
            if t.is_root():
                continue
            yield (t.id, t.head, t.deprel)

    def zip(self, other):
      for tup in zip(self.tokens, other.tokens):
        if len(tup) != 2:
          print 'Error: invalid input:', tup
          sys.exit(1)
        else:
          if tup[0].is_root() and tup[1].is_root:
            continue
          yield ((tup[0].id, tup[0].head), (tup[1].id, tup[1].head))

def replace_special(s):
  for c in special_chars:
    s = s.replace(c, '\\' + c)
  return s

def init_token(lis, is_conllx=True):
    t = Token()
    t.id = int(lis[0])
    t.form = replace_special(lis[1])

    t.lemma = lis[2]
    t.cpos = lis[3]
    t.pos = lis[4]
    t.feat = lis[5]
    t.head = int(lis[6])

    if lis[7] == '_':
      t.deprel = ''
    else:
      t.deprel = lis[7]

    if is_conllx:
      t.phead = lis[8]
      t.pdeprel = lis[9]
    return t

def open_conll(filename):
    with open(filename) as f:
        return read(f)

def read(f):
    sents = []
    s = Sentence()
    for l in f:
        if l.startswith('\n'):
            sents.append(s)
            s = Sentence()
            continue

        lis = l.rstrip().split('\t')
        if len(lis) == 1:
          lis = l.rstrip().split(' ')
        if len(lis) == 0:
            continue
        elif len(lis) == 8:
          s.add(init_token(lis, False))
        elif len(lis) == 10:
          s.add(init_token(lis))
        else:
          print 'Data format is broken!'
          sys.exit(1)
    return sents

# h: head, dependent.
def wrap_depedge(dep, h, opt=None):
  if opt == None:
    return '\depedge{%d}{%d}{}' % (h, dep)
  else:
    return '\depedge[%s]{%d}{%d}{}' % (opt, h, dep)

def wrap_depedge_with_label(dep, h, label, opt=None):
  if opt == None:
    return '\depedge{%d}{%d}{%s}' % (h, dep, label)
  else:
    return '\depedge[%s]{%d}{%d}{%s}' % (opt, h, dep, label)

def wrap_depedges(sent):
    return '\n'.join([wrap_depedge(dep, h) for dep, h in sent.iterate_edges()])

def wrap_depedges_with_label(sent):
    return '\n'.join([wrap_depedge_with_label(dep, h, l) for dep, h, l in sent.iterate_labeled_edges()])

class LaTeXFormatter(object):

    def __init__(self, doc_opt, tikz_dep_opt, tikz_deptxt_opt, with_label=False):
        self.doc_opt = doc_opt
        self.tikz_dep_opt = tikz_dep_opt
        self.tikz_deptxt_opt = tikz_deptxt_opt
        self.with_label = with_label

        self.dep_template = '''\\begin{dependency}[%s]
\\begin{deptext}[%s]
%s
\end{deptext}
%s
\end{dependency}'''

    def latex_header(self):
        return '''\documentclass{%s}
\usepackage{tikz-dependency}
\\begin{document}''' % self.doc_opt

    def latex_footer(self):
        return '''\end{document}'''

    def print_tikz_dep(self, sent):
      if self.with_label:
        print self.dep_template % (self.tikz_dep_opt, self.tikz_deptxt_opt,
                                   sent.to_deptext(), wrap_depedges_with_label(sent))
      else:
        print self.dep_template % (self.tikz_dep_opt, self.tikz_deptxt_opt,
                                   sent.to_deptext(), wrap_depedges(sent))

    def diff_depedges(self, gold, predict):
      res = []
      for correct, pre in gold.zip(predict):
        if correct == pre:
          res.append(wrap_depedge(*pre))
        else:
          res.append(wrap_depedge(*correct, opt='edge style={%s}' % correct_edge_color))
          res.append(wrap_depedge(*pre, opt='edge style={%s}' % wrong_edge_color))
      return '\n'.join(res)

    def print_diff_dep(self, gold, predict):
      print '''\\begin{dependency}[%s]
\\begin{deptext}[%s]
%s
\end{deptext}
%s
\end{dependency}''' % (self.tikz_dep_opt, self.tikz_deptxt_opt,
                       gold.to_deptext(), self.diff_depedges(gold, predict))

def parse_options():
    parser = optparse.OptionParser(usage='%prog [options] data')
    parser.add_option('--doc-option', dest='doc_opt', default='standalone',
                      help='the options of documentclass')
    parser.add_option('--dep-option', dest='dep_opt', default='theme = simple',
                      help='the option of the dependency environment')
    parser.add_option('--deptxt-option', dest='deptxt_opt',
                      default='column sep=.7em,ampersand replacement=%s' % matrix_separator,
                      help='the option of the deptext environment')
    parser.add_option('--reverse-edge', dest='reverse_edge', action="store_true", default=False,
                      help='Flag to reverse the direction of edges [default: %default]')
    parser.add_option('--with-label', dest='with_label', action="store_true", default=False,
                      help='Flag to enable label [default: %default]')
    parser.add_option('--diff', dest='gold', default=None,
                      help='Diff mode. You need to specify a gold file annotated by human.')
    (options, unused_args) = parser.parse_args()

    if options.reverse_edge:
      options.dep_opt += ',edge style={<-}'
    return (options, unused_args)

def diff(opts, args, tex_formatter):
  gold = open_conll(opts.gold)
  predict = open_conll(args[0])
  for g, p in zip(gold, predict):
    print tex_formatter.latex_header()
    tex_formatter.print_diff_dep(g, p)
    print tex_formatter.latex_footer()
    print

def main():
    import sys
    opts, unused_args = parse_options()

    tex_formatter = LaTeXFormatter(opts.doc_opt, opts.dep_opt, opts.deptxt_opt, opts.with_label)

    if opts.gold:
      diff(opts, unused_args, tex_formatter)
    else:
      if len(unused_args) == 0:
        sents = read(sys.stdin)
      if len(unused_args) >= 1:
        sents = open_conll(unused_args[0])

      for i, s in enumerate(sents):
        if i > 0: print
        print tex_formatter.latex_header()
        tex_formatter.print_tikz_dep(s)
        print tex_formatter.latex_footer()

if __name__ == '__main__':
    main()
