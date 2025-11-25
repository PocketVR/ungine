#include <nodepp/nodepp.h>
#include <ungine/ungine.h>

/*────────────────────────────────────────────────────────────────────────────*/

using namespace nodepp;

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { void main() {

    node::node_scene([=]( ref_t<node_t> self ){
    
        self->append_child( node::node_fly_camera_3D( nullptr ) );
        self->on3D([=](){ rl::DrawGrid( 10, 100 ); });
        cursor::lock();

    });

}}

/*────────────────────────────────────────────────────────────────────────────*/

void onMain(){ 
    ungine::engine::start  ( 800, 600, "MyGame" );
    ungine::engine::set_fps( 60 ); ungine::main();
}

/*────────────────────────────────────────────────────────────────────────────*/