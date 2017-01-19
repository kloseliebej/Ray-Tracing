/*
 *  ConcaveLens.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 10/27/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#ifndef __CONCAVE_LENS__
#define __CONCAVE_LENS__
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This file contains the declaration of the class ConcaveLens
// It consists of two concave part spheres and a convex part cylinder

// The parameters are:
//						radius 			
//						thickness
//						min_distance:   the minimum distance between the curved surfaces
//										at the center

// it's horizontal with the (x, z) plane through the center

#include "Compound.h"

//------------------------------------------------------------------------- class ConcaveLens

class ConcaveLens: public Compound {
public:
	
	ConcaveLens(const double radius, const double _thickness, const double _min_distance);
	
	ConcaveLens(const ConcaveLens& cl); 					
	
	virtual ConcaveLens* 								
	clone(void) const;
	
	virtual ConcaveLens& 						
	operator= (const ConcaveLens& rhs);		
	
	virtual 								
	~ConcaveLens(void); 
	
	virtual BBox 
	get_bounding_box(void);
	
	virtual bool 																						 
	hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	
private:
	
	float 		lens_radius; 
	float 		thickness; 
	float 		min_distance;
	BBox		bbox;
};

#endif
