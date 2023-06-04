CC=g++ -Wall -Werror -Wpedantic -fsanitize=address 
LDFLAGS= -lglfw -lGL -Iinclude 

OGLTest: OGLTest.cpp linked.cpp
	echo "Building OGLTest"
	$(CC) $(LDFLAGS) src/gl.c linked.cpp  OGLTest.cpp -o OGLTest

glad:
	echo "Running GLAD"
	glad --api gl:core=3.3 --out-path . c
clean:
	rm OGLTest
