/*
 *  GlobalTrace.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/24/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "GlobalTrace.h"
#include "World.h"
#include "Material.h"

// -------------------------------------------------------------------- default constructor

GlobalTrace::GlobalTrace(void)
: Tracer()
{}


// -------------------------------------------------------------------- constructor

GlobalTrace::GlobalTrace(World* _worldPtr)
: Tracer(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

GlobalTrace::~GlobalTrace(void) {}


// -------------------------------------------------------------------- trace_ray

MyRGBColor	
GlobalTrace::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed
	
	if (sr.hit_an_object)   {
		sr.ray = ray;
		return (sr.material_ptr->shade(sr));   
	}
	else
		return (world_ptr->background_color);
}

// --------------------------------------- DEPTH NOT USED YET 

MyRGBColor	
GlobalTrace::trace_ray(const Ray ray, const int depth) const {
	
	if (depth > world_ptr->vp.max_depth)
		return (black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray)); // sr is copy constructed
		
		if (sr.hit_an_object)   {
			sr.depth = depth;
			sr.ray = ray;
			return (sr.material_ptr->global_shade(sr));   
		}
		else
			return (world_ptr->background_color);
	}
}

