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

    double size() const;

    bool contains(double x) const;

    bool surrounds(double x) const;

    double clamp(double x) const;

    static const interval empty, universe;

    
};



#endif //INTERVAL_H
