CC=g++ -Wall -g
LDFLAGS= -fsanitize=address -lglfw -lGL -Iinclude 

OGLTest: OGLTest.cpp
	echo "Building OGLTest"
	$(CC) $(LDFLAGS) src/gl.c OGLTest.cpp -o OGLTest

glad:
	echo "Running GLAD"
	glad --api gl:core=3.3 --out-path . c
clean:
	rm OGLTest
