#ifndef MEASUREUNITS_HPP_INCLUDED
#define MEASUREUNITS_HPP_INCLUDED

/// TD
/*
    multiple levels of precision... (?!)
    temperature: Klevin, Celsius, Fahrenheit (and their history, mechanism of measurement, algebraic relationship
        // and computational model for the constants between them and whether they are precise)
*/

enum Degrees {
    Kelvin,
    Celsius,
    Fahrenheit,
};

struct Temperature {
    enum Degrees degree_type;
    float value;    // this type should / could be adjusted / normalized / scoped to
        // the most relevant interval of powers of 2, for efficiency and performance
};

float kelvin_to_celsius(float value) {
    return value - 273.15;
}

float kelvin_to_fahrenheit(float value) {
    return (((value - 273.15) / 5.0) * 9.0) + 32.0;
}

float celsius_to_kelvin(float value) {
    return value + 273.15;
}

float celsius_to_fahrenheit(float value) {
    return ((value / 5.0) * 9.0) + 32.0;
}

float fahrenheit_to_kelvin(float value) {
    return (((value / 9.0) - (32.0 / 9.0)) * 5.0) + 273.15;
}
float fahrenheit_to_celsius(float value) {
    return ((value / 9.0) - (32.0 / 9.0)) * 5.0;
}

#endif // MEASUREUNITS_HPP_INCLUDED
