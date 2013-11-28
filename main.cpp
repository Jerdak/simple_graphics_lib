#include <iostream>
#include "math/Vector3.h"

using namespace std;
using namespace sgl::math;


int main()
{
    Vector3 v1(1,0,0);
    Vector3 v2(v1);
    Vector3 v3(Vector3(12,13,14));

    cout << "sign(43): " << sgl::math::sign(43) << "\n";
    cout << "sign(-42): " << sgl::math::sign(-42) << "\n";
    cout << "sign(42.0f): " << sgl::math::sign(42.0f) << "\n";
    cout << "sign(-42.0f): " << sgl::math::sign(-42.0f) << "\n";
    cout << "sign(42.0): " << sgl::math::sign(42.0) << "\n";
    cout << "sign(-42.0): " << sgl::math::sign(-42.0) << "\n";
    cout << "sign(0): " << sgl::math::sign(0) << "\n";
    cout << "sign(0.0f): " << sgl::math::sign(0.0f) << "\n";
    cout << "sign(0.0): " << sgl::math::sign(0.0) << "\n";


    return 0;
}

