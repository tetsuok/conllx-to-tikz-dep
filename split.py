#!/usr/bin/env python

# Copyright 2013 Tetsuo Kiso. All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.

"""
A helper script to split sentences separated by new lines such as
CoNLL format.

Usage:
  $ ./split.py file [directory to output]
"""

import os
import sys

def split(filename, out, ext):
  i = 0
  fout = open('%s/%05d%s' % (out, i, ext), 'w')
  with open(filename) as f:
    for l in f:
      if l.startswith('n'):
        print >>fout
        fout.close()
        i += 1
        fout = open('%s/%05d%s' % (out, i, ext), 'w')
      else:
        print >>fout, l,
  fout.close()

def main():
  if len(sys.argv) < 2:
    print 'Usage: %s filename [outdir]' % sys.argv[0]
    sys.exit(1)
  if len(sys.argv) > 2:
    out = sys.argv[2]
  else:
    out = '.'

  filename = sys.argv[1]
  _, ext = os.path.splitext(filename)
  split(filename, out, ext)


if __name__ == '__main__':
    main()
