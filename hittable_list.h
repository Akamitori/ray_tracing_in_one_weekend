//
// Created by PETROS on 15/09/2024.
//

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include "hittable.h"

using std::shared_ptr;
using std::vector;


class hittable_list : public hittable {
public:
    vector<shared_ptr<hittable> > objects;

    hittable_list() = default;

    explicit hittable_list(const shared_ptr<hittable> &object);

    void clear();

    void add(const shared_ptr<hittable> &object);

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override;

};


#endif //HITTABLE_LIST_H
