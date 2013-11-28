#include "AxisAlignedBoundingBox.h"
//Axis aligned bounding box
    #define FINDMINMAX(x0,x1,x2,min,max) \
    min = max = x0;   \
    if(x1<min) min=x1;\
    if(x1>max) max=x1;\
    if(x2<min) min=x2;\
    if(x2>max) max=x2;


/*======================== X-tests ========================*/
    #define AXISTEST_X01(a, b, fa, fb)			   \
    p0 = a*v0.y - b*v0.z;			       	   \
    p2 = a*v2.y - b*v2.z;			       	   \
        if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
    rad = fa * half_size_.y + fb * half_size_.z;   \
    if(min>rad || max<-rad) return 0;

    #define AXISTEST_X2(a, b, fa, fb)			   \
    p0 = a*v0.y - b*v0.z;			           \
    p1 = a*v1.y - b*v1.z;			       	   \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * half_size_.y + fb * half_size_.z;   \
    if(min>rad || max<-rad) return 0;

/*======================== Y-tests ========================*/
    #define AXISTEST_Y02(a, b, fa, fb)			   \
    p0 = -a*v0.x + b*v0.z;		      	   \
    p2 = -a*v2.x + b*v2.z;	       	       	   \
        if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
    rad = fa * half_size_.x + fb * half_size_.z;   \
    if(min>rad || max<-rad) return 0;

    #define AXISTEST_Y1(a, b, fa, fb)			   \
    p0 = -a*v0.x + b*v0.z;		      	   \
    p1 = -a*v1.x + b*v1.z;	     	       	   \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * half_size_.x + fb * half_size_.z;   \
    if(min>rad || max<-rad) return 0;

/*======================== Z-tests ========================*/

    #define AXISTEST_Z12(a, b, fa, fb)			   \
    p1 = a*v1.x - b*v1.y;			           \
    p2 = a*v2.x - b*v2.y;			       	   \
        if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;} \
    rad = fa * half_size_.x + fb * half_size_.y;   \
    if(min>rad || max<-rad) return 0;

    #define AXISTEST_Z0(a, b, fa, fb)			   \
    p0 = a*v0.x - b*v0.y;				   \
    p1 = a*v1.x - b*v1.y;			           \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
    rad = fa * half_size_.x + fb * half_size_.y;   \
    if(min>rad || max<-rad) return 0;

namespace sgl { namespace math {

AxisAlignedBoundingBox::AxisAlignedBoundingBox():
    position_(Vector3::ZERO),
    size_(Vector3::ZERO),
    center_(Vector3::ZERO)
{
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox( const Vector3& position, const Vector3& size ):
    position_(position),
    size_(size)
{
    center_ = (position_ + size_) / 2.0f;
    half_size_ = size_ / 2.0f;
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox( const AxisAlignedBoundingBox& aabb){
    position_ = aabb.position_;
    size_ = aabb.size_;
    center_ = aabb.center_;
    half_size_ = aabb.half_size_;
}

void AxisAlignedBoundingBox::operator=( const AxisAlignedBoundingBox& aabb){
    position_ = aabb.position_;
    size_ = aabb.size_;
    center_ = aabb.center_;
    half_size_ = aabb.half_size_;
}

Vector3 AxisAlignedBoundingBox::GetMaximum() const{
    return position_ + size_;
}

Vector3 AxisAlignedBoundingBox::GetMinimum() const{
    return position_;
}

bool AxisAlignedBoundingBox::Intersects(const AxisAlignedBoundingBox& b2 ) const {
    Vector3 v1 = b2.GetMinimum(), v2 = b2.GetMaximum();
    Vector3 v3 = position_, v4 = position_ + size_;
    return ((v4.x >= v1.x) && (v3.x <= v2.x) && // x-axis overlap
            (v4.y >= v1.y) && (v3.y <= v2.y) && // y-axis overlap
            (v4.z >= v1.z) && (v3.z <= v2.z));  // z-axis overlap
}

bool AxisAlignedBoundingBox::Intersects(const Ray& r) const{
    Real txmin, txmax, tymin, tymax, tzmin, tzmax, tmin, tmax;

    Vector3 rdirection = r.get_direction();
    Vector3 rorigin = r.get_origin();

    Vector3 min = position_;
    Vector3 max = position_ + size_;
    if ( rdirection.x >= 0 ){
        txmin = ( min.x - rorigin.x ) * rdirection.x;
        txmax = ( max.x - rorigin.x ) * rdirection.x;
    }else{
        txmin = ( max.x - rorigin.x ) * rdirection.x;
        txmax = ( min.x - rorigin.x ) * rdirection.x;
    }

    if ( rdirection.y >= 0 ){
        tymin = ( min.y - rorigin.y ) * rdirection.y;
        tymax = ( max.y - rorigin.y ) * rdirection.y;
    }else{
        tymin = ( max.y - rorigin.y ) * rdirection.y;
        tymax = ( min.y - rorigin.y ) * rdirection.y;
    }

    if ( (txmin > tymax) || (tymin > txmax ) ){ return false; }

    if ( tymin > txmin ){
        tmin = tymin;
    }else{
        tmin = txmin;
    }

    if ( tymax < txmax ){
        tmax = tymax;
    }else{
        tmax = txmax;
    }

    if ( rdirection.z >= 0 ){
        tzmin = ( min.z - rorigin.z ) * rdirection.z;
        tzmax = ( max.z - rorigin.z ) * rdirection.z;
    }else{
        tzmin = ( max.z - rorigin.z ) * rdirection.z;
        tzmax = ( min.z - rorigin.z ) * rdirection.z;
    }

    if ( (tmin > tzmax) || (tzmin > tmax) )	{ return false; }

    // original paper (see method declaration) included a check for t0/t1 bounds that was removed
    return true;
}
bool AxisAlignedBoundingBox::Contains(const Vector3& p) const{
    Vector3 max = position_ + size_;
    return ((p.x >= position_.x) && (p.x <= max.x) &&
            (p.y >= position_.y) && (p.y <= max.y) &&
            (p.z >= position_.z) && (p.z <= max.z));
}

int planeBoxOverlap(const Vector3& normal,const Real& d, const Vector3& maxbox)
{
    int q;
    Vector3 vmin,vmax;
    for(q=0;q<=2;q++)
    {
        if(normal.cell[q]>0.0f)
        {
            vmin.cell[q]=-maxbox.cell[q];
            vmax.cell[q]=maxbox.cell[q];
        } else {
            vmin.cell[q]=maxbox.cell[q];
            vmax.cell[q]=-maxbox.cell[q];
        }
    }
    if(normal.Dot(vmin)+d>0.0f) return 0;
    if(normal.Dot(vmax)+d>=0.0f) return 1;

    return 0;
}
bool AxisAlignedBoundingBox::ContainsTriangle( const Vector3& a, const Vector3& b, const Vector3& c) const{
    Vector3 axis,normal,e0,e1,e2,v0,v1,v2;
    Real min, max, d, p0, p1, p2,rad,fex,fey,fez;

    v0 = a - center_;
    v1 = b - center_;
    v2 = c - center_;

    e0 = v1 - v0;
    e1 = v2 - v1;
    e2 = v0 - v2;

    fex = fabs(e0.x);
    fey = fabs(e0.y);
    fez = fabs(e0.z);
    AXISTEST_X01(e0.z, e0.y, fez, fey);
    AXISTEST_Y02(e0.z, e0.x, fez, fex);
    AXISTEST_Z12(e0.y, e0.x, fey, fex);

    fex = fabs(e1.x);
    fey = fabs(e1.y);
    fez = fabs(e1.z);
    AXISTEST_X01(e1.z, e1.y, fez, fey);
    AXISTEST_Y02(e1.z, e1.x, fez, fex);
    AXISTEST_Z0(e1.y, e1.x, fey, fex);

    fex = fabs(e2.x);
    fey = fabs(e2.y);
    fez = fabs(e2.z);
    AXISTEST_X2(e2.z, e2.y, fez, fey);
    AXISTEST_Y1(e2.z, e2.x, fez, fex);
    AXISTEST_Z12(e2.y, e2.x, fey, fex);

    /* test in X-direction */
    FINDMINMAX(v0.x,v1.x,v2.x,min,max);

    if(min>half_size_.x || max<-half_size_.x) return false;

    /* test in Y-direction */
    FINDMINMAX(v0.y,v1.y,v2.y,min,max);
    if(min>half_size_.y || max<-half_size_.y) return false;

    /* test in Z-direction */
    FINDMINMAX(v0.z,v1.z,v2.z,min,max);
    if(min>half_size_.z || max<-half_size_.z) return false;

    /* Bullet 2: */
    /*  test if the box intersects the plane of the triangle */
    /*  compute plane equation of triangle: normal*x+d=0 */
    normal = e0.Cross(e1);
    d=-1 * normal.Dot(v0);  /* plane eq: normal.x+d=0 */
    if(!planeBoxOverlap(normal,d,half_size_)) return false;

    return true;
}

}} //end sgl::math
