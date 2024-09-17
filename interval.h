//
// Created by PETROS on 16/09/2024.
//

#ifndef INTERVAL_H
#define INTERVAL_H


class interval {
public:
    double min;
    double max;

    interval();

    interval(double min, double max);

    [[nodiscard]] double size() const;

    [[nodiscard]]bool contains(double x) const;

    [[nodiscard]]bool surrounds(double x) const;

    [[nodiscard]]double clamp(double x) const;

    static const interval empty, universe;


};


#endif //INTERVAL_H
