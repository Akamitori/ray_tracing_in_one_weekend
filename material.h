//
// Created by PETROS on 16/09/2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "hittable.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const =0;
};

class lambertian:public material {
public:
    lambertian(const color& albedo);

    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;

private:
    color albedo;
};

class metal:public material {
  public:
    metal(const color& albedo, double fuzz);
    bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;
private:
    color albedo;
    double fuzz;
};


#endif //MATERIAL_H
