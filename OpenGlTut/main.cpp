#define SOKOL_IMPL          // WICHTIG: Implementierung aktivieren
#define SOKOL_GLCORE        // Für Linux erforderlich
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_app.h"
#include "sokol/sokol_glue.h"


// Sokol-Funktionen
void init() {  
    sg_buffer sg_make_buffer(const sg_buffer_desc*);
    
    sg_shader sg_make_shader(const sg_shader_desc*);
    
    sg_pipeline sg_make_pipeline(const sg_pipeline_desc*);
    
}
void frame() { }
void cleanup() { /* ... */ }

// SOKOL_MAIN ersetzt die Standard-main()
sapp_desc sokol_main(int argc, char* argv[]) {
    return (sapp_desc){
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .width = 800,
        .height = 600,
        .window_title = "Sokol Project",
    };
}
