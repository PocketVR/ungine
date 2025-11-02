#include <nodepp/nodepp.h>
#include <ungine/ungine.h>

using namespace nodepp;

namespace ungine { void run() {

    node::node_scene([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto tim = type::bind( new float(.0f) );

        self->append_child( node::node_fly_camera_3D([=]( ref_t<node_t> self ){
            auto pos = self->get_attribute<transform_3D_t>( "transform" );
                 pos->position.y += 10; cursor::lock();
        }) );

        self->onUIDraw([=](){ rl::DrawFPS ( 10 , 10 ); });
        self->on3DDraw([=](){ rl::DrawGrid( 100, 10 ); });
        self->onLoop  ([=]( float delta ){ *tim+= delta; });

        self->append_child( node::node_collision_cube([=]( ref_t<node_t> self ){
            auto pos = self->get_attribute<transform_3D_t>( "transform" );
            auto shp = self->get_attribute<shape_3D_t>    ( "shape" );
                 shp->mode     = shape::MODE::SHAPE_MODE_FACES;
                 pos->scale    = vec3_t({ 3, 3, 3 });
                 pos->position = vec3_t({ 0, 0,25 });

            self->onDraw     ([=]( /*---*/ ){ shp->color = rl::RED;   });
            self->onCollision([=]( node_t* ){ shp->color = rl::GREEN; });
        
        }) );

    });

} }

void onMain() {

    ungine::engine::start  ( 600, 400, "my game" );
    ungine::engine::set_fps( 60 ); 
    ungine::run();

}