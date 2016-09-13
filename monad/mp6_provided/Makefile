CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpng

ifeq ($(strip $(MP_PART)),1)
TESTOBJS=png.o rgbapixel.o coloredout.o
else
TESTOBJS=png.o rgbapixel.o coloredout.o maptiles.o mosaiccanvas.o sourceimage.o tileimage.o
endif

include Makefile.proxy
