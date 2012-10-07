# Copyright 2012 Tetsuo Kiso. All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.

TARGET = conllx_to_tikz_dep

CC = gcc
#CC = clang
CFLAGS = -Wall -g -O2
LDFLAGS =

OBJS = \
	main.o \
  token.o \
  sentence.o \
  blocks.o \
	util.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
