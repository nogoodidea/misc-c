CC=g++ -Wall -g
LDFLAGS= -lfreetype -lglfw	-lGL -Iinclude -I/usr/include/freetype2

OGLTest:
	echo "Building OGLTest"
	$(CC) $(LDFLAGS) src/gl.c OGLTest.cpp -o a.out

glad:
	echo "Running GLAD"
	glad --api gl:core=3.1 --out-path . c
