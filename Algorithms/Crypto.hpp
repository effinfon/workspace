#ifndef CRYPTO_HPP_INCLUDED
#define CRYPTO_HPP_INCLUDED

/*  RSA

    p, q - primes
    n = p * q
    phi = (p - 1) * (q - 1) -> (*?) f(n) -> phi (?)
    public_key, private_key -> public_key * private_key = 1 (mod n) => computing one from the other ("inverse modulo multiplicand")
    message
    signature = message^private_key (mod n)
    verification: message^(public_key * private_key) = message^(1) (mod n) = message
*/

bool isPrime(uint64_t number) {
//    debug_print("Debug isPrime - start\n");

    if(number % 2 == 0) {
//        printf("Debug isPrime - end false\n");
        return false; }

    for(uint64_t i {3}; i * i < number; i += 2) {
        if(number % i == 0) {
//        printf("Debug isPrime - end false\n");
        return false; }
    }

//    printf("Debug isPrime - end true\n");

    return true;
}

uint64_t ComputeN(uint64_t p, uint64_t q) {
//    printf("Debug ComputeN - start\n");

    if(isPrime(p) && isPrime(q)) {
//        printf("Debug ComputeN - end product returned\n");
        return p * q;
    }

//    printf("Debug ComputeN - end not prime\n");
}

uint64_t ComputePhi(uint64_t p, uint64_t q) {
//    printf("Debug ComputePhi- start\n");

    if(isPrime(p) && isPrime(q)) {
//        printf("Debug ComputePhi- end returned product\n");

        return (p - 1) * (q - 1);   // (*?) this is a ~ "difficulty / complexity function" for finding what the modulo space is for the keys
                                    // (*!?) but essentially, the relation between the keys is still that of "inverse modulo multiplicand"
    }

//    printf("Debug ComputePhi- end not prime\n");
}

uint64_t ComputeGcd(uint64_t a, uint64_t b) {
//    printf("Debug ComputeGcd - start\n");

    if(b == 0) {
//    printf("Debug ComputeGcd- end final recursion\n");
        return a; }
    else return ComputeGcd(b, a % b);
}

uint64_t ComputeLcm(uint64_t a, uint64_t b) {
//    printf("Debug ComputeLcm - start and end, single liner; calls ComputeGcd()\n");
    return (a / ComputeGcd(a, b)) * b;
}

uint64_t ComputeK(uint64_t coefficient, uint64_t target, uint64_t modulo) {
//    printf("Debug ComputeK - start\n");
    // (*?) modulo equation: ax = b (mod n), where a and b are known / constraints
    uint64_t x = 1;
    while((x * coefficient) % modulo != target) {
//        printf("coefficient: %lu, x: %lu, product: %lu, modulo product: %lu, target: %lu\n", coefficient, x, x * coefficient, (x * coefficient) % modulo, target);
        x++; }

    return x;
}

uint64_t ComputePrivateKey(uint64_t public_key, uint64_t phi) {
//    printf("Debug ComputePrivateKey - start and end, single liner - calls ComputeLcm()\n");

    // (*?!) this (long return expression) is an interesting example of where factorization-out / distribution of a computation cannot be done without loss
        // of information, on a ~ "lattice computer" / "integer computer" / "modulo computer"
    // (*?) the optimization of computation to be stored as pre-compute should / could be handled by an optimizer (!?), leaving the programmer in a more
        // mathematically relevant position of designing the functions and thinking about their abstract complexity
    // (*!?) an interesting problem is that in cryptography, where supposedly the "implementation" is prone to bugs / vulnerabilities (?!), or is this
        // just another case of "impure functions" / "non-equivalent implementation" / "physical domain is larger than abstract domain" (?!)
        // (*?) and yet, any impure function can be brought back to some "abstract space" and thought of in the same (~ mathematical) framework, therefore
            // "physical effects" are themselves ~ "unconsidered abstract (properties or effects)" (?!)
        printf("k: %lu\n", ComputeK(phi % public_key, public_key - 1, public_key));
    return (phi / public_key) * ComputeK(phi % public_key, public_key - 1, public_key) + ((phi % public_key) * ComputeK(phi % public_key, public_key - 1, public_key) + 1) / public_key;
}

uint64_t Pow(uint64_t base, uint64_t exp) {
//    printf("Debug Pow - start\n");

    if(exp == 1) {
//        printf("Debug Pow - end last recursion\n");
        return base; }
    if(exp % 2 == 1) return base * Pow(base * base, exp / 2);
    else return Pow(base * base, exp / 2);
}

// (*!?) care needs to be taken when modulo > sqrt(state-machine's word-size)
uint64_t PowModulo(uint64_t base, uint64_t exp, uint64_t modulo) {
//    printf("Debug PowModulo - start\n");

    if(exp == 1) {
//        printf("Debug PowModulo - end last recursion\n");
        return base % modulo; }
    if(exp % 2 == 1) return (base * PowModulo((base * base) % modulo, exp / 2, modulo)) % modulo ;
    else return PowModulo((base * base) % modulo, exp / 2, modulo) % modulo;

}

uint64_t ComputeSignature(uint64_t n, uint64_t private_key, uint64_t message) {
    return PowModulo(message, private_key, n) % n;
}

bool isSignatureValid(uint64_t signature, uint64_t message, uint64_t public_key, uint64_t n) {
    if((Pow(signature, public_key) % n) == message) return true;
    else return false;
}

uint64_t isSignatureValid_v2(uint64_t signature, uint64_t message, uint64_t key_product, uint64_t n) {
    if((PowModulo(signature, key_product, n) % n) == message) return true;
    else return false;
}

bool areKeysValid(uint64_t keyA, uint64_t keyB, uint64_t phi) {
    if((keyA * keyB % phi) == 1) return true;
    else return false;
}

void Solve(uint64_t p, uint64_t q, uint64_t public_key, uint64_t message) {
    uint64_t private_key = ComputePrivateKey(public_key, ComputePhi(p, q));
    bool verify = areKeysValid(public_key, private_key, ComputePhi(p, q));
    if(verify) printf("areKeysValid: true\n"); else printf("areKeysValid: false\n");

    uint64_t signature = ComputeSignature(p * q, private_key, message);
    printf("primes: %lu %lu n: %lu phi: %lu\nkeys: %lu [private] %lu [public]\nmessage: %lu signature: %lu\n", p, q, p * q, ComputePhi(p, q), private_key, public_key, message, signature);

    verify = isSignatureValid(signature, message, public_key, p * q);
    if(verify) printf("isSignatureValid: true\n"); else printf("isSignatureValid: false\n");
    verify = isSignatureValid_v2(signature, message, public_key, p * q);
    if(verify) printf("isSignatureValid_v2: true\n"); else printf("isSignatureValid_v2: false\n");
    printf("message: %lu, signature: %lu, signature %% modulo: %lu, signature^public_key: %lu, signature^public_key %% modulo: %lu\n", message, Pow(message, private_key), signature, Pow(signature, public_key), Pow(signature, public_key) % (p * q));
}

#endif // CRYPTO_HPP_INCLUDED
