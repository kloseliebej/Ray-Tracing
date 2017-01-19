/*
 *  Light.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Light.h"
#include "Constants.h"

Light::Light(void)
:	shadows(true)
{}

Light::Light(const Light& ls)
:	shadows(ls.shadows)
{}

Light&
Light::operator= (const Light& rhs) {
	if (this == &rhs) 
		return (*this);
	
	shadows = rhs.shadows;
		
	return (*this);		// same I guess
}

Light::~Light(void) {}
	
MyRGBColor
Light::L(ShadeRec& sr) {
	return (black);			// return the radiance
}