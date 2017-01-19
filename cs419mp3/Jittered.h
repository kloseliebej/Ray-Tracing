#ifndef __JITTERED__
#define __JITTERED__

/*
 *  Jittered.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/13/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Sampler.h"

class Jittered: public Sampler {

public:
	
	Jittered(void);
	
	Jittered(const int num_samples);
	
	Jittered(const Jittered& js);
	
	Jittered&
	operator= (const Jittered& rhs);
	
	Jittered*
	clone(void) const;
	
	~Jittered(void);
	
private:
	
	virtual void
	generate_samples(void);
	
};

#endif