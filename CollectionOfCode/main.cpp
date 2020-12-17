extern void Union_v1(void);  // apparently, doing it without a header file is just fine,
extern void Union_v2(void);  // but it's like trying to use a library without having code
    // autocomplete and having to memorize all the identifiers, and there is no
    // help when making a typo; as such, bindings are useful for this, and defining
    // a Union.hpp and externing things there would be exactly that

int main() {
    Union_v2(); // won't crash
    Union_v1(); // might crash - undefined behaviour
}
