#ifndef PLANE_H
#define PLANE_H
#include "Vector3.h"

namespace sgl { namespace math {
    class Plane {
    public:
        enum Side { SIDE_NONE, SIDE_POSITIVE, SIDE_NEGATIVE };
    public:
        Plane():
            magnitude_(0.0f),
            normal_(Vector3::ZERO) {}

        Plane(const Plane &p){
            normal_ = p.normal_;
            magnitude_ = p.magnitude_;
        }
        Plane(const Real& a,const Real& b,const Real& c,const Real& d){
            FromDirect(a,b,c,d);
        }

        Plane(const Vector3& normal, const Real& magnitude){
            FromNormalDistance(normal,magnitude);
        }

        Plane(const Vector3& p, const Vector3& n){
            FromPointNormal(p,n);
        }

        Plane(const Vector3& a, const Vector3& b, const Vector3& c){
            FromThreePoints(a,b,c);
        }

        Real GetDistance(const Vector3& a){
            return normal_.Dot(a) + magnitude_;
        }
        Real get_magnitude(){
            return magnitude_;
        }
        Vector3 get_normal(){
            return normal_;
        }
        void Invert()		{
            normal_.Invert();
            magnitude_ *= -1;
        }
        void operator=(const Plane &p){
            normal_ = p.normal_;
            magnitude_ = p.magnitude_;
        }

        // Create plane from 3 points
        void FromThreePoints(const Vector3& a, const Vector3& b, const Vector3& c){
            Vector3 ed1 = b - a;
            Vector3 ed2 = c - a;
            normal_ = ed1.Cross(ed2);
            normal_.Normalize();

            magnitude_ = -normal_.Dot(a);
        }

        // Create plane from a point and normal
        void FromPointNormal(const Vector3& p, const Vector3& n){
            normal_ = n;
            normal_.Normalize();
            magnitude_ = -normal_.Dot(p);
        }

        // Create a plane from a normal and a distance along that normal
        void FromNormalDistance(const Vector3& n, const Real& d){
            normal_ = n;
            magnitude_ = d;
        }

        // Create a plane directly from the a+b+c+d=0 values;
        void FromDirect(const Real& a,const Real& b,const Real& c,const Real& d){
            normal_ = Vector3(a,b,c);
            magnitude_ = d;
        }

        Plane::Side GetSide(const Vector3& a){
            Real dist = Plane::GetDistance(a);
            if(dist < 0.0f)return Plane::SIDE_NEGATIVE;
            if(dist > 0.0f)return Plane::SIDE_POSITIVE;

            return Plane::SIDE_NONE;
        }

        Vector3 Project(const Vector3& v){
            Real t = -(normal_.Dot(v) + magnitude_)/normal_.SqrLength();
            return Vector3(v.x + normal_.x * t,
                           v.y + normal_.y * t,
                           v.z + normal_.z * t);
        }

        /*bool Intersect(const Ray &r,double *aMu){
            double num = mag - r.GetOrigin().Dot(GetNormal());
            double den = r.GetDirection().Dot(GetNormal());

            if(den == 0) {
                //DbgWrite("  - Error w/ [Intersections::RayPlane], denominator is zero meaning either Ray direction or plane normal are undefined.\n");
                return false;
            }
            double mu = num / den;

            if(aMu)*aMu = mu;

            if(mu < 0) {
                //DbgWriteV(3,"  - Warning w/ [Intersections::RayPlane], intersection is behind the Ray origin, no hit.\n");
                //return false;
            }
            return true;
        }*/
        Vector3 normal_;
        Real magnitude_;
    };
}}   //end sgl::math

#endif // PLANE_H
