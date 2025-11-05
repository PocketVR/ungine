#include <nodepp/nodepp.h>
#include <ungine/ungine.h>

using namespace nodepp;

namespace ungine { void run() {

    node::node_scene([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto viw = self->get_attribute<viewport_t>    ( "viewport" );

        self->append_child( node::node_fly_camera_3D([=]( ref_t<node_t> self ){
            auto pos = self->get_attribute<transform_3D_t>( "transform" );
                 pos->position.y += 20; // cursor::lock();
                 pos->rotation.x += PI/4;
        }) );

        self->append_child( node::node_collision_cube([=]( ref_t<node_t> self ){
            auto pos = self->get_attribute<transform_3D_t>( "transform" );
            auto shp = self->get_attribute<shape_3D_t>    ( "shape" );
                 shp->mode = shape::MODE::SHAPE_MODE_EDGES;
                 pos->scale *= 3;

            self->onLoop([=]( float delta ){

                pos->position.y = 0;

                if  ( key::is_down('W') )
                    { pos->position.z += delta * 30; }
                elif( key::is_down('S') )
                    { pos->position.z -= delta * 30; }

                if  ( key::is_down('A') )
                    { pos->position.x += delta * 30; }
                elif( key::is_down('D') )
                    { pos->position.x -= delta * 30; }

            });

            self->onCollision([=]( node_t* node, any_t overlap ){
                pos->position = rl::Vector3MoveTowards(
                pos->position, pos->position + overlap.as<overlap_3D_t>().point
                /*--------*/ * pos->translate.scale, 10
                );
            });

        }) );

        self->onUIDraw([=](){ rl::DrawFPS ( 10 , 10 ); });
        self->on3DDraw([=](){ rl::DrawGrid( 100, 10 ); });

        self->append_child( node::node_collision_cube([=]( ref_t<node_t> self ){

            auto pos = self->get_attribute<transform_3D_t>( "transform" );
                 pos->scale    = vec3_t({ 3 , 5, 20 });
                 pos->position = vec3_t({ 30, 0, 25 });

            auto shp = self->get_attribute<shape_3D_t>( "shape" );
                 shp->mode = shape::MODE::SHAPE_MODE_EDGES;

            self->onDraw([=](){ shp->color = rl::WHITE; });

            self->onCollision([=]( node_t* node, any_t overlap ){
                shp->color = rl::GREEN;
            });

        }) );

        self->append_child( node::node_collision_cube([=]( ref_t<node_t> self ){

            auto pos = self->get_attribute<transform_3D_t>( "transform" );
                 pos->scale    = vec3_t({  3, 5, 20 });
                 pos->position = vec3_t({-30, 0, 35 });

            auto shp = self->get_attribute<shape_3D_t>( "shape" );
                 shp->mode = shape::MODE::SHAPE_MODE_EDGES;

            self->onDraw([=](){ shp->color = rl::WHITE; });

            self->onLoop([=]( float delta ){
                pos->rotation.y += delta * 3;
            });

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