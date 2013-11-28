TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    math/Vector4.cpp \
    math/Vector3.cpp \
    math/Matrix33.cpp \
    collections/Simplecloud.cpp \
    collections/Mesh.cpp \
    math/Quaternion.cpp \
    math/Matrix44.cpp \
    math/Ray.cpp \
    math/AxisAlignedBoundingBox.cpp \
    collections/IndexedPolygon.cpp \
    math/Plane.cpp


HEADERS += \
    math/Vector4.h \
    math/Vector3.h \
    math/Matrix33.h \
    sgl.h \
    math/sglmath.h \
    collections/Simplecloud.h \
    collections/Cloud.h \
    collections/Mesh.h \
    math/Quaternion.h \
    math/Matrix44.h \
    math/Ray.h \
    math/AxisAlignedBoundingBox.h \
    collections/IndexedPolygon.h \
    math/Plane.h
