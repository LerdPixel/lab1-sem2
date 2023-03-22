#ifndef VECTOR3
#define VECTOR3

struct Vector3 {
    struct Ring *ring;
    void *x;
    void *y;
    void *z;
};

struct Vector3* FromNums();

#endif
