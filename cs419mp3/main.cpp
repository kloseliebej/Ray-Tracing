//
//  main.cpp
//  cs419mp3
//
//  Created by Yiwei Li on 4/10/16.
//  Copyright © 2016 Yiwei Li. All rights reserved.
//
#include "GlassOfWater.h"
#include "Dielectric.h"
#include "OpenCylinder.h"
#include "CylindricalMap.h"
#include "RectangularMap.h"
#include "SphericalMap.h"
#include "ImageTexture.h"
#include "LightProbe.h"
#include "Image.h"
#include "Transparent.h"
#include "GlossyReflector.h"
#include "Regular.h"
#include "BeveledCylinder.h"
#include "PlaneChecker.h"
#include "SolidCylinder.h"
#include "Reflective.h"
#include "Whitted.h"
#include "Instance.h"
#include "AmbientOccluder.h"
#include "Rectangle.h"
#include "Checker3D.h"
#include "SV_Matte.h"
#include "Box.h"
#include "AreaLight.h"
#include "Emissive.h"
#include "AreaLighting.h"
#include "FlatMeshTriangle.h"
#include "MeshTriangle.h"
#include <ctime>
#include "PointLight.h"
#include "Phong.h"
#include "Grid.h"
#include "RayCast.h"
#include "MultiJittered.h"
#include "Mesh.h"
#include "Camera.h"
#include "Triangle.h"
#include "MyRGBColor.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Sphere.h"
#include "World.h"

#include "Plane.h"
#include "Sphere.h"
#include "SingleSphere.h"
#include "MultipleObjects.h"
#include "RayCast.h"
#include "Pinhole.h"
#include "Directional.h"
#include "Matte.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"
#include "Ray.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv/cv.h>
#include <iostream>
using namespace std;
using namespace cv;

MyRGBColor yellow(1, 1, 0);										// yellow
MyRGBColor brown(0.71, 0.40, 0.16);								// brown
MyRGBColor darkGreen(0.0, 0.41, 0.41);							// darkGreen
MyRGBColor orange(1, 0.75, 0);									// orange
MyRGBColor green(0, 0.6, 0.3);									// green
MyRGBColor lightGreen(0.65, 1, 0.30);								// light green
MyRGBColor darkYellow(0.61, 0.61, 0);								// dark yellow
MyRGBColor lightPurple(0.65, 0.3, 1);								// light purple
MyRGBColor darkPurple(0.5, 0, 1);									// dark purple
MyRGBColor grey(0.25);											// grey


int main(int argc, const char * argv[]) {
    int start_s=clock();
    char window_name1[] = "Output Image";
    
    World theworld;
    World* w = &theworld;
    int vres = 600;
    int hres = 600;
    theworld.set_imgout(vres, hres);

    //set view plane///
    
    //////////////////////////////////////////////////////////////////////////////////////
    int num_samples = 256;
    
    theworld.vp.set_hres(600);
    theworld.vp.set_vres(600);
    theworld.vp.set_samples(num_samples);
    theworld.vp.set_max_depth(5);
    
    theworld.tracer_ptr = new AreaLighting(w);
    theworld.background_color = MyRGBColor(0.5);
    
    Pinhole* pinholePtr = new Pinhole;
    pinholePtr->set_eye(100, 100, 300);
    pinholePtr->set_lookat(-0.2, 1.0, 0);
    pinholePtr->set_view_distance(12000.0);
    pinholePtr->compute_uvw();
    theworld.set_camera(pinholePtr);
    
    Ambient* ambient_ptr = new Ambient;
    ambient_ptr->scale_radiance(0.5);
    theworld.set_ambient_light(ambient_ptr);

    Directional* light_ptr = new Directional;
    light_ptr->set_direction(0, 0, 1);
    light_ptr->scale_radiance(1.5);
    theworld.add_light(light_ptr);
    
    PointLight* light_ptr1 = new PointLight;
    light_ptr1->set_location(0, 500, -100);
    light_ptr1->scale_radiance(4.5);
    light_ptr1->set_shadows(true);
    theworld.add_light(light_ptr1);
    
    // cylinder
    
    Transparent* glass_ptr = new Transparent;
    glass_ptr->set_ks(0.2);
    glass_ptr->set_exp(2000.0);
    glass_ptr->set_ior(0.75);
    glass_ptr->set_kr(0.1);
    glass_ptr->set_kt(0.9);
    
    float exp = 10000.0;
    GlossyReflector* glossy_ptr2 = new GlossyReflector;
    glossy_ptr2->set_samples(num_samples, exp);
    glossy_ptr2->set_ka(0.0);
    glossy_ptr2->set_kd(0.0);
    glossy_ptr2->set_ks(0.0);
    glossy_ptr2->set_exp(exp);
    glossy_ptr2->set_cd(black);
    glossy_ptr2->set_kr(0.9);
    glossy_ptr2->set_exponent(exp);
    glossy_ptr2->set_cr(0.5, 1.0, 0);
    
    Instance* cylinder_ptr = new Instance(new SolidCylinder(-2.5, 6, 1.5));
    cylinder_ptr->translate(-3.5, -2, 0);
    cylinder_ptr->transform_texture(false);
    cylinder_ptr->set_material(glossy_ptr2);
    theworld.add_object(cylinder_ptr);
    
    Sphere* sphere_ptr1 = new Sphere(Point3D(-4.0, 0, -5.0), 3.0);
    sphere_ptr1->set_material(glass_ptr);
    theworld.add_object(sphere_ptr1);
    
    Sphere* sphere_ptr3 = new Sphere(Point3D(2.0, 0, 3.0), 1.0);
    sphere_ptr3->set_material(glass_ptr);
    theworld.add_object(sphere_ptr3);

    
    
    // box
    
    Checker3D* checker_ptr4 = new Checker3D;
    checker_ptr4->set_size(1.0);
    checker_ptr4->set_color1(black);
    checker_ptr4->set_color2(white);
    
    SV_Matte* sv_matte_ptr4 = new SV_Matte;
    sv_matte_ptr4->set_ka(0.75);
    sv_matte_ptr4->set_kd(0.75);
    sv_matte_ptr4->set_cd(checker_ptr4);
    
    Box* box_ptr = new Box(Point3D(0, -4.5, -2), Point3D(4, -0.5, 2));
    box_ptr->set_material(sv_matte_ptr4);
    theworld.add_object(box_ptr);
    
    
    // sphere
    
    Image* image_ptr = new Image;
    image_ptr->read_ppm_file("EarthHighRes.ppm");
    SphericalMap* map_ptr = new SphericalMap;
    ImageTexture* texture_ptr = new ImageTexture;
    texture_ptr->set_image(image_ptr);
    texture_ptr->set_mapping(map_ptr);
  
    SV_Matte* sv_matte_ptr = new SV_Matte;
    sv_matte_ptr->set_ka(0.2);
    sv_matte_ptr->set_kd(0.8);
    sv_matte_ptr->set_cd(texture_ptr);
   
    Sphere*	sphere_ptr = new Sphere;
    sphere_ptr->set_material(sv_matte_ptr);
    
    Instance* earth_ptr = new Instance(sphere_ptr);
    earth_ptr->transform_texture(true);
    earth_ptr->translate(1,0.5,0);
    earth_ptr->rotate_y(60);
    theworld.add_object(earth_ptr);
    
    //glossy sphere
    exp = 100.0;
    GlossyReflector* glossy_ptr = new GlossyReflector;
    glossy_ptr->set_samples(num_samples, exp);
    glossy_ptr->set_ka(0.0);
    glossy_ptr->set_kd(0.0);
    glossy_ptr->set_ks(0.0);
    glossy_ptr->set_exp(exp);
    glossy_ptr->set_cd(1.0, 1.0, 0.3);
    glossy_ptr->set_kr(0.9);
    glossy_ptr->set_exponent(exp);
    glossy_ptr->set_cr(1.0, 1.0, 0.3);  // lemon
    
    Sphere* sphere_ptr2 = new Sphere(Point3D(4, -1.5, -7), 3);
    sphere_ptr2->set_material(glossy_ptr);
    theworld.add_object(sphere_ptr2);
    
    
    // ground plane
    Checker3D* checker_ptr = new Checker3D;
    checker_ptr->set_size(4.0);
    checker_ptr->set_color1(0,0.3,0.6);
    checker_ptr->set_color2(0,0,0.4);
    
    SV_Matte* sv_matte_ptr5 = new SV_Matte;
    sv_matte_ptr5->set_ka(1);
    sv_matte_ptr5->set_kd(0.4);
    sv_matte_ptr5->set_cd(checker_ptr);
    
    Matte* matte_ptr = new Matte;
    matte_ptr->set_ka(0.15);
    matte_ptr->set_kd(0.75);
    matte_ptr->set_cd(0,0,0.4);
    
    Plane* plane_ptr = new Plane(Point3D(0, -4.5, 0), Normal(0, 1, 0));
    plane_ptr->set_material(matte_ptr);
    theworld.add_object(plane_ptr);

    
    ////////////////////////////////////////////////////////////////////////////////////////
    theworld.camera_ptr->render_scene(theworld);
    namedWindow( window_name1, WINDOW_AUTOSIZE );
    imshow("Output Image",theworld.imgout);
    int stop_s=clock();
    cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
    cout << "Rays: " << theworld.num_rays<<endl;
    waitKey();
    return 0;

}
/*
 int num_samples = 16;
 
 theworld.vp.set_hres(600);
 theworld.vp.set_vres(600);
 theworld.vp.set_samples(num_samples);
 theworld.vp.set_max_depth(5);
 
 theworld.background_color = MyRGBColor(0.0, 0.3, 0.25);
 
 theworld.tracer_ptr = new AreaLighting(w);
 
 Ambient* ambient_ptr = new Ambient;
 ambient_ptr->scale_radiance(0.25);
 theworld.set_ambient_light(ambient_ptr);
 
 Pinhole* pinhole_ptr = new Pinhole;
 pinhole_ptr->set_eye(-8, 5.5, 40);
 pinhole_ptr->set_lookat(1, 4, 0);
 pinhole_ptr->set_view_distance(2400.0);
 pinhole_ptr->compute_uvw();
 theworld.set_camera(pinhole_ptr);
 
 
 // point light
 
 PointLight* light_ptr1 = new PointLight;
 light_ptr1->set_location(40, 50, 0);
 light_ptr1->scale_radiance(4.5);
 light_ptr1->set_shadows(true);
 theworld.add_light(light_ptr1);
 
 
 // point light
 
 PointLight* light_ptr2 = new PointLight;
 light_ptr2->set_location(-10, 20, 10);
 light_ptr2->scale_radiance(4.5);
 light_ptr2->set_shadows(true);
 theworld.add_light(light_ptr2);
 
 
 // directional light
 
 Directional* light_ptr3 = new Directional;
 light_ptr3->set_direction(-1, 0, 0);
 light_ptr3->scale_radiance(4.5);
 light_ptr3->set_shadows(true);
 theworld.add_light(light_ptr3);
 
 
 // transparent sphere
 
 Transparent* glass_ptr = new Transparent;
 glass_ptr->set_ks(0.2);
 glass_ptr->set_exp(2000.0);
 glass_ptr->set_ior(0.75);
 glass_ptr->set_kr(0.1);
 glass_ptr->set_kt(0.9);
 
 Sphere* sphere_ptr1 = new Sphere(Point3D(0.0, 4.5, 0.0), 3.0);
 sphere_ptr1->set_material(glass_ptr);
 theworld.add_object(sphere_ptr1);
 
 
 // red sphere
 
 Reflective*	reflective_ptr = new Reflective;
 reflective_ptr->set_ka(0.3);
 reflective_ptr->set_kd(0.3);
 reflective_ptr->set_cd(red);
 reflective_ptr->set_ks(0.2);
 reflective_ptr->set_exp(2000.0);
 reflective_ptr->set_kr(0.25);
 
 float exp2 = 100000.0;
 GlossyReflector* glossy_ptr2 = new GlossyReflector;
 glossy_ptr2->set_cd(0, 0.5, 0.25);
 glossy_ptr2->set_ka(0.2);
 glossy_ptr2->set_kd(0.3);
 glossy_ptr2->set_ks(0.0);
 glossy_ptr2->set_exp(exp2);
 glossy_ptr2->set_kr(0.5);
 glossy_ptr2->set_samples(num_samples, exp2);
 
 float exp = 100.0;
 GlossyReflector* glossy_ptr = new GlossyReflector;
 glossy_ptr->set_samples(num_samples, exp);
 glossy_ptr->set_ka(0.0);
 glossy_ptr->set_kd(0.0);
 glossy_ptr->set_ks(0.0);
 glossy_ptr->set_exp(exp);
 glossy_ptr->set_cd(1.0, 1.0, 0.3);
 glossy_ptr->set_kr(0.9);
 glossy_ptr->set_exponent(exp);
 glossy_ptr->set_cr(1.0, 1.0, 0.3);  // lemon
 
 Sphere* sphere_ptr2 = new Sphere(Point3D(4, 4, -6), 3);
 sphere_ptr2->set_material(glossy_ptr);
 theworld.add_object(sphere_ptr2);
 
 
 Checker3D* checker_ptr = new Checker3D;
 checker_ptr->set_size(4);
 checker_ptr->set_color1(0.75);
 checker_ptr->set_color2(white);
 
 SV_Matte* sv_matte_ptr = new SV_Matte;
 sv_matte_ptr->set_ka(0.5);
 sv_matte_ptr->set_kd(0.35);
 sv_matte_ptr->set_cd(checker_ptr);
 
 // rectangle
 
 Rectangle* rectangle_ptr = new Rectangle(Point3D(-20, -0.001, -100), Vector3D(0, 0, 120), Vector3D(40, 0, 0));
 rectangle_ptr->set_material(sv_matte_ptr);
 theworld.add_object(rectangle_ptr);

*/






/*
 int num_samples = 25;
 
 theworld.vp.set_hres(600);
 theworld.vp.set_vres(600);
 theworld.vp.set_samples(num_samples);
 theworld.vp.set_max_depth(1);
 
 theworld.tracer_ptr = new AreaLighting(w);
 
 Pinhole* pinhole_ptr = new Pinhole;
 pinhole_ptr->set_eye(-150, 75, 500);
 pinhole_ptr->set_lookat(-6, 50, 0);
 pinhole_ptr->set_view_distance(3000);
 pinhole_ptr->compute_uvw();
 theworld.set_camera(pinhole_ptr);
 
 
 PointLight* light_ptr1 = new PointLight;
 light_ptr1->set_location(250, 500, 250);
 light_ptr1->scale_radiance(2.0);
 light_ptr1->set_shadows(true);
 theworld.add_light(light_ptr1);
 
 float exp = 1.0;  		// for Figure 25.30(a)
 //	float exp = 10.0;  		// for Figure 25.30(b)
 //	float exp = 100.0;  	// for Figure 25.30(c)
 //	float exp = 1000.0;  	// for Figure 25.30(d)
 //	float exp = 10000.0;  	// for Figure 25.30(e)
 //	float exp = 100000.0;  	// for Figure 25.30(f)
 
 GlossyReflector* glossy_ptr = new GlossyReflector;
 glossy_ptr->set_samples(num_samples, exp);
 glossy_ptr->set_ka(0.0);
 glossy_ptr->set_kd(0.0);
 glossy_ptr->set_ks(0.0);
 glossy_ptr->set_exp(exp);
 glossy_ptr->set_cd(1.0, 1.0, 0.3);
 glossy_ptr->set_kr(0.9);
 glossy_ptr->set_exponent(exp);
 glossy_ptr->set_cr(1.0, 1.0, 0.3);  // lemon
 
 Sphere* sphere_ptr1 = new Sphere(Point3D(-6, 55, 0), 40);
 sphere_ptr1->set_material(glossy_ptr);
 theworld.add_object(sphere_ptr1);
 
 
 //cylinder
 
 Matte* matte_ptr = new Matte;
 matte_ptr->set_ka(0.15);
 matte_ptr->set_kd(0.75);
 matte_ptr->set_cd(0.5, 1.0, 0.5);   // green
 
 double bottom = -100;
 double top = 15;
 double radius = 30;
 Instance* cylinder_ptr = new Instance(new SolidCylinder(bottom, top, radius));
 cylinder_ptr->translate(-6, 0, 0);
 cylinder_ptr->set_material(matte_ptr);
 theworld.add_object(cylinder_ptr);
 
 
 Image* image_ptr = new Image;
 image_ptr->read_ppm_file("uffizi_probe_small.ppm");  // for testing
 //	image_ptr->read_ppm_file("uffizi_probe_large.ppm");  // for production
 
 
 LightProbe* light_probe_ptr = new LightProbe;
 light_probe_ptr->set_map_type(panoramic);
 
 ImageTexture* image_texture_ptr = new ImageTexture(image_ptr);
 image_texture_ptr->set_mapping(light_probe_ptr);
 
 SV_Matte* sv_matte_ptr = new SV_Matte;
 sv_matte_ptr->set_ka(1);
 sv_matte_ptr->set_kd(0.85);
 sv_matte_ptr->set_cd(image_texture_ptr);
 
 Sphere* unit_sphere_ptr = new Sphere;
 unit_sphere_ptr->set_shadows(false);
 
 Instance* sphere_ptr2 = new Instance(unit_sphere_ptr);
 sphere_ptr2->transform_texture(true);
 sphere_ptr2->scale(1000000.0);
 sphere_ptr2->set_material(sv_matte_ptr);
 theworld.add_object(sphere_ptr2);

*/









/*
 int num_samples = 100;
 
 theworld.vp.set_hres(400);
 theworld.vp.set_vres(400);
 theworld.vp.set_samples(num_samples);
 theworld.vp.set_max_depth(1);
 
 theworld.background_color = MyRGBColor(0.8, 0.9, 1);
 
 theworld.tracer_ptr = new AreaLighting(w);
 
 Ambient* ambient_ptr = new Ambient;
 ambient_ptr->scale_radiance(0.5);
 theworld.set_ambient_light(ambient_ptr);
 
 Pinhole* pinhole_ptr = new Pinhole;
 
 // view with checker
 
 pinhole_ptr->set_eye(5, 0, 20);
 pinhole_ptr->set_view_distance(3000);
 pinhole_ptr->set_lookat(0);
 pinhole_ptr->compute_uvw();
 theworld.set_camera(pinhole_ptr);
 
 // Point light
 
 PointLight* light_ptr1 = new PointLight;
 light_ptr1->set_location(10, 30, 20);
 light_ptr1->scale_radiance(5.0);
 light_ptr1->set_shadows(false);
 theworld.add_light(light_ptr1);
 
 
 // glossy reflector sphere
 
 float exp = 100.0;
 
 GlossyReflector* glossy_ptr = new GlossyReflector;
 glossy_ptr->set_samples(num_samples, exp);
 glossy_ptr->set_ka(0.0);
 glossy_ptr->set_kd(0.0);
 glossy_ptr->set_ks(0.0);
 glossy_ptr->set_exp(exp);
 glossy_ptr->set_cd(black);
 glossy_ptr->set_kr(0.8);
 glossy_ptr->set_exponent(exp);
 glossy_ptr->set_cr(white);
 
 Sphere* sphere_ptr = new Sphere;
 sphere_ptr->set_material(glossy_ptr);
 theworld.add_object(sphere_ptr);
 
 
 // ground plane with checker
 
 Checker3D* checker_ptr = new Checker3D;
 checker_ptr->set_size(4.0);
 checker_ptr->set_color1(white);
 checker_ptr->set_color2(black);
 
 SV_Matte* sv_matte_ptr = new SV_Matte;
 sv_matte_ptr->set_ka(1);
 sv_matte_ptr->set_kd(0.4);
 sv_matte_ptr->set_cd(checker_ptr);
 
 Plane* plane_ptr = new Plane(Point3D(0, -5.01, 0), Normal(0, 1, 0));
 plane_ptr->set_material(sv_matte_ptr);
 theworld.add_object(plane_ptr);
*/








/*
 int num_samples = 16;
 
 theworld.vp.set_hres(600);
 theworld.vp.set_vres(600);
 theworld.vp.set_samples(num_samples);
 
 theworld.tracer_ptr = new AreaLighting(w);
 theworld.background_color = MyRGBColor(0.5);
 
 Pinhole* pinholePtr = new Pinhole;
 pinholePtr->set_eye(100, 100, 300);
 pinholePtr->set_lookat(-0.2, 1.0, 0);
 pinholePtr->set_view_distance(12000.0);
 pinholePtr->compute_uvw();
 theworld.set_camera(pinholePtr);
 
 Directional* light_ptr = new Directional;
 light_ptr->set_direction(0, 0, 1);
 light_ptr->scale_radiance(1.5);
 theworld.add_light(light_ptr);
 
 
 // sphere
 
 Checker3D* checker_pt1 = new Checker3D;
 checker_pt1->set_size(1.0);
 checker_pt1->set_color1(black);
 checker_pt1->set_color2(white);
 
 SV_Matte* sv_matte_ptr1 = new SV_Matte;
 sv_matte_ptr1->set_ka(0.75);
 sv_matte_ptr1->set_kd(0.75);
 sv_matte_ptr1->set_cd(checker_pt1);
 
 
 // cylinder
 
 Checker3D* checker_ptr2 = new Checker3D;
 checker_ptr2->set_size(1.0);
 checker_ptr2->set_color1(black);
 checker_ptr2->set_color2(white);
 
 SV_Matte* sv_matte_ptr2 = new SV_Matte;
 sv_matte_ptr2->set_ka(0.75);
 sv_matte_ptr2->set_kd(0.75);
 sv_matte_ptr2->set_cd(checker_ptr2);
 
 Instance* cylinder_ptr = new Instance(new SolidCylinder(-2.5, 4.0, 1.95));
 cylinder_ptr->translate(-3.5, 0, 0);
 cylinder_ptr->transform_texture(false);
 cylinder_ptr->set_material(sv_matte_ptr2);
 theworld.add_object(cylinder_ptr);
 
 
 // box
 
 Checker3D* checker_ptr4 = new Checker3D;
 checker_ptr4->set_size(1.0);
 checker_ptr4->set_color1(black);
 checker_ptr4->set_color2(white);
 
 SV_Matte* sv_matte_ptr4 = new SV_Matte;
 sv_matte_ptr4->set_ka(0.75);
 sv_matte_ptr4->set_kd(0.75);
 sv_matte_ptr4->set_cd(checker_ptr4);
 
 Box* box_ptr = new Box(Point3D(0, -1.0, -2), Point3D(4, 3, 2));
 box_ptr->set_material(sv_matte_ptr4);
 theworld.add_object(box_ptr);
 
 
 // image:
 
 Image* image_ptr = new Image;
 //	image_ptr->read_ppm_file("EarthLowRes.ppm");
 image_ptr->read_ppm_file("EarthHighRes.ppm");
 
 
 // mapping:
 
 SphericalMap* map_ptr = new SphericalMap;
 
 
 // image based texture:
 
 ImageTexture* texture_ptr = new ImageTexture;
 texture_ptr->set_image(image_ptr);
 texture_ptr->set_mapping(map_ptr);
 
 
 // textured material:
 
 SV_Matte* sv_matte_ptr = new SV_Matte;
 sv_matte_ptr->set_ka(0.2);
 sv_matte_ptr->set_kd(0.8);
 sv_matte_ptr->set_cd(texture_ptr);
 
 
 // generic sphere:
 
 Sphere*	sphere_ptr = new Sphere(Point3D(2, 5, 0), 2);
 sphere_ptr->set_material(sv_matte_ptr);
 
 
 // rotated sphere
 
 Instance* earth_ptr = new Instance(sphere_ptr);
 earth_ptr->transform_texture(true);
 earth_ptr->rotate_y(60);
 theworld.add_object(earth_ptr);
 //    Sphere* sphere_ptr = new Sphere(Point3D(2, 5, 0), 2);
 //    sphere_ptr->set_material(sv_matte_ptr);
 //    theworld.add_object(sphere_ptr);
 //
 
 
 // ground plane
 
 Checker3D* checker_ptr5 = new Checker3D;
 checker_ptr5->set_size(1.5);
 checker_ptr5->set_color1(0.35);
 checker_ptr5->set_color2(0.5);
 
 SV_Matte* sv_matte_ptr5 = new SV_Matte;
 sv_matte_ptr5->set_ka(0.75);
 sv_matte_ptr5->set_kd(0.75);
 sv_matte_ptr5->set_cd(checker_ptr5);
 
 Plane* plane_ptr = new Plane(Point3D(0, -4.5, 0), Normal(0, 1, 0));
 plane_ptr->set_material(sv_matte_ptr5);
 theworld.add_object(plane_ptr);

*/






/*
	int num_samples = 16;
 
 theworld.vp.set_hres(400);
 theworld.vp.set_vres(400);
 theworld.vp.set_samples(num_samples);
 
 theworld.background_color = black;
 
 theworld.tracer_ptr = new AreaLighting(w);
 
 Pinhole* camera_ptr = new Pinhole;
 camera_ptr->set_eye(0, 0, -65);
 camera_ptr->set_lookat(0.0);
 camera_ptr->set_view_distance(21000.0);
 camera_ptr->compute_uvw();
 camera_ptr->set_zoom(4.0/7.0);
 theworld.set_camera(camera_ptr);
 
 
 //    	Directional* light_ptr = new Directional;
 //    	light_ptr->set_direction(-0.25, 0.4, -1);
 //    	light_ptr->scale_radiance(2.5);
 //    	theworld.add_light(light_ptr);
 
 
 // image:
 
 Image* image_ptr = new Image;
 //	image_ptr->read_ppm_file("EarthLowRes.ppm");
 image_ptr->read_ppm_file("EarthHighRes.ppm");
 
 
 // mapping:
 
 SphericalMap* map_ptr = new SphericalMap;
 
 
 // image based texture:
 
 ImageTexture* texture_ptr = new ImageTexture;
 texture_ptr->set_image(image_ptr);
 texture_ptr->set_mapping(map_ptr);
 
 
 // textured material:
 
 SV_Matte* sv_matte_ptr = new SV_Matte;
 sv_matte_ptr->set_ka(0.2);
 sv_matte_ptr->set_kd(0.8);
 sv_matte_ptr->set_cd(texture_ptr);
 
 
 // generic sphere:
 
 Sphere*	sphere_ptr = new Sphere;
 sphere_ptr->set_material(sv_matte_ptr);
 theworld.add_object(sphere_ptr);
 
 // rotated sphere
 
 Instance* earth_ptr = new Instance(sphere_ptr);
 earth_ptr->rotate_y(60);
 //theworld.add_object(earth_ptr);

*/