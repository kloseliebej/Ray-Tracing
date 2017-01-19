#include "Tracer.h"
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
// -------------------------------------------------------------------- default constructor

Tracer::Tracer(void)
	: world_ptr(NULL)
{}


// -------------------------------------------------------------------- constructor

Tracer::Tracer(World* _worldPtr)
	: world_ptr(_worldPtr)
{}



// -------------------------------------------------------------------- destructor

Tracer::~Tracer(void) {
	if (world_ptr)
		world_ptr = NULL;
}


// -------------------------------------------------------------------- trace_ray

MyRGBColor	
Tracer::trace_ray(const Ray& ray) const {
	return (black);
}


// -------------------------------------------------------------------- trace_ray

MyRGBColor	
Tracer::trace_ray(const Ray ray, const int depth) const {
	return (black);
}

MyRGBColor	
Tracer::trace_ray(const Ray ray, double& tmin, const int depth) const {
	return (black);
}



