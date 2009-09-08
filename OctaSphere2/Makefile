TARGET		=Sphere 

$(TARGET):	Sphere.o  gl2ps.o 
	g++ -g -o $(TARGET) Sphere.o  gl2ps.o  \
	 `sdl-config --libs` -lGL -lGLU -lgltt -lttf  -lm

Sphere.o:   
	g++ -g  -c Sphere.cpp `sdl-config --cflags`

gl2ps.o:
	cc -g -c gl2ps.c 

clean:
	rm -f $(TARGET) *.o  core
