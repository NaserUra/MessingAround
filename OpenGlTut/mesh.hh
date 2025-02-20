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
        Mesh(Vertex* vertices, unsigned int numVertices, unsigned int indices);
        
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

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int indices){
    m_drawCount = numVertices;

    glGenVertexArrays(1, &m_vertexArrayObject);

    glBindVertexArray(m_vertexArrayObject);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW); 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw(){
    glBindVertexArray(m_vertexArrayObject);

    glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

    glBindVertexArray(0);
}
