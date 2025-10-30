/*
 * Copyright 2023 The Ungine Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/UngineOfficial/Ungine/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef UNGINE_COLLISION
#define UNGINE_COLLISION

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { namespace node {

    node_t node_collision_line( function_t<void,ref_t<node_t>> clb ){
    return node_2D([=]( ref_t<node_t> self ){
        
        self->set_attribute( "collision", collision::MODE::COLLISION_MODE_2D  |
        /*-----------------------------*/ collision::MODE::COLLISION_MODE_RAY );

        auto pos = self->get_attribute<transform_2D_t>( "transform" );
        auto col = self->get_attribute<int>           ( "collision" );

        self->on2DDraw([=](){
            if( *col & collision::MODE::COLLISION_MODE_VISIBLE ){ rl::DrawLineV(
                pos->translate.position , 
                pos->translate.position + vec2_t({
                    sin( pos->translate.rotation ),
                    cos( pos->translate.rotation )
                })* pos->translate.scale.x, rl::RED
            );}
        });

    clb( self ); }); }

    node_t node_collision_rectangle( function_t<void,ref_t<node_t>> clb ){
    return node_2D([=]( ref_t<node_t> self ){
        
        self->set_attribute( "collision", collision::MODE::COLLISION_MODE_2D  |
        /*-----------------------------*/ collision::MODE::COLLISION_MODE_BOX );

        auto pos = self->get_attribute<transform_2D_t>( "transform" );
        auto col = self->get_attribute<int>           ( "collision" );

        self->on2DDraw([=](){
            if( *col & collision::MODE::COLLISION_MODE_VISIBLE ){ rl::DrawRectangleLines(
                pos->translate.position.x, pos->translate.position.y,
                pos->translate.scale.x   , pos->translate.scale.y   , rl::RED
            );}
        });

    clb( self ); }); }

    node_t node_collision_circle( function_t<void,ref_t<node_t>> clb ){
    return node_2D([=]( ref_t<node_t> self ){
        
        self->set_attribute( "collision", collision::MODE::COLLISION_MODE_2D  |
        /*-----------------------------*/ collision::MODE::COLLISION_MODE_SPH );

        auto pos = self->get_attribute<transform_2D_t>( "transform" );
        auto col = self->get_attribute<int>           ( "collision" );

        self->on2DDraw([=](){
            if( *col & collision::MODE::COLLISION_MODE_VISIBLE ){ rl::DrawCircleLines(
                pos->translate.position.x, pos->translate.position.y,
                pos->translate.scale.x   , rl::RED
            );}
        });

    clb( self ); }); }
    
    /*─······································································─*/

    node_t node_collision_ray( function_t<void,ref_t<node_t>> clb ){
    return node_3D([=]( ref_t<node_t> self ){
        
        self->set_attribute( "collision", collision::MODE::COLLISION_MODE_3D  |
        /*-----------------------------*/ collision::MODE::COLLISION_MODE_RAY );

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto col = self->get_attribute<int>           ( "collision" );

        self->on3DDraw([=](){
            if( *col & collision::MODE::COLLISION_MODE_VISIBLE ){
                auto rot = math::matrix::rotation( math::negate( pos->translate.rotation ) );
                auto fr  = vec3_t({ rot.m2, rot.m6, rot.m10 });
            rl::DrawLine3D( 
                pos->translate.position, 
                pos->translate.position+ fr * pos->translate.scale
            ,   rl::RED );}
        });

    clb( self ); }); }

    node_t node_collision_cube( function_t<void,ref_t<node_t>> clb ){
    return node_3D([=]( ref_t<node_t> self ){
        
        self->set_attribute( "collision", collision::MODE::COLLISION_MODE_3D  |
        /*-----------------------------*/ collision::MODE::COLLISION_MODE_BOX );

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto col = self->get_attribute<int>           ( "collision" );

        self->on3DDraw([=](){
            if( *col & collision::MODE::COLLISION_MODE_VISIBLE ){
            rl::DrawCubeWiresV( 
                pos->translate.position,
                pos->translate.scale   , rl::RED
            );}
        });

    clb( self ); }); }

    node_t node_collision_sphere( function_t<void,ref_t<node_t>> clb ){
    return node_3D([=]( ref_t<node_t> self ){
        
        self->set_attribute( "collision", collision::MODE::COLLISION_MODE_3D  |
        /*-----------------------------*/ collision::MODE::COLLISION_MODE_SPH );

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto col = self->get_attribute<int>           ( "collision" );

        self->on3DDraw([=](){
            if( *col & collision::MODE::COLLISION_MODE_VISIBLE ){
            rl::DrawSphereWires( 
                pos->translate.position, 
                pos->translate.scale.x , 8, 8, rl::RED
            );}
        });

    clb( self ); }); }
    
}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { namespace collision {

    bool check_rect_collision( node_t& a, node_t& b ) {

        auto col1 = a.get_attribute<int>           ( "collision" );
        auto col2 = b.get_attribute<int>           ( "collision" );

        auto pos1 = a.get_attribute<transform_2D_t>( "transform" );
        auto pos2 = b.get_attribute<transform_2D_t>( "transform" );
        
        if( *col2&collision::MODE::COLLISION_MODE_BOX ){ 
            return rl::CheckCollisionRecs( rect_t({ 
                pos1->translate.position.x,
                pos1->translate.position.y,
                pos1->translate.scale.x,
                pos1->translate.scale.y
            }),rect_t({
                pos2->translate.position.x,
                pos2->translate.position.y,
                pos2->translate.scale.x,
                pos2->translate.scale.y
            })); 
        }

        elif( *col2&collision::MODE::COLLISION_MODE_RAY ){
            // FIXME
        }

        elif( *col2&collision::MODE::COLLISION_MODE_SPH ){
            return rl::CheckCollisionCircleRec( 
                pos2->translate.position,
                pos2->translate.scale.x ,
                rect_t({
                    pos1->translate.position.x,
                    pos1->translate.position.y,
                    pos1->translate.scale.x,
                    pos1->translate.scale.y
                })
            );
        }

    return false; }
    
    /*─······································································─*/

    bool check_circ_collision( node_t& a, node_t& b ) {

        auto col1 = a.get_attribute<int>           ( "collision" );
        auto col2 = b.get_attribute<int>           ( "collision" );

        auto pos1 = a.get_attribute<transform_2D_t>( "transform" );
        auto pos2 = b.get_attribute<transform_2D_t>( "transform" );
        
        if( *col2&collision::MODE::COLLISION_MODE_BOX ){ 
            return rl::CheckCollisionCircleRec( 
                pos1->translate.position,
                pos1->translate.scale.x ,
                rect_t({
                    pos2->translate.position.x,
                    pos2->translate.position.y,
                    pos2->translate.scale.x,
                    pos2->translate.scale.y
                })
            ); 
        }

        elif( *col2&collision::MODE::COLLISION_MODE_RAY ){
            // FIXME
        }

        elif( *col2&collision::MODE::COLLISION_MODE_SPH ){
            return rl::CheckCollisionCircles( 
                pos1->translate.position,
                pos1->translate.scale.x ,
                pos2->translate.position,
                pos2->translate.scale.x 
            ); 
        }

    return false; }
    
    /*─······································································─*/

    bool check_line_collision( node_t& a, node_t& b ) {

        auto col1 = a.get_attribute<int>           ( "collision" );
        auto col2 = b.get_attribute<int>           ( "collision" );

        auto pos1 = a.get_attribute<transform_2D_t>( "transform" );
        auto pos2 = b.get_attribute<transform_2D_t>( "transform" );
        
        if( *col2&collision::MODE::COLLISION_MODE_BOX ){ 
            // FIXME
        }

        elif( *col2&collision::MODE::COLLISION_MODE_RAY ){
            // FIXME
        }

        elif( *col2&collision::MODE::COLLISION_MODE_SPH ){
            // FIXME
        }

    return false; }
    
    /*─······································································─*/

    bool check_box_collision( node_t& a, node_t& b ) {

        auto col1 = a.get_attribute<int>           ( "collision" );
        auto col2 = b.get_attribute<int>           ( "collision" );

        auto pos1 = a.get_attribute<transform_3D_t>( "transform" );
        auto pos2 = b.get_attribute<transform_3D_t>( "transform" );
        
        if( *col2&collision::MODE::COLLISION_MODE_BOX ){
            return rl::CheckCollisionBoxes( rl::BoundingBox({ 
                pos1->translate.position - pos1->translate.scale/2,
                pos1->translate.position + pos1->translate.scale/2
            }),rl::BoundingBox({ 
                pos2->translate.position - pos2->translate.scale/2,
                pos2->translate.position + pos2->translate.scale/2
            }));
        }

        elif( *col2&collision::MODE::COLLISION_MODE_RAY ){
            // FIXME
        }

        elif( *col2&collision::MODE::COLLISION_MODE_SPH ){
            return rl::CheckCollisionBoxSphere( rl::BoundingBox({ 
                pos1->translate.position - pos1->translate.scale/2,
                pos1->translate.position + pos1->translate.scale/2
            }), pos2->translate.position , pos2->translate.scale.x);
        }

    return false; }
    
    /*─······································································─*/

    bool check_sph_collision( node_t& a, node_t& b ) {

        auto col1 = a.get_attribute<int>           ( "collision" );
        auto col2 = b.get_attribute<int>           ( "collision" );

        auto pos1 = a.get_attribute<transform_3D_t>( "transform" );
        auto pos2 = b.get_attribute<transform_3D_t>( "transform" );
        
        if( *col2&collision::MODE::COLLISION_MODE_BOX ){
            return rl::CheckCollisionBoxSphere(
                rl::BoundingBox({ 
                    pos2->translate.position - pos2->translate.scale/2,
                    pos2->translate.position + pos2->translate.scale/2
                }), pos1->translate.position , pos1->translate.scale.x
            );
        }

        elif( *col2&collision::MODE::COLLISION_MODE_RAY ){
            // FIXME
        }

        elif( *col2&collision::MODE::COLLISION_MODE_SPH ){
            return rl::CheckCollisionSpheres(
                pos1->translate.position , pos1->translate.scale.x,
                pos2->translate.position , pos2->translate.scale.x
            );
        }

    return false; }
    
    /*─······································································─*/

    bool check_ray_collision( node_t& a, node_t& b ) {

        auto col1 = a.get_attribute<int>           ( "collision" );
        auto col2 = b.get_attribute<int>           ( "collision" );

        auto pos1 = a.get_attribute<transform_3D_t>( "transform" );
        auto pos2 = b.get_attribute<transform_3D_t>( "transform" );
        
        if( *col2&collision::MODE::COLLISION_MODE_BOX ){ 
            // FIXME
        }

        elif( *col2&collision::MODE::COLLISION_MODE_RAY ){
            // FIXME
        }

        elif( *col2&collision::MODE::COLLISION_MODE_SPH ){
            // FIXME
        }

    return false; }
    
    /*─······································································─*/

    bool check_collision( node_t a, node_t b ){ do {

        auto mask = collision::MODE::COLLISION_MODE_2D | collision::MODE::COLLISION_MODE_3D;
        auto col1 = a.get_attribute<int>( "collision" );
        auto col2 = b.get_attribute<int>( "collision" );

        if(( *col1 & *col2 & mask )==0) { break; }

        if( *col1&collision::MODE::COLLISION_MODE_2D ){
            if  ( *col1&collision::MODE::COLLISION_MODE_BOX ){ return check_rect_collision( a, b ); }
            elif( *col1&collision::MODE::COLLISION_MODE_SPH ){ return check_circ_collision( a, b ); }
            elif( *col1&collision::MODE::COLLISION_MODE_RAY ){ return check_line_collision( a, b ); }
        } else {
            if  ( *col1&collision::MODE::COLLISION_MODE_BOX ){ return check_box_collision( a, b ); }
            elif( *col1&collision::MODE::COLLISION_MODE_SPH ){ return check_sph_collision( a, b ); }
            elif( *col1&collision::MODE::COLLISION_MODE_RAY ){ return check_ray_collision( a, b ); }
        }

    } while(0); return false; }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/
