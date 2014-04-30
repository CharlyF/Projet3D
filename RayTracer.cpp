// *********************************************************
// Ray Tracer Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2012 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "RayTracer.h"
#include "Ray.h"
#include "Scene.h"
#include <QProgressDialog>

static RayTracer * instance = NULL;

RayTracer * RayTracer::getInstance () {
    if (instance == NULL)
        instance = new RayTracer ();
    return instance;
}

void RayTracer::destroyInstance () {
    if (instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

inline int clamp (float f, int inf, int sup) {
    int v = static_cast<int> (f);
    return (v < inf ? inf : (v > sup ? sup : v));
}

// POINT D'ENTREE DU PROJET.
// Le code suivant ray trace uniquement la boite englobante de la scene.
// Il faut remplacer ce code par une veritable raytracer
QImage RayTracer::render (const Vec3Df & camPos,
                          const Vec3Df & direction,
                          const Vec3Df & upVector,
                          const Vec3Df & rightVector,
                          float fieldOfView,
                          float aspectRatio,
                          unsigned int screenWidth,
                          unsigned int screenHeight) {
    QImage image (QSize (screenWidth, screenHeight), QImage::Format_RGB888);
    Scene * scene = Scene::getInstance ();
    const BoundingBox & bbox = scene->getBoundingBox ();
    const Vec3Df & minBb = bbox.getMin ();
    const Vec3Df & maxBb = bbox.getMax ();
    const Vec3Df rangeBb = maxBb - minBb;
    QProgressDialog progressDialog ("Raytracing...", "Cancel", 0, 100);
    progressDialog.show ();

    for (unsigned int i = 0; i < screenWidth; i++) {
        progressDialog.setValue ((100*i)/screenWidth);
        for (unsigned int j = 0; j < screenHeight; j++) {
            float tanX = tan (fieldOfView)*aspectRatio;
            float tanY = tan (fieldOfView);
            Vec3Df stepX = (float (i) - screenWidth/2.f)/screenWidth * tanX * rightVector;
            Vec3Df stepY = (float (j) - screenHeight/2.f)/screenHeight * tanY * upVector;
            Vec3Df step = stepX + stepY;
            Vec3Df dir = direction + step;
            dir.normalize ();
            Vec3Df intersectionPoint;
            float smallestIntersectionDistance = 1000000.f;
            Vec3Df c (backgroundColor);
            for (unsigned int k = 0; k < scene->getObjects().size(); k++) {
                const Object & o = scene->getObjects()[k];
                Ray ray (camPos-o.getTrans(), dir);
                if (ray.intersect(o.getBoundingBox(), intersectionPoint)){
                    std::vector<Vertex> Vertices = o.getMesh().getVertices();
                    std::vector<Triangle> triangles = o.getMesh().getTriangles();

                    for (unsigned int l = 0; l< triangles.size();l++){
                        Triangle t = triangles[l];
                        Vec3Df p0 = Vertices[t.getVertex(0)].getPos();
                        Vec3Df p1 = Vertices[t.getVertex(1)].getPos();
                        Vec3Df p2 = Vertices[t.getVertex(2)].getPos();
                        Vec3Df n0 = Vertices[t.getVertex(0)].getNormal();
                        Vec3Df n1 = Vertices[t.getVertex(1)].getNormal();
                        Vec3Df n2 = Vertices[t.getVertex(2)].getNormal();
                        Vec3Df lightpos = scene->getLights()[0].getPos();
                        float diffuse = o.getMaterial().getDiffuse();
                        float specular = o.getMaterial().getSpecular();
                        float Intersection = ray.intersectTriangle(t , intersectionPoint, p0, p1, p2, diffuse,specular, n0, n1, n2, lightpos);//Vertices) ;

                        if (Intersection!=1000) {
                            //float f = ray.brdfPhong(t ,intersectionPoint,p0, p1, p2, diffuse);
                           float intersectionDistance = Vec3Df::squaredDistance ( intersectionPoint + o.getTrans (),
                                                                           camPos);
                            if (intersectionDistance < smallestIntersectionDistance) {
                                //Vec3Df tmp (1,1,1);
                                c = Intersection * o.getMaterial().getColor() * 255.f;
                                //c = Vec3Df(Intersection, Intersection, Intersection);
                                smallestIntersectionDistance = intersectionDistance;
                                //std::cout << Intersection << std::endl;
                            }
                        }
                    }
                }

            }
            image.setPixel (i, j, qRgb (clamp (c[0], 0, 255), clamp (c[1], 0, 255), clamp (c[2], 0, 255)));

        }

    }

    progressDialog.setValue (100);
    return image;
}
