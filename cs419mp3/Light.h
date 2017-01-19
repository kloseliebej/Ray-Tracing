#ifndef __LIGHT__
#define __LIGHT__

/*
 *  Light.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Vector3D.h"
#include "MyRGBColor.h"
#include "Ray.h"
#include "ShadeRec.h"

class Light {
public:
	
	Light(void);
	
	Light(const Light& l);
	
	Light&
	operator= (const Light& rhs); 
	
	virtual Light*
	clone(void) const = 0;
	
	virtual
	~Light(void);
	
	virtual Vector3D
	get_direction(ShadeRec& sr) = 0;
	
	virtual float
	G(const ShadeRec& sr) const;
	
	virtual float
	pdf(const ShadeRec& sr) const;
	
	virtual MyRGBColor
	L(ShadeRec& sr);
	
	bool
	casts_shadows() const;
	
	virtual bool
	in_shadow(const Ray& ray, const ShadeRec& sr) const = 0;
	
	void
	set_shadows(const bool shadow);
	
protected:
	
	bool shadows;
	
};

inline void
Light::set_shadows(const bool shadow){
	shadows = shadow;
}


inline bool
Light::casts_shadows() const {
	return shadows;
}

inline float
Light::G(const ShadeRec& sr) const {
	return 1.0;
}

inline float
Light::pdf(const ShadeRec& sr) const{
	return 1.0;
}

#endif