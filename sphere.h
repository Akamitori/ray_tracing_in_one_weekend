//
// Created by PETROS on 15/09/2024.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"


class sphere : public hittable {
public:
    sphere(const point3 &center, double radius, const std::shared_ptr<material> &mat);

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override;

private:
    point3 center;
    double radius;
    std::shared_ptr<material> mat;
};


#endif //SPHERE_H
