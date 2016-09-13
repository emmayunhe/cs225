CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpng

ifeq ($(strip $(MP_PART)),1)
TESTOBJS=rgbapixel.o png.o dsets.o
else
TESTOBJS=rgbapixel.o png.o dsets.o maze.o mazereader.o
endif

include Makefile.proxy
