//
// Created by PETROS on 15/09/2024.
//

#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"


class sphere : public hittable{
public:
    sphere(const point3& center, const double radius);
    virtual bool hit(const ray& r, double ray_t_min, double ray_t_max, hit_record& rec) const;
private:
    point3 center;
    double radius;
};



#endif //SPHERE_H
