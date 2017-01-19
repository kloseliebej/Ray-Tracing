#ifndef __TEXTURE__
#define __TEXTURE__

/*
 *  Texture.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include <math.h>

#include "ShadeRec.h"
#include "MyRGBColor.h"

class Texture {	
public:
	
	Texture(void);										
	
	Texture(const Texture& texture); 					
	
	virtual Texture*									
	clone(void) const = 0;	
	
	virtual 											
	~Texture(void);
	
	virtual MyRGBColor																			
	get_color(const ShadeRec& sr) const = 0;
	
protected:
	
	Texture& 											
	operator= (const Texture& rhs);
};

#endif
