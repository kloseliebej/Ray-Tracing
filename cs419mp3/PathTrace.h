#ifndef __PATH_TRACE__
#define __PATH_TRACE__

/*
 *  PathTrace.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/23/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Tracer.h"

class PathTrace: public Tracer {
public:
	
	PathTrace(void);							
	
	PathTrace(World* _world_ptr);
	
	~PathTrace(void);
	
	virtual MyRGBColor	
	trace_ray(const Ray& ray) const;
	
	virtual MyRGBColor	
	trace_ray(const Ray ray, const int depth) const;
};

#endif
