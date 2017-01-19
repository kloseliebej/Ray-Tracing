#include "SingleSphere.h"
#include "World.h"
#include "ShadeRec.h"
#include <iostream>
using namespace std;
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
// -------------------------------------------------------------------- default constructor

SingleSphere::SingleSphere(void)
	: Tracer()
{}


// -------------------------------------------------------------------- constructor
		
SingleSphere::SingleSphere(World* _worldPtr)
	: Tracer(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

SingleSphere::~SingleSphere(void) {}


// -------------------------------------------------------------------- trace_ray

MyRGBColor	
SingleSphere::trace_ray(const Ray& ray) const {
	ShadeRec	sr(*world_ptr); 	// not used
	double    	t;  				// not used
    //cout<<"Single Sphere"<<endl;
	if (world_ptr->sphere.hit(ray, t, sr))		
		return (red);  
	else
		return (black);   
}


