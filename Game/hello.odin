package main

import "base:runtime"
import "core:log"
import "core:fmt"
import sapp "sokol-odin/sokol/app"
import shelpers "sokol-odin/sokol/helpers"
import sg "sokol-odin/sokol/gfx"

default_context : runtime.Context

Globals :: struct{
    shader: sg.Shader,
    pipeline: sg.Pipeline,
    vertex_buffer: sg.Buffer,
}
g: ^Globals

main :: proc(){
    context.logger = log.create_console_logger()
    default_context = context

    sapp.run({
        width = 800,
        height = 600,
        window_title = "John Cena",

        allocator = sapp.Allocator(shelpers.allocator(&default_context)),
        logger = sapp.Logger(shelpers.logger(&default_context)),

        init_cb = init_cb,
        frame_cb = frame_cb,
        cleanup_cb = cleanup_cb,
        event_cb = event_cb,
    })
}

init_cb :: proc "c" (){
    context = default_context

    sg.setup({
        environment = shelpers.glue_environment(),
        allocator = sg.Allocator(shelpers.allocator(&default_context)),
        logger = sg.Logger(shelpers.logger(&default_context))
    })

    g = new(Globals)
    
    g.shader = sg.make_shader(main_shader_desc(sg.query_backend()))
    g.pipeline = sg.make_pipeline({
        shader = g.shader,
        layout = {
            attrs = {
                ATTR_main_pos = { format = .FLOAT2 },
                ATTR_main_col = { format = .FLOAT4 }
            }
        }
    })

    vertices := []f32 {
        -0.3, -0.3, 1,0,0,1,
           0,  0.3, 0,1,0,1,
         0.3, -0.3, 0,0,1,1,
    }

    g.vertex_buffer = sg.make_buffer({
        data = { ptr = raw_data(vertices), size = len(vertices) * size_of(vertices[0])}
    })
}

cleanup_cb :: proc "c" (){
    context = default_context

    sg.destroy_buffer(g.vertex_buffer)
    sg.destroy_pipeline(g.pipeline)
    sg.destroy_shader(g.shader)
    
    free(g)
    sg.shutdown()
}

frame_cb :: proc "c" (){
    context = default_context

    sg.begin_pass({ swapchain = shelpers.glue_swapchain()} )
    sg.apply_pipeline(g.pipeline)
    sg.apply_bindings({
        vertex_buffers = { 0 = g.vertex_buffer }
    })
    sg.draw(0, 3, 1)

    sg.end_pass()
    
    sg.commit()

}

event_cb :: proc "c" (ev: ^sapp.Event){
    context = default_context
    
}