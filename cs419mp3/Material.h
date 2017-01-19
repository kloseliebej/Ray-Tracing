#ifndef __MATERIAL__
#define __MATERIAL__

/*
 *  Material.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Material.h"
#include "ShadeRec.h"
#include "MyRGBColor.h"

class Material {
public:
	Material(void);
	
	Material(const Material& m);
	
	Material&
	operator= (const Material& m);
	
	virtual Material*
	clone(void) const = 0;
	
	~Material(void);
	
	virtual MyRGBColor
	shade(ShadeRec& sr);
	
	virtual MyRGBColor
	area_light_shade(ShadeRec& sr);
	
	virtual MyRGBColor
	path_shade(ShadeRec& sr);
	
	virtual MyRGBColor
	global_shade(ShadeRec& sr);
	
	virtual MyRGBColor
	get_Le(ShadeRec& sr) const;
	
	void
	set_shadows(bool shadow);
    
    virtual int
    name() = 0;
	
protected:
	bool shadows;
};

inline void
Material::set_shadows(bool shadow) {
	shadows = shadow;
}


#endif