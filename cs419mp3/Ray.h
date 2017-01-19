#ifndef __RAY__
#define __RAY__

#include "Point3D.h"
#include "Vector3D.h"
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
class Ray {
	public:
	
		Point3D			o;  	// origin 
		Vector3D		d; 		// direction 
		
		Ray(void);			
		
		Ray(const Point3D& origin, const Vector3D& dir);	
		
		Ray(const Ray& ray); 		
		
		Ray& 						
		operator= (const Ray& rhs);
		 								
		~Ray(void);
};

#endif
