#include <nodepp/nodepp.h>
#include <ungine/ungine.h>

using namespace nodepp;

namespace ungine { void run() {

    node::node_scene([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto tim = type::bind( new float(.0f) );

        self->append_child( node::fly_camera_3D([=]( ref_t<node_t> self ){
            auto pos = self->get_attribute<transform_3D_t>( "transform" );
                 pos->position.y += 10; cursor::lock();

            self->append_child( "box", node::node_collision_cube([=]( ref_t<node_t> self ){

                auto pos = self->get_attribute<transform_3D_t>( "transform" );
                auto col = self->get_attribute<int>           ( "collision" );
                    pos->scale    = vec3_t({ 10, 10, 10 });

                * col |= collision::MODE::COLLISION_MODE_VISIBLE;

                self->onCollision([=]( node_t* node ){
                    console::log( "BBB" );
                });

            }) );

        }) );

        self->append_child( "box2", node::node_cube([=]( ref_t<node_t> self ){

            auto pos = self->get_attribute<transform_3D_t>( "transform" );
            auto shp = self->get_attribute<shape_3D_t>    ( "shape" );
                 pos->scale    = vec3_t({ 10, 10, 10 });
                 pos->position = vec3_t({ 10, 10, 10 }); 

            self->onLoop([=]( float ){ pos->position.x += cos( *tim ); });

            self->onDraw([=](){ shp->color = rl::GetColor( 0x00FF00FF ); });

            self->append_child( "box", node::node_collision_sphere([=]( ref_t<node_t> self ){

                auto pos = self->get_attribute<transform_3D_t>( "transform" );
                auto col = self->get_attribute<int>           ( "collision" );
                    pos->scale    = vec3_t({ 10, 10, 10 });

                * col |= collision::MODE::COLLISION_MODE_VISIBLE;

                self->onCollision([=]( node_t* node ){
                    shp->color = rl::GetColor( 0xFF0000FF );
                    console::log( "AAA" );
                });

            }) );

        }) );

        self->onUIDraw([=](){ rl::DrawFPS ( 10 , 10 ); });
        self->on3DDraw([=](){ rl::DrawGrid( 100, 10 ); });
        self->onLoop([=]( float delta ){ *tim+= delta; });

    });

} }

void onMain() {

    ungine::engine::start( 600, 400, "my game" );
    ungine::engine::set_fps( 60 ); 
    ungine::run();

}