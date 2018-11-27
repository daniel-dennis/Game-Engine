# (c) Daniel Dennis 2018

CXX = g++ -std=c++11
CXXFLAGS = -lglew -lassimp -lglfw -lil -lilu -lilut -framework OpenGL

#BEGIN

COMP = main.o hierarchy_implementation.o gl_object.o shader_loader.o model_loader.o object_relationships.o image_loader.o camera.o key_controls.o #light_relationships.o
main: $(COMP)
	$(CXX) $(CXXFLAGS) $(COMP) -o main

MAIN = main.cpp
main.o: $(MAIN)
	$(CXX) $(MAIN) -c

HIERARCHY_IMPLEMENTATION = hierarchy_implementation.cpp hierarchy_implementation.hpp
hierarchy_implementation.o: $(HIERARCHY_IMPLEMENTATION)
	$(CXX) $(HIERARCHY_IMPLEMENTATION) -c

GL_OBJECT = gl_object.cpp gl_object.hpp
gl_object.o: $(GL_OBJECT)
	$(CXX) $(GL_OBJECT) -c

SHADER_LOADER = shader_loader.cpp shader_loader.hpp
shader_loader.o: $(SHADER_LOADER)
	$(CXX) $(SHADER_LOADER) -c

MODEL_LOADER = model_loader.cpp model_loader.hpp
model_loader.o: $(MODEL_LOADER)
	$(CXX) $(MODEL_LOADER) -c

OBJECT_RELATIONSHIPS = object_relationships.cpp object_relationships.hpp
object_relationships.o: $(OBJECT_RELATIONSHIPS)
	$(CXX) $(OBJECT_RELATIONSHIPS) -c

IMAGE_LOADER = image_loader.cpp image_loader.hpp
image_loader.o: $(IMAGE_LOADER)
	$(CXX) $(IMAGE_LOADER) -c

CAMERA = camera.cpp camera.hpp
camera.o: $(CAMERA)
	$(CXX) $(CAMERA) -c

KEY_CONTROLS = key_controls.cpp key_controls.hpp
key_controls.o: $(KEY_CONTROLS)
	$(CXX) $(KEY_CONTROLS) -c

#CLEAN UP

clean:
	rm *.o
	rm *.gch
