/*
 *  FakeSphericalLight.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "FakeSphericalLight.h"
#include "World.h"

FakeSphericalLight::FakeSphericalLight(void)
:	Light(),
ls(1.0),
color(1.0),
location(0),
r(1.0)
{}

FakeSphericalLight::FakeSphericalLight(const FakeSphericalLight& pl)
:	Light(pl),
ls(pl.ls),
color(pl.color),
location(pl.location),
r(pl.r)
{}

FakeSphericalLight&
FakeSphericalLight::operator= (const FakeSphericalLight& pl) {
	if (this == &pl)
		return (*this);
	
	Light::operator= (pl);
	
	ls = pl.ls;
	color = pl.color;
	location = pl.location;
	r = pl.r;
	
	return (*this);
}

Light*
FakeSphericalLight::clone(void) const {
	return (new FakeSphericalLight(*this));
}

Vector3D
FakeSphericalLight::get_direction(ShadeRec& sr) {
	
	Point3D new_location;
	new_location.x = location.x + r * (2.0 * rand_float() - 1.0);
	new_location.y = location.y + r * (2.0 * rand_float() - 1.0); 
	new_location.z = location.z + r * (2.0 * rand_float() - 1.0);
	
	return ((new_location - sr.hit_point).hat());
}

MyRGBColor
FakeSphericalLight::L(ShadeRec& sr) {
	return (ls * color);
}

bool
FakeSphericalLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	float t;
	int num_objects = sr.w.objects.size();
	float d = location.distance(ray.o);
	
	for (int j = 0; j < num_objects; j++)
		if (sr.w.objects[j]->shadow_hit(ray, t) && t < d)
			return (true);
	
	return (false);
}