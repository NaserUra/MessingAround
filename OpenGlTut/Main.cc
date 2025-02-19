#include "display.hh"
#include "shader.hh"
#include "mesh.hh"

int main(int argc, char *argv[])
{	
    Display display(800, 600, "Hello World!");
    Shader shader("../res/basicShader"); //add right path
    Vertex vertices[] = {   
        Vertex(glm::vec3(-0.5,-0.5,0)),                    
        Vertex(glm::vec3(0,0.5,0)),
        Vertex(glm::vec3(0.5,-0.5,0))
    };

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));

    while(!display.IsClosed()){
        display.Clear(0, 0, 0.1, 1.0);

        mesh.Draw();

        shader.Bind();
        display.Update();
    }

	return 0;
}
