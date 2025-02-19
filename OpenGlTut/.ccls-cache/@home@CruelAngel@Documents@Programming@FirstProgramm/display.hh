#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <string>


class Display{
    public:
        Display(int width, int height, const std::string& title){
            SDL_Init(SDL_INIT_EVERYTHING);
        
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        
            m_window =  SDL_CreateWindow(
                    title.c_str(), 
                    SDL_WINDOWPOS_CENTERED, 
                    SDL_WINDOWPOS_CENTERED,
                    width,
                    height,
                    SDL_WINDOW_OPENGL); 
            
            m_glContext = SDL_GL_CreateContext(m_window);
        
            GLenum status = glewInit();

            if(status != GLEW_OK){
                std::cerr << "FAILED" << std::endl;
            }

            isClosed = false;
        }

        void Clear(float r, float g, float b, float a){
            glClearColor(r, g, b, a);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void Update(){
            SDL_GL_SwapWindow(m_window);

            SDL_Event e;

            while(SDL_PollEvent(&e)){
                if(e.type == SDL_QUIT){
                    isClosed = true;
                }
            }
        }

        bool IsClosed(){
            return isClosed;
        }

        virtual ~Display(){
            SDL_GL_DeleteContext(m_glContext);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
        }
    private:
        SDL_Window* m_window;
        SDL_GLContext m_glContext;
        bool isClosed;
};


