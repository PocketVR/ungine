#include <nodepp/nodepp.h>
#include <ungine/ungine.h>

using namespace nodepp;

namespace ungine { void run() {

    auto render_2D = node::node_render([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto viw = self->get_attribute<viewport_t>    ( "viewport" );

        self->append_child( node::node_rectangle([=]( ref_t<node_t> self ){

            auto pos = self->get_attribute<transform_2D_t>( "transform" );
            auto shp = self->get_attribute<shape_2D_t>    ( "shape" );
                 pos->scale *= 10; shp->color = rl::RED;

            auto time = type::bind( new float(.0f) );

            self->onLoop([=]( float delta ){
                pos->position = vec2_t({
                    sinf( *time ) * 100 + rl::GetRenderWidth ()/2,
                    cosf( *time ) * 100 + rl::GetRenderHeight()/2
                }); *time += delta;
            });

        }) );

        self->onUIDraw([=](){ rl::DrawFPS( 100, 100 ); });

    });

    node::node_scene([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto viw = self->get_attribute<viewport_t>    ( "viewport" );

        self->append_child( node::node_fly_camera_3D([=]( ref_t<node_t> self ){
            auto pos = self->get_attribute<transform_3D_t>( "transform" );
                 pos->position.y += 10; cursor::lock();

            self->append_child( node::node_collision_ray([=]( ref_t<node_t> self ){
                auto pos = self->get_attribute<transform_3D_t>( "transform" );
                     pos->scale *= 30;

                self->on2DDraw([=](){
                    auto size = window::get_size();
                    rl::DrawCircle( size.x/2, size.y/2, 3, rl::WHITE );
                });

            }) );

        }) );

        self->onUIDraw([=](){ rl::DrawFPS ( 10 , 10 ); });
        self->on3DDraw([=](){ rl::DrawGrid( 100, 10 ); });

        self->append_child( node::node_3D([=]( ref_t<node_t> self ){

            auto pos = self->get_attribute<transform_3D_t>( "transform" );
                 pos->scale    = vec3_t({ 3, 3, 3 });
                 pos->position = vec3_t({ 0, 0,25 });

            auto mdl = model_t( rl::GenMeshCube( 1, 1, 1 ) );
            auto rnd = render_2D.get_viewport()->render;
            auto shd = shader_t();
            
            mdl->materials[0].maps[0].texture = rnd->get_texture();

            self->on3DDraw([=](){ shd.emit([=](){
                mdl.draw( *pos, rl::WHITE );
            }); });
        
        }) );

    });

} }

void onMain() {

    ungine::engine::start  ( 600, 400, "my game" );
    ungine::engine::set_fps( 60 ); 
    ungine::run();

}