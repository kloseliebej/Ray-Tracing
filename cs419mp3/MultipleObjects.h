#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Tracer.h"

class MultipleObjects: public Tracer {
	public:
		
		MultipleObjects(void);							
		
		MultipleObjects(World* _world_ptr);				
	
		virtual											
		~MultipleObjects(void);
						
		virtual MyRGBColor	
		trace_ray(const Ray& ray) const;
	
		virtual MyRGBColor	
		trace_ray(const Ray ray, const int depth) const;
};

#endif
