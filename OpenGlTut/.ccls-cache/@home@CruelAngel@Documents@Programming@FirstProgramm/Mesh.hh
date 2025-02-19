#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex{
    public:
        Vertex(const glm::vec3& pos){
            this->pos = pos;
        }
    private:
        glm::vec3 pos;    
};

class Mesh{
    public:
        Mesh(Vertex* vertices, unsigned int numVertices);
        
        void Draw();

        virtual ~Mesh();
    private:
        Mesh(const Mesh& other){}
        void operator=(const Mesh& other){}

        enum{
            POSITION_VB,

            NUM_BUFFERS
        };
        
        GLuint m_vertexArrayObject;
        GLuint m_vertexArrayBuffers[NUM_BUFFERS];
        unsigned int m_drawCount;
};

Mesh::Mesh(Vertex* vertices, unsigned int numVertices){
    m_drawCount = numVertices;

    glGenVertexArrays(1, &m_vertexArrayObject);

    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW); 

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}
