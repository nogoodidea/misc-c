CC=g++ -Wall -g
LDFLAGS= -lGLEW -lglut -lGL

OGLTest:
	echo "Building OGLTest"
	$(CC) $(LDFLAGS) OGLTest.cpp -o OGLTest

glad.h:
	echo "Running GLAD"
	glad --api gl:core=3.3 --out-path . c
