#ifndef __CYLINDRICAL_MAP__
#define __CYLINDRICAL_MAP__

/*
 *  CylindricalMap.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/28/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Constants.h"
#include "Mapping.h"

class CylindricalMap: public Mapping {		
public:
	
	CylindricalMap(void);									
	
	CylindricalMap(const CylindricalMap& sm);					
	
	CylindricalMap& 											
	operator= (const CylindricalMap& rhs);		
	
	virtual CylindricalMap*									
	clone(void) const;				
	
	~CylindricalMap(void);									
	
	virtual void
	get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
						  const 	int 		xres, 
						  const 	int 		yres, 
						  int& 		row, 
						  int& 		column) const;
};

#endif