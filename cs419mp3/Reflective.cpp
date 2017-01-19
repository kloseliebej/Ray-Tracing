/*
 *  Reflective.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/22/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<3> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Reflective.h"
#include "World.h"
#include <iostream>
using namespace std;
// ---------------------------------------------------------------- default constructor

Reflective::Reflective (void)
:	Phong(),
reflective_brdf(new PerfectSpecular)
{}


// ---------------------------------------------------------------- copy constructor

Reflective::Reflective(const Reflective& rm)
: 	Phong(rm) {
	
	if(rm.reflective_brdf)
		reflective_brdf = (PerfectSpecular*)rm.reflective_brdf->clone(); 
	else  
		reflective_brdf = NULL;
}


// ---------------------------------------------------------------- assignment operator

Reflective& 
Reflective::operator= (const Reflective& rhs) {
	if (this == &rhs)
		return (*this);
	
	Phong::operator=(rhs);
	
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
	
	if (rhs.reflective_brdf)
		reflective_brdf = (PerfectSpecular*) rhs.reflective_brdf->clone();
	
	return (*this);
}


// ---------------------------------------------------------------- clone

Reflective*										
Reflective::clone(void) const {
	return (new Reflective(*this));
}	


// ---------------------------------------------------------------- destructor

Reflective::~Reflective(void) {
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
}

void
Reflective::set_sampler(Sampler* sampl_ptr) {
	reflective_brdf->set_sampler(sampl_ptr);
}

MyRGBColor
Reflective::shade(ShadeRec& sr) {
	MyRGBColor L(Phong::shade(sr));	// direct illumination
	
	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	MyRGBColor fr = reflective_brdf->sample_f(sr, wi, wo);
	Ray reflected_ray(sr.hit_point, wi);
	//reflected_ray.depth = sr.depth + 1;
    //cout<<"srdepth reflect = "<<sr.depth<<endl;
	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);
	
	return (L);
}

MyRGBColor										
Reflective::path_shade(ShadeRec& sr) {
	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	float pdf;
	MyRGBColor fr = reflective_brdf->sample_f(sr, wi, wo, pdf);
	Ray reflected_ray(sr.hit_point, wi);

	
	return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
}

MyRGBColor
Reflective::global_shade(ShadeRec& sr) {
	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	float pdf;
	MyRGBColor fr = reflective_brdf->sample_f(sr, wi, wo, pdf);
	Ray reflected_ray(sr.hit_point, wi);
	
	if (sr.depth == 0)
		return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 2) * (sr.normal * wi) / pdf);
	else
		return (fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi) / pdf);
}

MyRGBColor
Reflective::area_light_shade(ShadeRec& sr) {
    MyRGBColor L(Phong::area_light_shade(sr));	// direct illumination
    //L = MyRGBColor(0.75,0.75,0);
    Vector3D wo = -sr.ray.d;
    Vector3D wi;
    MyRGBColor fr = reflective_brdf->sample_f(sr, wi, wo);
    Ray reflected_ray(sr.hit_point, wi);
    sr.normal.normalize();
    wi.normalize();
    L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, (sr.depth + 1)) * (sr.normal * wi);


    return (L);
}

int
Reflective::name(){
    return 7;
}
