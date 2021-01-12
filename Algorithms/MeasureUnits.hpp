#ifndef MEASUREUNITS_HPP_INCLUDED
#define MEASUREUNITS_HPP_INCLUDED

/// TD
/*
    multiple levels of precision... (?!)
    temperature: Klevin, Celsius, Fahrenheit (and their history, mechanism of measurement, algebraic relationship
        // and computational model for the constants between them and whether they are precise)
*/
namespace MeasurementUnits {
    enum Degrees {
        Kelvin,
        Celsius,
        Fahrenheit,
    };

    template<typename Precision_Type>
    struct Temperature {
        enum Degrees degree_type;
        Precision_Type value;    // this type should / could be adjusted / normalized / scoped to
            // the most relevant interval of powers of 2, for efficiency and performance

    static Precision_Type kelvin_to_celsius(Precision_Type value) {
        return value - static_cast<Precision_Type>(273.15);
    }

    static Precision_Type kelvin_to_fahrenheit(Precision_Type value) {
        return (((value - 273.15) / 5.0) * 9.0) + 32.0;
    }

    static Precision_Type celsius_to_kelvin(Precision_Type value) {
        return value + 273.15;
    }

    static Precision_Type celsius_to_fahrenheit(Precision_Type value) {
        return ((value / 5.0) * 9.0) + 32.0;
    }

    static Precision_Type fahrenheit_to_kelvin(Precision_Type value) {
        return (((value / 9.0) - (32.0 / 9.0)) * 5.0) + 273.15;
    }

    static Precision_Type fahrenheit_to_celsius(Precision_Type value) {
        return ((value / 9.0) - (32.0 / 9.0)) * 5.0;
    }
    };
};
#endif // MEASUREUNITS_HPP_INCLUDED
