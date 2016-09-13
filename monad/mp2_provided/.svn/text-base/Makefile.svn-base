CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -Wall -Wextra
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi
ifeq ($(strip $(MP_PART)),1)
	TESTOBJS=rgbapixel.o png.o image.o
else
	TESTOBJS=rgbapixel.o png.o image.o scene.o
endif
include Makefile.proxy
