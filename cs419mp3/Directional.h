#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

/*
 *  Directional.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Light.h"
#include "Vector3D.h"

class Directional: public Light {
public:
	
	Directional(void);
	
	Directional(const Directional& pl);
	
	Directional&
	operator= (const Directional& pl);
	
	virtual Light*
	clone(void) const;
	
	void
	scale_radiance(const float b);
	
	void
	set_color(const float c);
	
	void
	set_color(const MyRGBColor& c);
	
	void
	set_color(const float r, const float g, const float b); 
	
	void
	set_direction(const float x, const float y, const float z);
	
	virtual Vector3D
	get_direction(ShadeRec& sr);
	
	virtual MyRGBColor
	L(ShadeRec& sr);
	
	virtual bool
	in_shadow(const Ray& ray, const ShadeRec& sr) const;
	
private:
	
	float ls;
	MyRGBColor color;
	Vector3D direction;
};

// ------------------------------------------------------------------------------- scale_radiance

inline void
Directional::scale_radiance(const float b) { 
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
Directional::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Directional::set_color(const MyRGBColor& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Directional::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

inline void
Directional::set_direction(const float x, const float y, const float z) {
	direction.x = x; direction.y = y; direction.z = z;
	direction.normalize();
}

#endif