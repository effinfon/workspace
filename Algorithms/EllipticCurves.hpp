#ifndef ELLIPTICCURVES_HPP_INCLUDED
#define ELLIPTICCURVES_HPP_INCLUDED

/// TD
/*  "FUNCTION FORMS"

    y^2 = a * x^3 + b * x + c
*/
/*  DISCUSSIONS

    (*?) intersection of a line with an arbitrary function <e.g.> the tangent is basically a line equation, and it needs to intersect the curve's equation
        (an elliptic curve in this case); this will produce the relevant point; next, just use the opposite of y
    addition in this ~ "geometry grgoup" is basically a binary operation that defines the pair of points which constitute the tangent line; I suspect P + P is not literally the
        same point, but instead "P + infinitesimal neighbour of P" (otherwise how is there even a tangent, formally speaking ?)
    (*?) the elliptic curve seems to act out a similar role as the modulo spaces do
    (*?) how do I compute an "elliptic step" / "elliptic-group addition" without loss of precision ? or rather, which points can be computed without loss of precision (-> integers,
        but not fractional numbers; real numbers are also excluded)
    (*?) are elliptic curves structures that are guaranteed to have tangents at all points only intersecting them at a single (other) point ? (except the "identity point", which
        could also be seen as a particular case of a line equation)
*/


#endif // ELLIPTICCURVES_HPP_INCLUDED
