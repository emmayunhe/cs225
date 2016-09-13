EXENAME = testscene testimage
OBJS = testimage.o image.o png.o rgbapixel.o scene.o testscene.o

CXX = clang++
CXXFLAGS = -std=c++0x -stdlib=libc++ -c -g -O0 -w
LD = clang++
LDFLAGS = -std=c++0x -stdlib=libc++ -lpng #-lc++abi

all : $(EXENAME)

testimage : testimage.o image.o png.o rgbapixel.o
	$(LD) testimage.o image.o png.o rgbapixel.o  $(LDFLAGS) -o testimage

testscene : testscene.o scene.o image.o png.o rgbapixel.o
	$(LD) testscene.o image.o png.o rgbapixel.o scene.o $(LDFLAGS) -o testscene

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

png.o : png.cpp png.h
	$(CXX) $(CXXFLAGS) png.cpp

image.o : image.cpp image.h
	$(CXX) $(CXXFLAGS) image.cpp

scene.o : scene.cpp scene.h 
	$(CXX) $(CXXFLAGS) scene.cpp

testimage.o : testimage.cpp png.h image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

testscene.o : testscene.cpp png.h scene.h 
	$(CXX) $(CXXFLAGS) testscene.cpp
clean :
	-rm -f *.o $(EXENAME)