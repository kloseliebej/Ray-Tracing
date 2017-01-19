/*
 *  Phong.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/22/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */
//#419begin #type=<3> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include "Phong.h"
#include "World.h"
#include <iostream>
using namespace std;
Phong::Phong(void) 
:	Material(),
	ambient_brdf(new Lambertian),
	diffuse_brdf(new Lambertian),
	specular_brdf(new GlossySpecular),
    specular_brdf2(new PerfectSpecular)
{}

Phong::Phong(const Phong& rhs)
:	Material(rhs) {	
	
	if (rhs.ambient_brdf)
		ambient_brdf = (Lambertian*)rhs.ambient_brdf->clone();
	else
		ambient_brdf = NULL;
	
	if (rhs.diffuse_brdf)
		diffuse_brdf = (Lambertian*)rhs.diffuse_brdf->clone();
	else
		diffuse_brdf = NULL;
	
	if (rhs.specular_brdf)
		specular_brdf = (GlossySpecular*)rhs.specular_brdf->clone();
	else
		specular_brdf = NULL;
    
    if (rhs.specular_brdf2)
        specular_brdf2 = (PerfectSpecular*)rhs.specular_brdf2->clone();
    else
        specular_brdf2 = NULL;
}

Phong::~Phong(void) {
	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
	
	if (specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}
	
    if (specular_brdf2) {
        delete specular_brdf2;
        specular_brdf2 = NULL;
    }
}

Phong&
Phong::operator= (const Phong& p) {
	if (this == &p)
		return (*this);
	
	Material::operator= (p);
	
	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
	
	if (specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}
    
    if (specular_brdf2) {
        delete specular_brdf2;
        specular_brdf2 = NULL;
    }
	
	if (p.ambient_brdf)
		ambient_brdf = (Lambertian*)p.ambient_brdf->clone();
	
	if (p.diffuse_brdf)
		diffuse_brdf = (Lambertian*)p.diffuse_brdf->clone();
	
	if (p.specular_brdf)
		specular_brdf = (GlossySpecular*)p.specular_brdf->clone();
    
    if (p.specular_brdf2)
        specular_brdf2 = (PerfectSpecular*)p.specular_brdf2->clone();

    
    return (*this);
}

Material*
Phong::clone(void) const {
	return (new Phong(*this));
}


MyRGBColor
Phong::shade(ShadeRec& sr) {
	Vector3D wo = -sr.ray.d;
	MyRGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int num_lights = sr.w.lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal * wi;
		
		if (ndotwi > 0.0) {
			
			bool in_shadow = false;
			
			if (sr.w.lights[j]->casts_shadows()) {
				Ray shadowRay(sr.hit_point, wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadowRay, sr);
			}
			
			if (!in_shadow) {
				L += (diffuse_brdf->f(sr, wi, wo) + specular_brdf->f(sr, wi, wo)) * sr.w.lights[j]->L(sr) * ndotwi;
			}
		}
	}
	return (L);
}

MyRGBColor
Phong::area_light_shade(ShadeRec& sr) {
	Vector3D wo = -sr.ray.d;
	MyRGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
    //cout<<"L average = "<<L.average()<<endl;
    Vector3D wi;
    float ndotwi;
	int num_lights = sr.w.lights.size();
	for (int j = 0; j < num_lights; j++) {
		wi = sr.w.lights[j]->get_direction(sr);
		ndotwi = sr.normal * wi;
		
		if (ndotwi > 0.0) {
			bool in_shadow = false;
			if (sr.w.lights[j]->casts_shadows()) {
				Ray shadow_ray(sr.hit_point, wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
			}
			
			if (!in_shadow)
                if(specular_brdf){
				L += (diffuse_brdf->f(sr, wi, wo) + specular_brdf->f(sr, wi, wo)) * sr.w.lights[j]->L(sr) *
				sr.w.lights[j]->G(sr) * ndotwi /
				sr.w.lights[j]->pdf(sr);
                }
            
        }
	}
    /*if(specular_brdf && sr.w.lights[0] && sr.w.lights[1]){
        wi = sr.w.lights[0]->get_direction(sr);
        ndotwi = sr.normal * wi;
        Vector3D wi2 = sr.w.lights[1]->get_direction(sr);
        float ndotwi2 = sr.normal* wi2;
        L += specular_brdf->f(sr, wi, wo) * sr.w.lights[0]->L(sr) *
        sr.w.lights[0]->G(sr) * ndotwi /
        sr.w.lights[0]->pdf(sr);
        L += specular_brdf->f(sr, wi2, wo) * sr.w.lights[1]->L(sr) *
        sr.w.lights[1]->G(sr) * ndotwi2 /
        sr.w.lights[1]->pdf(sr);
    }*/

    return (L);

}

void
Phong::set_ka(const float ka) {
	if (ambient_brdf)
		ambient_brdf->set_kd(ka);
}

void
Phong::set_kd(const float kd) {
	if (diffuse_brdf)
		diffuse_brdf->set_kd(kd);
}

void
Phong::set_ks(const float ks) {
	if (specular_brdf)
		specular_brdf->set_ks(ks);
}

void
Phong::set_ca(const float r, const float g, const float b) {
	if (ambient_brdf)
		ambient_brdf->set_cd(r, g, b);
}

void
Phong::set_cd(const float r, const float g, const float b) {
	if (diffuse_brdf)
		diffuse_brdf->set_cd(r,g,b);
}

void
Phong::set_cs(const float r, const float g, const float b) {
	if (specular_brdf)
		specular_brdf->set_cs(r, g, b);
}

void
Phong::set_exp_s(const float exp_s){
	if (specular_brdf)
		specular_brdf->set_exp(exp_s);

}

void 
Phong::set_k(const float k) {
	if (ambient_brdf)
		ambient_brdf->set_kd(k);
	
	if (diffuse_brdf)
		diffuse_brdf->set_kd(k);
	
	if (specular_brdf)
		specular_brdf->set_ks(k);
}

void
Phong::set_c(const float r, const float g, const float b) {
	if (ambient_brdf)
		ambient_brdf->set_cd(r,g,b);
	
	if (diffuse_brdf)
		diffuse_brdf->set_cd(r,g,b);
	
	if (specular_brdf)
		specular_brdf->set_cs(r,g,b);
}

void
Phong::set_c(const MyRGBColor& c) {
	if (ambient_brdf)
		ambient_brdf->set_cd(c);
	
	if (diffuse_brdf)
		diffuse_brdf->set_cd(c);
	
	if (specular_brdf)
		specular_brdf->set_cs(c);
}

int
Phong::name(){
    return 6;
}
