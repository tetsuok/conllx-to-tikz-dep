# Copyright 2012 Tetsuo Kiso. All rights reserved.
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file.

TARGET = conllx_to_tikz_dep conllx_to_tikz_dep_pp

CC = gcc
CXX = g++
OPT = -O2
CFLAGS = -Wall -g $(OPT)

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
CC = clang
CXX = clang++
CFLAGS = -Weverything -g $(OPT)
endif

LDFLAGS =

OBJS = \
	latex_helper.o \
  token.o \
  sentence.o \
  blocks.o \
	util.o

all: $(TARGET)

conllx_to_tikz_dep: main.o $(OBJS)
	$(CC) -o $@ main.o $(OBJS) $(LDFLAGS)

conllx_to_tikz_dep_pp: cpp_main.o $(OBJS)
	$(CXX) -o $@ cpp_main.o $(OBJS) $(LDFLAGS)

clean:
	-rm -f *.o $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.cc.o:
	$(CXX) $(CFLAGS) -c $< -o $@
