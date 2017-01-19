#ifndef __MATTE__
#define __MATTE__

/*
 *  Matte.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/19/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Material.h"
#include "Lambertian.h"

class Matte: public Material {
public:
	
	Matte(void);
	
	Matte(const Matte& m);
	
	Matte&
	operator= (const Matte& m);
	
	~Matte(void);
	
	virtual Material*
	clone(void) const;
	
	void 
	set_ka(const float k);
	
	void
	set_kd(const float k);
	
	void
	set_cd(const MyRGBColor& c);
	
	void
	set_cd(const float r, const float g, const float b);
	
	void
	set_sampler(Sampler* sampl_ptr);
	
	virtual MyRGBColor
	shade(ShadeRec& sr);
	
	virtual MyRGBColor
	area_light_shade(ShadeRec& sr);
	
	virtual MyRGBColor
	path_shade(ShadeRec& sr);
	
	virtual MyRGBColor
	global_shade(ShadeRec& sr);
    
    virtual int
    name();

	
private:
	
	Lambertian*	ambient_ptr;
	Lambertian* diffuse_ptr;
};

#endif