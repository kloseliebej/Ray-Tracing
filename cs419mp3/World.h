#ifndef __WORLD__
#define __WORLD__
//#419begin #type=<3> #src=<http://www.raytracegroundup.com/>


// This file contains the declaration of the class World
// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 


#include <vector>

#include "ViewPlane.h"
#include "MyRGBColor.h"
#include "Tracer.h"
#include "GeometricObject.h"
#include "Sphere.h"
#include "Ray.h"
#include "SingleSphere.h"

#include "Camera.h"
#include "Light.h"
#include "Ambient.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv/cv.h>

using namespace std;
using namespace cv;
//class RenderThread; 	//part of skeleton - wxRaytracer.h


class World {	
	public:
	
		ViewPlane					vp;
		MyRGBColor					background_color;
		Tracer*						tracer_ptr;
		Light*   					ambient_ptr;
		Camera*						camera_ptr;		
		Sphere 						sphere;		// for Chapter 3 only
		vector<GeometricObject*>	objects;		
		vector<Light*> 				lights;
        Mat                         imgout;
        int                         num_rays;
		//RenderThread* 				paintArea; 	//connection to skeleton - wxRaytracer.h
			

	public:
	
		World(void);												
		
		~World();
    
        void
        set_imgout(int vres, int hres);
    
		void 
		add_object(GeometricObject* object_ptr);
		
		void 
		add_light(Light* light_ptr); 
		
		void
		set_ambient_light(Light* light_ptr);			
		
		void
		set_camera(Camera* c_ptr);	 

		void 					
		build(void);

		//void
		//render_scene(void) const;
						
		MyRGBColor
		max_to_one(const MyRGBColor& c) const;
		
		MyRGBColor
		clamp_to_color(const MyRGBColor& c) const;
		
		void
		display_pixel(const int row, const int column, const MyRGBColor& pixel_color);

		ShadeRec
		hit_objects(const Ray& ray);
    
        ShadeRec
        hit_bare_bones_objects(const Ray& ray);

        void
        render_scene(void) ;
    
		void
		delete_objects(void);
		
		void 
		delete_lights(void);
};


// ------------------------------------------------------------------ add_object

inline void 
World::add_object(GeometricObject* object_ptr) {  
	objects.push_back(object_ptr);	
}


// ------------------------------------------------------------------ add_light

inline void 
World::add_light(Light* light_ptr) {  
	lights.push_back(light_ptr);
}


// ------------------------------------------------------------------ set_ambient_light

inline void
World::set_ambient_light(Light* light_ptr) {
	ambient_ptr = light_ptr;
}


// ------------------------------------------------------------------ set_camera

inline void
World::set_camera(Camera* c_ptr) {
	camera_ptr = c_ptr;
}

inline void
World::set_imgout(int vres, int hres) {
    imgout = Mat::zeros(vres,hres,CV_8UC3);
}
//#419end
#endif
