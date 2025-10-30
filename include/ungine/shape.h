/*
 * Copyright 2023 The Ungine Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/UngineOfficial/Ungine/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef UNGINE_SHAPES
#define UNGINE_SHAPES

/*────────────────────────────────────────────────────────────────────────────*/

// FIXME: ADD SHAPE 2D DRAW SELECTOR SUPPORT
namespace ungine { struct shape_2D_t {
    uchar   mode  = shape::MODE::SHAPE_DRAW_FACES;
    color_t color = rl::WHITE;
    ptr_t<vec2_t>   points ;
    ptr_t<shader_t> shader ;
};}

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { namespace node {

    node_t node_strip_polygon( int sides, function_t<void,ref_t<node_t>> clb ) {
    return node_2D( [=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_2D_t>( "transform" );
        auto tmp = shape_2D_t(); tmp.points = ptr_t<vec2_t>({
             vec2_t({ 0, 0 }), vec2_t({ 0, 1 }),
             vec2_t({ 1, 0 }), vec2_t({ 1, 1 })
        });

        auto ptr = queue_t<vec2_t>();
        /*------*/ self->set_attribute( "shape", tmp );
        auto shp = self->get_attribute<shape_2D_t>( "shape" );

        self->onLoop([=]( float ){
            ptr.clear(); for( auto x: shp->points ){ 
            ptr.push( pos->translate.position + rl::Vector2Rotate(
            x * pos->translate.scale   , 
                pos->translate.rotation 
            )); } 
        });

        self->on2DDraw([=](){ if( ptr.empty() ){ return; }
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::BeginShaderMode( shp->shader->get() ); shp->shader->set_variables(); }
            rl::DrawTriangleStrip( ptr.data().get(), ptr.size(), shp->color );
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::EndShaderMode();  }
        });

    clb( self ); }); }

    /*─······································································─*/

    node_t node_fan_polygon( int sides, function_t<void,ref_t<node_t>> clb ) {
    return node_2D( [=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_2D_t>( "transform" );
        auto tmp = shape_2D_t(); tmp.points = ptr_t<vec2_t>( sides ); 
        
        for( auto x=tmp.points.size(); x-->0; ){
             tmp.points[x].x = sin( 2*PI*x/tmp.points.size() );
             tmp.points[x].y = cos( 2*PI*x/tmp.points.size() );
        }

        auto ptr = queue_t<vec2_t>();
        /*------*/ self->set_attribute( "shape", tmp );
        auto shp = self->get_attribute<shape_2D_t>( "shape" );

        self->onLoop([=]( float ){
            ptr.clear(); for( auto x: shp->points ){ 
            ptr.push( pos->translate.position + rl::Vector2Rotate(
            x * pos->translate.scale   ,
                pos->translate.rotation 
            )); } 
        });

        self->on2DDraw([=](){ if( ptr.empty() ){ return; }
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::BeginShaderMode( shp->shader->get() ); shp->shader->set_variables(); }
            rl::DrawTriangleFan( ptr.data().get(), ptr.size(), shp->color );
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::EndShaderMode();  }
        });

    clb( self ); }); }

    /*─······································································─*/

    node_t node_triangle( function_t<void,ref_t<node_t>> clb ) { 
        return node_fan_polygon( 3, clb );
    }

    node_t node_rectangle( function_t<void,ref_t<node_t>> clb ) {
        return node_strip_polygon( 16, clb );
    }

    node_t node_circle( function_t<void,ref_t<node_t>> clb ) { 
        return node_fan_polygon( 16, clb );
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

// FIXME: ADD SHAPE 3D SUPPORT
namespace ungine { struct shape_3D_t {
    uchar   mode  = shape::MODE::SHAPE_DRAW_FACES;
    color_t color = rl::WHITE;
    ptr_t<model_t>  model;
    ptr_t<shader_t> shader;
};}

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { namespace node {

    node_t node_heightmap( image_t img, function_t<void,ref_t<node_t>> clb ) {
    return node_3D([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto tmp = shape_3D_t(); tmp.model = type::bind(
             model_t( rl::GenMeshHeightmap( img.get(), vec3_t({1,1,1}) ) )
        );   self->set_attribute( "shape", tmp );

        auto shp = self->get_attribute<shape_3D_t>( "shape" );

        self->on3DDraw([=](){ if( shp->model.null() ){ return; }
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::BeginShaderMode( shp->shader->get() ); shp->shader->set_variables(); }
    
            if  ( shp->mode & shape::MODE::SHAPE_DRAW_FACES  ){ shp->model->draw       ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_EDGES  ){ shp->model->draw_edges ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_VERTEX ){ shp->model->draw_vertex( *pos, shp->color ); }
            
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::EndShaderMode();  }
        });

    clb( self ); }); }
    
    node_t node_cubicmap( image_t img, function_t<void,ref_t<node_t>> clb ) {
    return node_3D([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto tmp = shape_3D_t(); tmp.model = type::bind(
             model_t( rl::GenMeshCubicmap( img.get(), vec3_t({1,1,1}) ) )
        );   self->set_attribute( "shape", tmp );

        auto shp = self->get_attribute<shape_3D_t>( "shape" );

        self->on3DDraw([=](){ if( shp->model.null() ){ return; }
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::BeginShaderMode( shp->shader->get() ); shp->shader->set_variables(); }
    
            if  ( shp->mode & shape::MODE::SHAPE_DRAW_FACES  ){ shp->model->draw       ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_EDGES  ){ shp->model->draw_edges ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_VERTEX ){ shp->model->draw_vertex( *pos, shp->color ); }
            
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::EndShaderMode();  }
        });

    clb( self ); }); }
    
    node_t node_cone( function_t<void,ref_t<node_t>> clb ) {
    return node_3D([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto tmp = shape_3D_t(); tmp.model = type::bind(
             model_t( rl::GenMeshCylinder( 1, 1, 8 ) )
        );   self->set_attribute( "shape", tmp );

        auto shp = self->get_attribute<shape_3D_t>( "shape" );

        self->on3DDraw([=](){ if( shp->model.null() ){ return; }
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::BeginShaderMode( shp->shader->get() ); shp->shader->set_variables(); }
    
            if  ( shp->mode & shape::MODE::SHAPE_DRAW_FACES  ){ shp->model->draw       ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_EDGES  ){ shp->model->draw_edges ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_VERTEX ){ shp->model->draw_vertex( *pos, shp->color ); }
            
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::EndShaderMode();  }
        });

    clb( self ); }); }
    
    node_t node_cylinder( function_t<void,ref_t<node_t>> clb ) {
    return node_3D([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto tmp = shape_3D_t(); tmp.model = type::bind(
             model_t( rl::GenMeshCylinder( 1, 1, 8 ) )
        );   self->set_attribute( "shape", tmp );

        auto shp = self->get_attribute<shape_3D_t>( "shape" );

        self->on3DDraw([=](){ if( shp->model.null() ){ return; }
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::BeginShaderMode( shp->shader->get() ); shp->shader->set_variables(); }
    
            if  ( shp->mode & shape::MODE::SHAPE_DRAW_FACES  ){ shp->model->draw       ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_EDGES  ){ shp->model->draw_edges ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_VERTEX ){ shp->model->draw_vertex( *pos, shp->color ); }
            
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::EndShaderMode();  }
        });

    clb( self ); }); }

    node_t node_quad( function_t<void,ref_t<node_t>> clb ) {
    return node_3D([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto tmp = shape_3D_t(); tmp.model = type::bind(
             model_t( rl::GenMeshPlane( 1, 1, 1, 1 ) )
        );   self->set_attribute( "shape", tmp );

        auto shp = self->get_attribute<shape_3D_t>( "shape" );

        self->on3DDraw([=](){ if( shp->model.null() ){ return; }
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::BeginShaderMode( shp->shader->get() ); shp->shader->set_variables(); }
    
            if  ( shp->mode & shape::MODE::SHAPE_DRAW_FACES  ){ shp->model->draw       ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_EDGES  ){ shp->model->draw_edges ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_VERTEX ){ shp->model->draw_vertex( *pos, shp->color ); }
            
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::EndShaderMode();  }
        });

    clb( self ); }); }
    
    node_t node_cube( function_t<void,ref_t<node_t>> clb ) {
    return node_3D([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto tmp = shape_3D_t(); tmp.model = type::bind(
             model_t( rl::GenMeshCube( 1, 1, 1 ) )
        );   self->set_attribute( "shape", tmp );

        auto shp = self->get_attribute<shape_3D_t>( "shape" );

        self->on3DDraw([=](){ if( shp->model.null() ){ return; }
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::BeginShaderMode( shp->shader->get() ); shp->shader->set_variables(); }
    
            if  ( shp->mode & shape::MODE::SHAPE_DRAW_FACES  ){ shp->model->draw       ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_EDGES  ){ shp->model->draw_edges ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_VERTEX ){ shp->model->draw_vertex( *pos, shp->color ); }
            
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::EndShaderMode();  }
        });

    clb( self ); }); }

    node_t node_sphere( function_t<void,ref_t<node_t>> clb ) {
    return node_3D([=]( ref_t<node_t> self ){

        auto pos = self->get_attribute<transform_3D_t>( "transform" );
        auto tmp = shape_3D_t(); tmp.model = type::bind(
             model_t( rl::GenMeshSphere( 1, 8, 8 ) )
        );   self->set_attribute( "shape", tmp );

        auto shp = self->get_attribute<shape_3D_t>( "shape" );

        self->on3DDraw([=](){ if( shp->model.null() ){ return; }
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::BeginShaderMode( shp->shader->get() ); shp->shader->set_variables(); }
    
            if  ( shp->mode & shape::MODE::SHAPE_DRAW_FACES  ){ shp->model->draw       ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_EDGES  ){ shp->model->draw_edges ( *pos, shp->color ); }
            elif( shp->mode & shape::MODE::SHAPE_DRAW_VERTEX ){ shp->model->draw_vertex( *pos, shp->color ); }
            
        if( !shp->shader.null() && shp->shader->is_valid() )
          { rl::EndShaderMode();  }
        });

    clb( self ); }); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/
