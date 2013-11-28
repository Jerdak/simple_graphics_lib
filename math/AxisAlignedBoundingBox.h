#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H
#include "../sgl.h"
#include "Vector3.h"
#include "Ray.h"


namespace sgl { namespace math {
    // General purpose bounding box
    //
    // refs
    // [1] - http://people.csail.mit.edu/amy/papers/box-jgt.pdf
    class AxisAlignedBoundingBox
    {
    public:
        AxisAlignedBoundingBox();
        AxisAlignedBoundingBox( const Vector3& position, const Vector3& size );
        AxisAlignedBoundingBox( const AxisAlignedBoundingBox& aabb);

        // Get maximum corner of the bounding box (position + size)
        Vector3 GetMaximum() const;

        // Get minimum corner of the bounding box (position)
        Vector3 GetMinimum() const;

        // Get position/origin of bounding box
        Vector3 get_position() const {return position_;}

        // Get size of boundingbox
        Vector3 get_size() const { return size_;}

        // Get center of bounding box
        Vector3 get_center() const { return center_; }

        // Returns whether or not this boundingbox has intersected another bounding box
        bool Intersects(const AxisAlignedBoundingBox& b2 ) const;

        // Returns whether or not this boundingbox intersects a given ray
        //
        // Based off of a CSAIL bounding box paper [1]
        bool Intersects(const Ray& r) const;

        // Returns true if this bounding box contains specified vector
        bool Contains( const Vector3& p ) const;

        // Returns true if this bounding box contains a triangle defined by points (a,b,c)
        bool ContainsTriangle( const Vector3& a, const Vector3& b, const Vector3& c) const;
        void operator =(const AxisAlignedBoundingBox& aabb);


    private:
        Vector3 size_;
        Vector3 half_size_;
        Vector3 center_;
        Vector3 position_;
    };
}} // end sgl::math

#endif // AXISALIGNEDBOUNDINGBOX_H
