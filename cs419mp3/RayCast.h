#ifndef __RAY_CAST__
#define __RAY_CAST__
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Tracer.h"

class RayCast: public Tracer {
public:
	
	RayCast(void);							
	
	RayCast(World* _world_ptr);				
	
	virtual											
	~RayCast(void);
	
	virtual MyRGBColor	
	trace_ray(const Ray& ray) const;
	
	virtual MyRGBColor	
	trace_ray(const Ray ray, const int depth) const;
};

#endif
