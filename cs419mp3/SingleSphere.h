#ifndef __SINGLE_SPHERE__
#define __SINGLE_SPHERE__
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Tracer.h"

class SingleSphere: public Tracer {
	public:
		
		SingleSphere(void);
										
		SingleSphere(World* _worldPtr);					
		
		virtual											
		~SingleSphere(void);
		
		virtual MyRGBColor	
		trace_ray(const Ray& ray) const;
};

#endif
