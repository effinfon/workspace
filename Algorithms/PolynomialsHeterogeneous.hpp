#ifndef POLYNOMIALSHETEROGENEOUS_HPP_INCLUDED
#define POLYNOMIALSHETEROGENEOUS_HPP_INCLUDED

/// TD
/*
    all the interesting algebraic equations involving multiple dimensionalities (and possibly multiple "orders" / ~ 'steepnesses" too)
    ax + by = c, ax^2 + by = c, ax^2 + by^2 = c, ax^3 + by = c, ax^3 + by^2 = c, etc.
    ax + by + cz = d, ax^2 + by + cz = d, ..., ax^4 + by^3 + cz^2 = d, etc. // so far, both "families" seem to be just linear equations,
        // with the application / composition of an n-root at the end / in the "end expression" (?!); "typical solving" would involve
        // substituting the variables with "order 1 placeholders", but if the essence if indeed as stated above, then it's unnecessary
    ax + by + cz + dw = e, etc. // as an extension tot he previous discussion, $rhs^n is not discussed because it's a constant, but also
        // ecause even if $rhs^n is evaluated, it still has the "same properties as an rhs" (?!) [what would that be, evaluability ? it
        // does not change the "complexity", or rather the (!)  "solvability required property structures" of the end expression (?)]
        // [I sort of try to express here that when "solving an expression", it basically requires the searcher to find certain patterns
        // that somehow "extract" properties from the expression being computed, then apply certain operations on them and "something happens",
        // and that if some change in the expression does not affect these patterns (greatly), then it is a (?"sub-general parametrization"?)]
        // as a side note: if there were to be $rhs^n, it would just evaluate to a scalar, because it is ~ "directly evaluable" [because we
        // know how to do it; if we wouldn't know how to do it (!) analytically, then it would be a "complication", yes; so in fact, for ^n
        // not in N or Z, it does become significant actually, because n-roots are not always analytic, and then complications do appear actually (!?)]
    { a1x + b1y + c1z = d1, a2x + b2y + c2z = d2 }, from these result a ~ "determinant base" / "constraint", basically a "common denominator"; so I was
        // wondering how that denominator represents the "cummulation of constraints" from all the equations taken together (!?)
    "over-determinancy": { a1x + b1y + c1y = d1, a2x + b2y + c2y = d2, a3x + b3y + c3y = d3, a4x + b4y + c4y = d4, a5x + b5y + c5y = d5}; how will  that
        // "common denominator" / (?"determinant base"?) look like now ? and what happens when "the same constraint repeats", how does it "simplify" / "reduce" ?

*/

#endif // POLYNOMIALSHETEROGENEOUS_HPP_INCLUDED
