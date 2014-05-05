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
            Vec3Df ctemp;
            int nbinter=0;
            Vec3Df c (backgroundColor);
            for (unsigned int m =0; m<2; m++){
                for(unsigned int n=0; n<2; n++){
                    nbinter++;
                    Vec3Df stepX = (float (i+float(m/2)) - screenWidth/2.f)/screenWidth * tanX * rightVector;
                    Vec3Df stepY = (float (j+float(n/2)) - screenHeight/2.f)/screenHeight * tanY * upVector;
                    Vec3Df step = stepX + stepY;
                    Vec3Df dir = direction + step;
                    dir.normalize ();

                    Vec3Df intersectionPoint;
                    float smallestIntersectionDistance = 1000000.f;
                    Vec3Df currentColor = backgroundColor;
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
                                float  b0;
                                float  b1;
                                float  b2;
                                //Declaration des variabmes pour les avoir en eterne et calculer l'intersection triangle et la brdf

                                Vec3Df lightpos = scene->getLights()[0].getPos();
                                float diffuse = o.getMaterial().getDiffuse();
                                float specular = o.getMaterial().getSpecular();
                                bool intersection = ray.intersectTriangle(intersectionPoint, p0, p1, p2, b0, b1, b2);//Vertices) ;Omb
                                if (intersection) {
                                    float f = ray.brdfPhong(intersectionPoint, n0, n1, n2,b0, b1, b2, diffuse, specular, lightpos);
                                    float intersectionDistance = Vec3Df::squaredDistance ( intersectionPoint + o.getTrans (),
                                                                                           camPos);
                                    if (intersectionDistance < smallestIntersectionDistance) {


                                       // Vec3Df Omb = lightpos - intersectionPoint;
                                       // if (ray.intersectTriangle(intersectionPoint, p0, p1, p2, n0, n1, n2, diffuse, specular, lightpos)!=1000){//Si tu lance un rayon d'ici vers la lumiere et que tu croise un autre triangle alors tu met ce point en noir
                                       //     ctemp (255.f, 255.f, 255.f);
                                       // }
                                       // else{
                                            currentColor = f * o.getMaterial().getColor();// * 255.f;
                                        //c = f * o.getMaterial().getColor() * 255.f;
                                        //c = Vec3Df(Intersection, Intersection, Intersection);
                                        smallestIntersectionDistance = intersectionDistance;
                                       // }
                                    }
                                }
                            }
                        }

                    }
                    ctemp = ctemp + currentColor;

                }

            }
            c = c + ctemp/float(4)*255.f;
            image.setPixel (i, j, qRgb (clamp (c[0], 0, 255), clamp (c[1], 0, 255), clamp (c[2], 0, 255)));

        }

    }

    progressDialog.setValue (100);
    return image;
}
