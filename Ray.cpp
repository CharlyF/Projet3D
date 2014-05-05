// *********************************************************
// Ray Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "Ray.h"

using namespace std;

static const unsigned int NUMDIM = 3, RIGHT = 0, LEFT = 1, MIDDLE = 2;

bool Ray::intersect (const BoundingBox & bbox, Vec3Df & intersectionPoint) const {
    const Vec3Df & minBb = bbox.getMin ();
    const Vec3Df & maxBb = bbox.getMax ();
    bool inside = true;
    unsigned int  quadrant[NUMDIM];
    register unsigned int i;
    unsigned int whichPlane;
    Vec3Df maxT;
    Vec3Df candidatePlane;
    
    for (i=0; i<NUMDIM; i++)
        if (origin[i] < minBb[i]) {
            quadrant[i] = LEFT;
            candidatePlane[i] = minBb[i];
            inside = false;
        } else if (origin[i] > maxBb[i]) {
            quadrant[i] = RIGHT;
            candidatePlane[i] = maxBb[i];
            inside = false;
        } else	{
            quadrant[i] = MIDDLE;
        }

    if (inside)	{
        intersectionPoint = origin;
        return (true);
    }

    for (i = 0; i < NUMDIM; i++)
        if (quadrant[i] != MIDDLE && direction[i] !=0.)
            maxT[i] = (candidatePlane[i]-origin[i]) / direction[i];
        else
            maxT[i] = -1.;

    whichPlane = 0;
    for (i = 1; i < NUMDIM; i++)
        if (maxT[whichPlane] < maxT[i])
            whichPlane = i;

    if (maxT[whichPlane] < 0.) return (false);
    for (i = 0; i < NUMDIM; i++)
        if (whichPlane != i) {
            intersectionPoint[i] = origin[i] + maxT[whichPlane] *direction[i];
            if (intersectionPoint[i] < minBb[i] || intersectionPoint[i] > maxBb[i])
                return (false);
        } else {
            intersectionPoint[i] = candidatePlane[i];
        }
    return (true);
}

bool Ray::intersectTriangle (Vec3Df & intersectionPoint, Vec3Df p0, Vec3Df p1, Vec3Df p2, float & b0, float & b1, float & b2) const {
    Vec3Df e0 = p1-p0;
    Vec3Df e1 = p2-p0;
    Vec3Df n = Vec3Df::crossProduct(e0,e1);
    n.normalize();
    Vec3Df q = Vec3Df::crossProduct(direction, e1);
    float a = Vec3Df::dotProduct(e0, q);
    if (Vec3Df::dotProduct(n,direction)>=0 || abs(a)<0.0 ){
        return false;
    }
    Vec3Df s = (origin - p0)/a;
    Vec3Df r = Vec3Df::crossProduct(s, e0);
    b0 = Vec3Df::dotProduct(s,q);
    b1 =Vec3Df::dotProduct(r,direction);
    b2 = 1-b0-b1;
    if (b0<0 || b1<0 || b2<0){
        return false;
    }
    float k = Vec3Df::dotProduct(r,e1);
    if (k>=0) {
        intersectionPoint = b2*p0+b0*p1+b1*p2;
        return true;
    }
    return false;
}
float Ray::brdfPhong (Vec3Df intersectionPoint, Vec3Df n0, Vec3Df n1, Vec3Df n2, float b0, float b1, float b2,float diffuse, float specular, Vec3Df lightpos) const{
    Vec3Df norm = b2*n0+b0*n1+b1*n2;
    norm.normalize();
    Vec3Df wi = lightpos-intersectionPoint;
    wi.normalize();
    Vec3Df ri = 2*norm*Vec3Df::dotProduct(wi, norm)-wi;
    ri.normalize();
    float f = diffuse*(max(Vec3Df::dotProduct(norm, wi),0.f))+pow(specular*(max(Vec3Df::dotProduct(ri,-direction),0.f)),10);
    return f;
}

//float Ray::Mirror (Vec3Df intersectionPoint, Vec3Df camPos, const BoundingBox & bbox){

//}
