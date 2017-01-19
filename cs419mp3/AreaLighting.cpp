/*
 *  AreaLighting.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/26/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<3> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "AreaLighting.h"
#include "World.h"
#include "Material.h"
#include <iostream>
using namespace std;
// -------------------------------------------------------------------- default constructor

AreaLighting::AreaLighting(void)
: Tracer()
{}


// -------------------------------------------------------------------- constructor

AreaLighting::AreaLighting(World* _worldPtr)
: Tracer(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

AreaLighting::~AreaLighting(void) {}


// -------------------------------------------------------------------- trace_ray

MyRGBColor	
AreaLighting::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed
	
	if (sr.hit_an_object)   {
		sr.ray = ray;
		return (sr.material_ptr->area_light_shade(sr));   
	}
	else
		return (world_ptr->background_color);
}

// --------------------------------------- DEPTH NOT USED YET 

MyRGBColor	
AreaLighting::trace_ray(const Ray ray, const int depth) const{
//	ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed
//	
//	if (sr.hit_an_object)   {
//		sr.ray = ray;
//		return (sr.material_ptr->area_light_shade(sr));   
//	}
//	else
//		return (world_ptr->background_color);
    //cout<<"max_depth"<<world_ptr->vp.max_depth<<endl;
    //cout<<"depth"<<depth<<endl;
    world_ptr->num_rays++;
    if (depth > world_ptr->vp.max_depth){
        
        return (black);
    }
    else {
        ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed
        
        if (sr.hit_an_object)   {
            //cout<<"depth  "<<depth<<endl;
            sr.depth = depth;
            sr.ray = ray;
//            if(sr.depth == 1){
//                cout<<"sr1"<<endl;
//                cout<<"name = "<<sr.material_ptr->name()<<endl;
//                //if(sr.material_ptr->name()==2)
//                  //      cout<<"average color = "<<sr.material_ptr->area_light_shade(sr).average()<<endl;
//            }
            return (sr.material_ptr->area_light_shade(sr));
        }
        else
            return (world_ptr->background_color);
    }
}

MyRGBColor
AreaLighting::trace_ray(const Ray ray, double& tmin, const int depth) const {
	if (depth > world_ptr->vp.max_depth)
		return (black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));    
		
		if (sr.hit_an_object) {
			sr.depth 	= depth;
			sr.ray 		= ray;	
			tmin		= sr.t;     // required for colored transparency 
			
			return (sr.material_ptr->area_light_shade(sr));   
		}
		else {
			tmin = kHugeValue;
			
			return (world_ptr->background_color);
		}
	}
}
