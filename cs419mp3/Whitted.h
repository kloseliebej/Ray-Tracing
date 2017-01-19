#ifndef __WHITTED__
#define __WHITTED__
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
/*
 *  Whitted.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/22/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Tracer.h"

class Whitted: public Tracer {
public:
	
	Whitted(void);							
	
	Whitted(World* _world_ptr);
	
	~Whitted(void);
	
	virtual MyRGBColor	
	trace_ray(const Ray& ray) const;
	
	virtual MyRGBColor	
	trace_ray(const Ray ray, const int depth) const;
	
	virtual MyRGBColor
	trace_ray(const Ray ray, double& tmin, const int depth) const;
};

#endif
