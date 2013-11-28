#ifndef RAY_H
#define RAY_H
#include "../sgl.h"
#include "Vector3.h"

namespace sgl { namespace math {
    class Ray {
    public:
        Ray():
            origin_(Vector3::ZERO),
            direction_(Vector3::ZERO) {}

        Ray(const Vector3& origin, const Vector3& direction):
            origin_(origin),
            direction_(direction) {}

        Ray(const Ray& r){
            origin_ = r.origin_;
            direction_ = r.direction_;
        }

        void set_origin(const Vector3& origin) {origin_ = origin;}
        Vector3 get_origin() const {return origin_;}

        void set_direction(const Vector3& direction){direction_ = direction;}

        // Get ray direction
        Vector3 get_direction() const {return direction_;}

        // Return a point 't' units along ray direction from origin
        Vector3 GetPoint(const Real& t){
            return origin_ + direction_ * t;
        }

        void operator=(const Ray& r){
            origin_ = r.origin_;
            direction_ = r.direction_;
        }

    protected:

    private:

        Vector3 origin_;
        Vector3 direction_;

    };
}}   //end sgl::math

#endif // RAY_H
