#ifndef __LAMBERTIAN__
#define __LAMBERTIAN__

/*
 *  Lambertian.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/17/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "BRDF.h"
#include "Sampler.h"

class Lambertian: public BRDF {
public:
	Lambertian(void);
	
	Lambertian(const Lambertian& lamb);
	
	Lambertian&
	operator= (const Lambertian& rhs);
	
	~Lambertian(void);
	
	virtual BRDF*
	clone(void) const;
	
	void
	set_kd(const float the_kd);
	
	void
	set_cd(const MyRGBColor cd);
	
	void
	set_cd(const float r, const float g, const float b);
	
	virtual MyRGBColor
	f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr,  Vector3D& wi, const Vector3D& wo) const;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr,  Vector3D& wi, const Vector3D& wo, float& pdf) const;
	
	virtual MyRGBColor
	rho(const ShadeRec& sr, const Vector3D& wo) const;
	
	
private:
	
	float kd;		// diffuse coefficient
	MyRGBColor cd;	// diffuse color
};
	
inline void
Lambertian::set_kd(const float the_kd) {
	kd = the_kd;
}

inline void
Lambertian::set_cd(const MyRGBColor the_cd) {
	cd = the_cd;
}

inline void
Lambertian::set_cd(const float r, const float g, const float b) {
	cd.r = r; cd.g = g; cd.b = b;
}

#endif