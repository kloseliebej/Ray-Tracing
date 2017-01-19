/*
 *  OpenCylinder.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/12/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "OpenCylinder.h"
#include "math.h"
OpenCylinder::OpenCylinder(void) 
:	GeometricObject(),
	y0(-1.0),
	y1(1.0),
	radius(1.0),
	inv_radius(1.0)
{}

OpenCylinder::OpenCylinder(const double bottom, const double top, const double r)
:	GeometricObject(),
	y0(bottom),
	y1(top),
	radius(r),
	inv_radius(1.0 / r)
{}

OpenCylinder::OpenCylinder(const OpenCylinder& c) 
:	GeometricObject(c),
	y0(c.y0),
	y1(c.y1),
	radius(c.radius),
	inv_radius(c.inv_radius)
{}

OpenCylinder*
OpenCylinder::clone(void) const {
	return (new OpenCylinder(*this));
}

OpenCylinder&
OpenCylinder::operator= (const OpenCylinder& c) {
	if (this == &c)
		return (*this);
	
	GeometricObject::operator= (c);
	
	y0 = c.y0;
	y1 = c.y1;
	radius = c.radius;
	inv_radius = c.inv_radius;
	
	return (*this);
}

OpenCylinder::~OpenCylinder(void) {}

BBox
OpenCylinder::get_bounding_box(void) const {
	double delta = 0.0001; 
	
	return (BBox(Point3D(-radius - delta, y0 - delta, -radius - delta),
				 Point3D(radius + delta, y1 + delta, radius + delta)));
}

bool 															 
OpenCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;
	
	double a = dx * dx + dz * dz;  	
	double b = 2.0 * (ox * dx + oz * dz);					
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a * c ;
	
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			
			if (yhit > y0 && yhit < y1) {
				tmin = t;
				sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
				
				// test for hitting from inside
				
				if (-ray.d * sr.normal < 0.0)
					sr.normal = -sr.normal;
				
				sr.local_hit_point = ray.o + tmin * ray.d;
				
				return (true);
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			
			if (yhit > y0 && yhit < y1) {
				tmin = t;
				sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
				
				// test for hitting inside surface
				
				if (-ray.d * sr.normal < 0.0)
					sr.normal = -sr.normal;
				
				sr.local_hit_point = ray.o + tmin * ray.d;
				
				return (true);
			}
		} 
	}
	
	return (false);			
}



bool 															 
OpenCylinder::shadow_hit(const Ray& ray, float& tmin) const {
	
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;
	
	double a = dx * dx + dz * dz;  	
	double b = 2.0 * (ox * dx + oz * dz);					
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a * c ;
	
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			
			if (yhit > y0 && yhit < y1) {
				tmin = t;
				//sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
//				
//				// test for hitting from inside
//				
//				if (-ray.d * sr.normal < 0.0)
//					sr.normal = -sr.normal;
//				
//				sr.local_hit_point = ray.o + tmin * ray.d;
				
				return (true);
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > kEpsilon) {
			double yhit = oy + t * dy;
			
			if (yhit > y0 && yhit < y1) {
				tmin = t;
//				sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
//				
//				// test for hitting inside surface
//				
//				if (-ray.d * sr.normal < 0.0)
//					sr.normal = -sr.normal;
//				
//				sr.local_hit_point = ray.o + tmin * ray.d;
				
				return (true);
			}
		} 
	}
	
	return (false);			
}