#include <nodepp/nodepp.h>
#include <ungine/ungine.h>

using namespace nodepp;

namespace ungine { void run() {

    node::node_scene([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto viw = self->get_attribute<viewport_t>    ( "viewport" );

        self->append_child( node::node_fly_camera_3D([=]( ref_t<node_t> self ){
            auto ppos = self->get_attribute<transform_3D_t>( "transform" );
                 ppos->position.y += 10; cursor::lock();

            self->append_child( node::node_collision_ray([=]( ref_t<node_t> self ){
                auto pos = self->get_attribute<transform_3D_t>( "transform" );
                     pos->scale *= 30;

                self->on2DDraw([=](){
                    auto size = window::get_size();
                    rl::DrawCircle( size.x/2, size.y/2, 3, rl::WHITE );
                });

                self->onCollision([=]( node_t* node, any_t overlap ){
                    ppos->position += overlap.as<overlap_3D_t>().point
                                    * pos->translate.scale;
                });

            }) );

        }) );

        self->onUIDraw([=](){ rl::DrawFPS ( 10 , 10 ); });
        self->on3DDraw([=](){ rl::DrawGrid( 100, 10 ); });

        self->append_child( node::node_collision_cube([=]( ref_t<node_t> self ){

            auto pos = self->get_attribute<transform_3D_t>( "transform" );
                 pos->scale    = vec3_t({ 3, 3, 3 });
                 pos->position = vec3_t({ 0, 0,25 });

            auto shp = self->get_attribute<shape_3D_t>( "shape" );
                 shp->mode = shape::MODE::SHAPE_MODE_EDGES;

            self->onDraw([=](){ shp->color = rl::WHITE; });

            self->onCollision([=]( node_t* node, any_t overlap ){
                shp->color = rl::GREEN;
            });

        }) );

    });

} }

void onMain() {

    ungine::engine::start  ( 600, 400, "my game" );
    ungine::engine::set_fps( 60 ); 
    ungine::run();

}