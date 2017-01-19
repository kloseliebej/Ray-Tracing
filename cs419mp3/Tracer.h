// This is the declaration of the base class Tracer
// The tracer classes have no copy constructor, assignment operator. or clone function because 
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#ifndef __TRACER__
#define __TRACER__

#include "Constants.h"
#include "Ray.h"
#include "MyRGBColor.h"

class World;

class Tracer {
	public:
	
		Tracer(void);									
		
		Tracer(World* _world_ptr);						
				
		virtual											
		~Tracer(void);									

		virtual MyRGBColor	
		trace_ray(const Ray& ray) const;

		virtual MyRGBColor	
		trace_ray(const Ray ray, const int depth) const;
	
		virtual MyRGBColor
		trace_ray(const Ray ray, double& tmin, const int depth) const;
				
	protected:
	
		World* world_ptr;
};

#endif
