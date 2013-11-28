#ifndef PRIMITIVES_VECTOR3_H
#define PRIMITIVES_VECTOR3_H
#include "../SGL.h"
#include "sglmath.h"

#include <string>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <sstream>

namespace sgl { namespace math {
    class Vector3 {
    public:
        static const Vector3 ZERO;
        static const Vector3 UNIT_X;
        static const Vector3 UNIT_Y;
        static const Vector3 UNIT_Z;

        Vector3():
            x(0.0f),
            y(0.0f),
            z(0.0f)
        {}
        Vector3(const Real& x, const Real& y, const Real& z):
            x(x),
            y(y),
            z(z)
        {}
        explicit Vector3(const Real xyz[3]):
            x(xyz[0]),
            y(xyz[1]),
            z(xyz[2])
        {}
        Vector3(const Vector3& v){
            x = v.x;
            y = v.y;
            z = v.z;
        }
        Vector3(Vector3&& v){
            x = v.x;
            y = v.y;
            z = v.z;
        }

        ~Vector3(){}

        //todo: replace return value with radians class (do so for all angle funcs)
        static Real Angle(const Vector3& a, const Vector3& b) {
            Real dot = a.Dot(b);
            return std::acos(dot/(a.Length()*b.Length())) * 57.2957795f; //rads to degs
        }
        Real Angle(const Vector3& b) const{
            return Vector3::Angle(*this,b);
        }


        static Real SignedAngleBetween(const Vector3& a, const Vector3& b, const Vector3& up){
            // angle in [0,180]
            Real angle = Vector3::Angle(a,b);
            int sign = sgl::math::sign(Vector3::Dot(up,Vector3::Cross(a,b)));

            // angle in [-179,180]
            Real signed_angle = angle * sign;

            // angle in [0,360]
            Real angle360 =  std::fmod(signed_angle+360.0f,360.0f);//(signed_angle) + 360) % 360;

            return angle360;
        }
        Real Length() const{
            return std::sqrt(SqrLength());
        }
        Real SqrLength() const{
            return (x*x+y*y+z*z);
        }

        static Real Distance(const Vector3& a,const Vector3& b){
            return (b-a).Length();
        }
        Real Distance(const Vector3& b) const{
            return Vector3::Distance(*this,b);
        }

        static Real SqrDistance(const Vector3& a,const Vector3& b){
            return (b-a).SqrLength();
        }

        Real SqrDistance(const Vector3& b) const{
            return Vector3::SqrDistance(*this,b);
        }

        void Invert(){
            (*this)*=-1.0f;
        }
        Vector3 Inverted() const{
            return (*this)*-1.0f;
        }

        Vector3 Cross(const Vector3& rhs) const{
            return Vector3::Cross(*this,rhs);
        }

        static Vector3 Cross(const Vector3& lhs, const Vector3& rhs) {
            return Vector3(
                        (lhs.y*rhs.z - lhs.z * rhs.y),
                        (lhs.z*rhs.x - lhs.x * rhs.z),
                        (lhs.x*rhs.y - lhs.y * rhs.x));
        }
        Vector3 MidPoint(const Vector3& rhs) const{
            return Vector3::MidPoint(*this,rhs);
        }

        static Vector3 MidPoint(const Vector3& lhs, const Vector3& rhs) {
            return Vector3(
                        (lhs.x + rhs.x) * 0.5f,
                        (lhs.y + rhs.y) * 0.5f,
                        (lhs.z + rhs.z) * 0.5f);
        }

        void Normalize(){
            Real length = Length();
            (*this)/=length;
        }

        Vector3 Normalized() const{
            Real length = Length();
            return (*this)/length;
        }

        Real Dot(const Vector3& rhs) const{
            return Vector3::Dot(*this,rhs);
        }

        static Real Dot(const Vector3& lhs,const Vector3& rhs) {
            return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z*rhs.z;
        }

        static Vector3 Max(const Vector3& a,const Vector3& b){
            return Vector3( std::max(a.x,b.x),
                            std::max(a.y,b.y),
                            std::max(a.z,b.z));
        }

        static Vector3 Min(const Vector3& a,const Vector3& b){
            return Vector3( std::min(a.x,b.x),
                            std::min(a.y,b.y),
                            std::min(a.z,b.z));
        }
        void operator=(const Vector3& v){
            x = v.x;
            y = v.y;
            z = v.z;
        }

        void operator+=(const Vector3& rhs){
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
        }
        void operator+=(const Real& rhs){
            x += rhs;
            y += rhs;
            z += rhs;
        }

        void operator-=(const Vector3& rhs){
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
        }
        void operator-=(const Real& rhs){
            x -= rhs;
            y -= rhs;
            z -= rhs;
        }

        void operator*=(const Vector3& rhs){
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
        }
        void operator*=(const Real& rhs){
            x *= rhs;
            y *= rhs;
            z *= rhs;
        }

        void operator/=(const Vector3& rhs){
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
        }
        void operator/=(const Real& rhs){
            x /= rhs;
            y /= rhs;
            z /= rhs;
        }

        Vector3 operator+(const Vector3& rhs){
            return Vector3(
                    x + rhs.x,
                    y + rhs.y,
                    z + rhs.z);
        }
        Vector3 operator+(const Real& rhs){
            return Vector3(
                    x + rhs,
                    y + rhs,
                    z + rhs);
        }

        Vector3 operator-(const Vector3& rhs){
            return Vector3(
                    x - rhs.x,
                    y - rhs.y,
                    z - rhs.z);
        }
        Vector3 operator-(const Real& rhs){
            return Vector3(
                    x - rhs,
                    y - rhs,
                    z - rhs);
        }

        Vector3 operator*(const Vector3& rhs){
            return Vector3(
                    x * rhs.x,
                    y * rhs.y,
                    z * rhs.z);
        }
        Vector3 operator*(const Real& rhs){
            return Vector3(
                    x * rhs,
                    y * rhs,
                    z * rhs);
        }

        Vector3 operator/(const Vector3& rhs){
            return Vector3(
                    x / rhs.x,
                    y / rhs.y,
                    z / rhs.z);
        }
        Vector3 operator/(const Real& rhs){
            return Vector3(
                    x / rhs,
                    y / rhs,
                    z / rhs);
        }

        std::string ToString() const{
           std::stringstream ss;
           ss << x << " " << y << " " << z;
           return ss.str();
        }

        friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
        friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
        friend Vector3 Vector3::operator*(const Vector3& lhs, const Vector3& rhs);
        friend Vector3 Vector3::operator/(const Vector3& lhs, const Vector3& rhs);

        friend Vector3 operator+(const Vector3& lhs, const Real& rhs);
        friend Vector3 operator-(const Vector3& lhs, const Real& rhs);
        friend Vector3 Vector3::operator*(const Vector3& lhs, const Real& rhs);
        friend Vector3 Vector3::operator/(const Vector3& lhs, const Real& rhs);
    private:
    public:
        union {
            struct { Real x,y,z; };
            struct { Real cell[3];};
        };
    };
    inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs){
        return Vector3(
                lhs.x + rhs.x,
                lhs.y + rhs.y,
                lhs.z + rhs.z);
    }
    inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs){
        return Vector3(
                lhs.x - rhs.x,
                lhs.y - rhs.y,
                lhs.z - rhs.z);
    }
    inline Vector3 operator*(const Vector3& lhs, const Vector3& rhs){
        return Vector3(
                lhs.x * rhs.x,
                lhs.y * rhs.y,
                lhs.z * rhs.z);
    }
    inline Vector3 operator/(const Vector3& lhs, const Vector3& rhs){
        return Vector3(
                lhs.x / rhs.x,
                lhs.y / rhs.y,
                lhs.z / rhs.z);
    }

    inline Vector3 operator+(const Vector3& lhs, const Real& rhs){
        return Vector3(
                lhs.x + rhs,
                lhs.y + rhs,
                lhs.z + rhs);
    }
    inline Vector3 operator-(const Vector3& lhs, const Real& rhs){
        return Vector3(
                lhs.x - rhs,
                lhs.y - rhs,
                lhs.z - rhs);
    }
    inline Vector3 operator*(const Vector3& lhs, const Real& rhs){
        return Vector3(
                lhs.x * rhs,
                lhs.y * rhs,
                lhs.z * rhs);
    }
    inline Vector3 operator/(const Vector3& lhs, const Real& rhs){
        return Vector3(
                lhs.x / rhs,
                lhs.y / rhs,
                lhs.z / rhs);
    }
}} // end namespace sgl::math


#endif // PRIMITIVES_VECTOR3_H
