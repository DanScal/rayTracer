/*
 *  rayTracer.h
 *
 */

struct Point {
   float x, y, z;
};

struct Vector {
   struct Point start;
   float dx, dy, dz;
};

struct Camera {
    struct Point position;
    struct Point lookAt;
    struct Vector up;
    float focalLength;
};

struct Color {
    float red, green, blue;
};

struct  Light {
    struct Point position;
    struct Color color;
    struct Color ambientColor;
};

struct Hit {
    struct Point intersectionPt;
    int which;
    float omega;
};

struct Object {

   /* S is sphere; F is floor */
   char letter;
   struct Color ambient[2], diffuse[2], specular[2];
   float refractionIndex;
   float Ka, Kd, Ks, Ke, Kr, Kt;

   /* sphere */
   struct Point center;
   float radius;

   /* floor */
   struct Point vertex[4];
   float checksize;
   float xmin, xmax, ymin, ymax, zmin, zmax;
   struct Vector normal;
   float F; /* Minimal distance of floor to world origin */
};