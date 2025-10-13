/*
 * Copyright 2023 The Ungine Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/UngineOfficial/Ungine/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef UNGINE_STRUCT
#define UNGINE_STRUCT

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { namespace blend { enum MODE {

    BLEND_ALPHA= 0,           // Blend textures considering alpha (default)
    BLEND_ADDITIVE,           // Blend textures adding colors
    BLEND_MULTIPLIED,         // Blend textures multiplying colors
    BLEND_ADD_COLORS,         // Blend textures adding colors (alternative)
    BLEND_SUBTRACT_COLORS,    // Blend textures subtracting colors (alternative)
    BLEND_ALPHA_PREMULTIPLY,  // Blend premultiplied textures considering alpha
    BLEND_CUSTOM,             // Blend textures using custom src/dst factors (use rlSetBlendFactors())
    BLEND_CUSTOM_SEPARATE     // Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())

};}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { namespace window { enum FLAGS {

    WINDOW_VSYNC_HINT        = 0x00000040, // Set to try enabling V-Sync on GPU
    WINDOW_FULLSCREEN        = 0x00000002, // Set to run program in fullscreen
    WINDOW_RESIZABLE         = 0x00000004, // Set to allow resizable window
    WINDOW_UNDECORATED       = 0x00000008, // Set to disable window decoration (frame and buttons)
    WINDOW_HIDDEN            = 0x00000080, // Set to hide window
    WINDOW_MINIMIZED         = 0x00000200, // Set to minimize window (iconify)
    WINDOW_MAXIMIZED         = 0x00000400, // Set to maximize window (expanded to monitor)
    WINDOW_UNFOCUSED         = 0x00000800, // Set to window non focused
    WINDOW_TOPMOST           = 0x00001000, // Set to window always on top
    WINDOW_ALWAYS_RUN        = 0x00000100, // Set to allow windows running while minimized
    WINDOW_TRANSPARENT       = 0x00000010, // Set to allow transparent framebuffer
    WINDOW_HIGHDPI           = 0x00002000, // Set to support HighDPI
    WINDOW_MOUSE_PASSTHROUGH = 0x00004000, // Set to support mouse passthrough, only supported when WINDOW_UNDECORATED
    WINDOW_BORDERLESS        = 0x00008000, // Set to run program in borderless windowed mode
    WINDOW_MSAA_4X_HINT      = 0x00000020, // Set to try enabling MSAA 4X
    WINDOW_INTERLACED_HINT   = 0x00010000  // Set to try enabling interlaced video format (for V3D)

};}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { namespace texture { enum FILTER {

    FILTER_TEXTURE_POINT=0,         // No filter, just pixel approximation
    FILTER_TEXTURE_BILINEAR,        // Linear filtering
    FILTER_TEXTURE_TRILINEAR,       // Trilinear filtering (linear with mipmaps)
    FILTER_TEXTURE_ANISOTROPIC_4X,  // Anisotropic filtering 4x
    FILTER_TEXTURE_ANISOTROPIC_8X,  // Anisotropic filtering 8x
    FILTER_TEXTURE_ANISOTROPIC_16X, // Anisotropic filtering 16x

};}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { namespace image { enum FORMAT {

    FORMAT_UNCOMPRESSED_GRAYSCALE = 1, // 8 bit per pixel (no alpha)
    FORMAT_UNCOMPRESSED_GRAY_ALPHA,    // 8*2 bpp (2 channels)
    FORMAT_UNCOMPRESSED_R5G6B5,        // 16 bpp
    FORMAT_UNCOMPRESSED_R8G8B8,        // 24 bpp
    FORMAT_UNCOMPRESSED_R5G5B5A1,      // 16 bpp (1 bit alpha)
    FORMAT_UNCOMPRESSED_R4G4B4A4,      // 16 bpp (4 bit alpha)
    FORMAT_UNCOMPRESSED_R8G8B8A8,      // 32 bpp
    FORMAT_UNCOMPRESSED_R32,           // 32 bpp (1 channel - float)
    FORMAT_UNCOMPRESSED_R32G32B32,     // 32*3 bpp (3 channels - float)
    FORMAT_UNCOMPRESSED_R32G32B32A32,  // 32*4 bpp (4 channels - float)
    FORMAT_UNCOMPRESSED_R16,           // 16 bpp (1 channel - half float)
    FORMAT_UNCOMPRESSED_R16G16B16,     // 16*3 bpp (3 channels - half float)
    FORMAT_UNCOMPRESSED_R16G16B16A16,  // 16*4 bpp (4 channels - half float)
    FORMAT_COMPRESSED_DXT1_RGB,        // 4 bpp (no alpha)
    FORMAT_COMPRESSED_DXT1_RGBA,       // 4 bpp (1 bit alpha)
    FORMAT_COMPRESSED_DXT3_RGBA,       // 8 bpp
    FORMAT_COMPRESSED_DXT5_RGBA,       // 8 bpp
    FORMAT_COMPRESSED_ETC1_RGB,        // 4 bpp
    FORMAT_COMPRESSED_ETC2_RGB,        // 4 bpp
    FORMAT_COMPRESSED_ETC2_EAC_RGBA,   // 8 bpp
    FORMAT_COMPRESSED_PVRT_RGB,        // 4 bpp
    FORMAT_COMPRESSED_PVRT_RGBA,       // 4 bpp
    FORMAT_COMPRESSED_ASTC_4x4_RGBA,   // 8 bpp
    FORMAT_COMPRESSED_ASTC_8x8_RGBA    // 2 bpp

};}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { namespace gpu { enum UNIFORM_TYPE {

    UNIFORM_BOOL  = rl::RL_SHADER_UNIFORM_INT  ,
    UNIFORM_INT   = rl::RL_SHADER_UNIFORM_INT  ,
    UNIFORM_UINT  = rl::RL_SHADER_UNIFORM_UINT ,
    UNIFORM_FLOAT = rl::RL_SHADER_UNIFORM_FLOAT,
    
    UNIFORM_BVEC2 = rl::RL_SHADER_UNIFORM_IVEC2,
    UNIFORM_IVEC2 = rl::RL_SHADER_UNIFORM_IVEC2,
    UNIFORM_UVEC2 = rl::RL_SHADER_UNIFORM_UIVEC2,
    UNIFORM_VEC2  = rl::RL_SHADER_UNIFORM_VEC2 ,
    
    UNIFORM_BVEC3 = rl::RL_SHADER_UNIFORM_IVEC3,
    UNIFORM_IVEC3 = rl::RL_SHADER_UNIFORM_IVEC3,
    UNIFORM_UVEC3 = rl::RL_SHADER_UNIFORM_UIVEC3,
    UNIFORM_VEC3  = rl::RL_SHADER_UNIFORM_VEC3 ,
    
    UNIFORM_BVEC4 = rl::RL_SHADER_UNIFORM_IVEC4,
    UNIFORM_IVEC4 = rl::RL_SHADER_UNIFORM_IVEC4,
    UNIFORM_UVEC4 = rl::RL_SHADER_UNIFORM_UIVEC4,
    UNIFORM_VEC4  = rl::RL_SHADER_UNIFORM_VEC4 ,

    UNIFORM_IMG2D = rl::RL_SHADER_UNIFORM_SAMPLER2D

};}}

namespace ungine { namespace gpu { enum ATTR_TYPE {

    ATTRIBUTE_FLOAT = rl::SHADER_ATTRIB_FLOAT  ,
    ATTRIBUTE_VEC2  = rl::RL_SHADER_ATTRIB_VEC2 ,
    ATTRIBUTE_VEC3  = rl::RL_SHADER_ATTRIB_VEC3 ,
    ATTRIBUTE_VEC4  = rl::RL_SHADER_ATTRIB_VEC4 ,

};}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { namespace camera { enum VIEW {
    PROJECTION_PERSPECTIVE=0, // Perspective  projection
    PROJECTION_ORTHOGRAPHIC   // Orthographic projection
}; }}

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { namespace render { enum MASK {
    VISIBILITY_MASK_NONE = 0b00000000,
    VISIBILITY_MASK_1    = 0b00000001,
    VISIBILITY_MASK_2    = 0b00000010,
    VISIBILITY_MASK_3    = 0b00000100,
    VISIBILITY_MASK_4    = 0b00001000,
    VISIBILITY_MASK_5    = 0b00010000,
    VISIBILITY_MASK_6    = 0b00100000,
    VISIBILITY_MASK_7    = 0b01000000,
    VISIBILITY_MASK_8    = 0b10000000,
    VISIBILITY_MASK_ALL  = 0b11111111
};}}

namespace ungine { namespace render { enum MODE {
    RENDER_MODE_UI, RENDER_MODE_2D, RENDER_MODE_3D
};}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine {

    using color_t = rl::Color;

    using   mat_t = rl::Matrix; 
    using  vec2_t = rl::Vector2;
    using  vec3_t = rl::Vector3;
    using  vec4_t = rl::Vector4;
    using  rect_t = rl::Rectangle;

    struct bvec2_t { bool  x; bool y; };
    struct ivec2_t {  int  x;  int y; };
    struct uvec2_t { uint  x; uint y; };

    struct bvec3_t { bool  x; bool y; bool z; };
    struct ivec3_t {  int  x;  int y;  int z; };
    struct uvec3_t { uint  x; uint y; uint z; };

    struct bvec4_t { bool  x; bool y; bool z; bool w; };
    struct ivec4_t {  int  x;  int y;  int z;  int w; };
    struct uvec4_t { uint  x; uint y; uint z; uint w; };

}

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { struct transform_3D_t {

    struct priv {
        vec3_t rotation = { 0, 0, 0 };
        vec3_t position = { 0, 0, 0 };
        vec3_t scale    = { 1, 1, 1 };
    } translate = {0};

    vec3_t rotation = { 0, 0, 0 };
    vec3_t position = { 0, 0, 0 };
    vec3_t scale    = { 1, 1, 1 };
    vec3_t origin   = { 0, 0, 0 };

};}

namespace ungine { struct transform_2D_t {
    
    struct priv {
        float  rotation = .0f;
        vec2_t position = { 0, 0 };
        vec2_t scale    = { 1, 1 };
    } translate = {0};
    
    float  rotation = .0f;
    vec2_t position = { 0, 0 };
    vec2_t scale    = { 1, 1 };
    vec2_t origin   = { 0, 0 };

};}

namespace ungine { 
    using render_2D_t    = rl::RenderTexture;
    using transform_UI_t = transform_2D_t; 
    using camera_2D_t    = rl::Camera2D; 
    using camera_3D_t    = rl::Camera3D;
}

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { struct visibility_t {
    uint mask    = render::MASK::VISIBILITY_MASK_ALL;
    uint mode    = render::MODE::RENDER_MODE_UI;
    bool visible = true;
};}

namespace ungine { struct viewport_t {
    uint mask = render::MASK::VISIBILITY_MASK_ALL;
    color_t background = { 0, 0, 0, 255 };
    ref_t<camera_2D_t> camera2D; 
    ref_t<camera_3D_t> camera3D;
    ref_t<render_2D_t> render  ;
};}

namespace ungine { struct render_queue_t {
    queue_t<event_t<>> event3D;
    queue_t<event_t<>> event2D;
    queue_t<event_t<>> eventUI;
};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/