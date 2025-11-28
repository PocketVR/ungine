#include <nodepp/nodepp.h>
#include <ungine/ungine.h>

/*────────────────────────────────────────────────────────────────────────────*/

using namespace nodepp;

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { void main() {

    node::node_scene([=]( ref_t<node_t> self ){

        model_t model( rl::GenMeshCube( 1, 1, 1 ) );

        auto tme = type::bind( new float(0) );
        auto img = texture_t( "./img.jpg" );
        auto pos = transform_3D_t();
        auto shd = shader_t();

        pos.translate.scale *= 10;

        shd.set_fragment_shader( GPU_KERNEL(

            varying vec2 fragTexCoord;
            uniform sampler2D img;
            uniform float tme;

            void main(){
                 gl_FragColor = texture2D( img, vec2(
                    fract( fragTexCoord.x * 100 ),
                    fract( fragTexCoord.y * 100 )
                 ) );
            }

        ) );
        
        if( shd.compile() ){
            shd.append_uniform( "img", type::bind( img ) );
            shd.append_uniform( "tme", tme );
        }

        model->materials[0].shader = shd.get();

        self->append_child( node::node_fly_camera_3D( nullptr ) );

        self->onLoop([=]( float delta ){ *tme += delta; });

        self->on3D([=](){ shd.next();
            model.draw( pos, rl::WHITE ); });
        self->on3D([=](){ rl::DrawGrid( 100, 10 ); });

        cursor::lock();

    });

}}

/*────────────────────────────────────────────────────────────────────────────*/

void onMain(){ 
    ungine::engine::start  ( 800, 600, "MyGame" );
    ungine::engine::set_fps( 60 ); ungine::main();
}

/*────────────────────────────────────────────────────────────────────────────*/