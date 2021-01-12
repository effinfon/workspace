#ifndef OPTIMIZATIONPROBLEMS_HPP_INCLUDED
#define OPTIMIZATIONPROBLEMS_HPP_INCLUDED

/*  FITNESS PROJECT

    bike:
        // to estimate the mechanical power produced by the muscles (and the burnt calories, to some extent), I would like to use an alternator / electric generator
            to charge a capacitor; given the sampling rate of the capacitor's voltage and the sampling precision (~ bit depth of the ADC), the capacitor's voltage threshold
            and the capacitor's capacitance, plus an approximation of the path's resistance, and an approximation of the leakage current of the capacitor, decide:
                - what is the optimal capacitance for the capacitor ?
                    -> at what frequency does it require sampling ?
                - how big is the error ?
                - how is the "power in a capacitor" calculated ? (*?)["computed" ~!:= "calculated"]
            (*) this project would make use of an Atmel microprocessor (Atmel Atmega 128P most likely)
*/

#endif // OPTIMIZATIONPROBLEMS_HPP_INCLUDED
