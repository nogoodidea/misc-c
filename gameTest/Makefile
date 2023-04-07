CC=g++ -Wall -g
LDFLAGS= -lglfw -lGL -Iinclude

OGLTest:
	echo "Building OGLTest"
	$(CC) $(LDFLAGS) src/gl.c OGLTest.cpp -o OGLTest

glad.h:
	echo "Running GLAD"
	glad --api gl:core=3.3 --profile core --out-path . c
