CC=g++ -Wall -g
LDFLAGS= -lfreetype -lglfw	-lGL -Iinclude

OGLTest:
	echo "Building OGLTest"
	$(CC) $(LDFLAGS) src/gl.c stbLoad.cpp OGLTest.cpp -o a.out

glad:
	echo "Running GLAD"
	glad --api gl:core=3.3 --out-path . c
