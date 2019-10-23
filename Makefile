############################################################################
#                         Simple Stopwatch Library
#
#   File    : Makefile
#   Purpose : GNU Makefile using GCC to build stopwatch library and sample
#             executables.
#   Author  : Michael Dipperstein
#   Date    : July 7, 2011
#
############################################################################
#
# Stopwatch: An POSIX C/C++ Stopwatch Library
# Copyright (C) 2011 by Michael Dipperstein (mdipperstein@gmail.com)
#
# This file is part of the stopwatch library.
#
# The stopwatch library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation; either version 3 of the
# License, or (at your option) any later version.
#
# The stopwatch library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
# General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
############################################################################
CPP = g++
CC = gcc
LDPP = g++
LD = gcc
CPPFLAGS = -O2 -Wall -Wextra -pedantic -c
CFLAGS = -O2 -Wall -Wextra -pedantic -c
LDFLAGS = -O2 -lrt -o

# Treat NT and non-NT windows the same
ifeq ($(OS),Windows_NT)
	OS = Windows
endif

ifeq ($(OS),Windows)
	EXE = .exe
	DEL = del
else	#assume Linux/Unix
	EXE =
	DEL = rm
endif

all:		sample_cpp$(EXE) sample$(EXE)

sample_cpp$(EXE):	sample_cpp.o stopwatch.o
		$(LDPP) $^ $(LDFLAGS) $@

sample_cpp.o:	sample.cpp stopwatch.h
		$(CPP) $(CPPFLAGS) $< -o $@

sample$(EXE):	sample.o stopwatch.o
		$(LD) $^ $(LDFLAGS) $@

sample.o:	sample.c stopwatch.h
		$(CC) $(CFLAGS) $<

stopwatch.o:	stopwatch.c stopwatch.h
		$(CC) $(CFLAGS) $<

clean:
		$(DEL) *.o
		$(DEL) sample_cpp$(EXE)
		$(DEL) sample$(EXE)
