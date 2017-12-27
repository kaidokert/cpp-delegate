#include "gzilt/delegate.hpp"

#include <iostream>

void delegate_test();

int main(int, char **) {
    delegate_test();
    return 0;
}

using std::cout;
using std::endl;

static volatile bool dummy = false;

struct large {
    int lots_of_bits[16384 + 1];
};

bool demo_free(int para, int const &byref);
bool demo_free(int para, int const &byref) {
    cout << "Executed free function " << para << " " << byref << endl;
    return dummy;
}

struct struct_1 {
    bool demo(int para, int const &byref) {
        cout << "Executed member 1 " << para << " " << byref << endl;
        return dummy;
    }
};

struct struct_2 {
    bool demo2(int para, int const &byref) {
        cout << "Executed member 2 " << para << " " << byref << endl;
        return dummy;
    }
    void eats_bits_byref(large &bits) {
        bits.lots_of_bits[0] = 42;
    }
    void eats_bits_whole(large bits) {
        bits.lots_of_bits[0] = 42;
        cout << "No bits were harmed " << bits.lots_of_bits[0] << endl;
    }
    void const_demo(int para) const {
        cout << "Const here, didnt do much " << para << endl;
    }
};

void delegate_test() {
    struct_1 test_1;
    struct_2 test_2;
    int angstroms = 5;

    // create delegate to member and invoke
    auto delegate = CREATE_DELEGATE(&struct_1::demo, &test_1);
    delegate.invoke(2, angstroms);

    // reassign to a different class
    delegate = CREATE_DELEGATE(&struct_2::demo2, &test_2);
    delegate.invoke(4, angstroms);
    // invoke by () operator
    delegate(4, angstroms);

    // create delegate to free function
    auto free_delegate = CREATE_DELEGATE(&demo_free);
    free_delegate.invoke(4, angstroms);

    // reassign free delegate to member and call again
    delegate = free_delegate;
    delegate(10, angstroms);

    // making big moves
    large bits;
    auto large_1 = CREATE_DELEGATE(&struct_2::eats_bits_byref, &test_2);
    large_1(bits);

    auto large_2 = CREATE_DELEGATE(&struct_2::eats_bits_whole, &test_2);
    large_2(bits);

    // make a const delegate and call it
    auto const_delegate = CREATE_DELEGATE(&struct_2::const_demo, &test_2);
    const_delegate(angstroms);
}

// global new/delete overrides to make sure no allocations happen

#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wunknown-warning-option"
#endif
#pragma GCC diagnostic ignored "-Wsuggest-attribute=pure"

/* LCOV_EXCL_START */

static volatile void * p = nullptr;
void* operator new(std::size_t) {
    cout << "No allocations, sire" << endl;
    return const_cast<void *>(p);
}
#if !defined(_MSC_VER) || (_MSC_VER > 1800)  // missing noexcept
void operator delete(void* ptr) noexcept {
    p = ptr;
}
#endif

/* LCOV_EXCL_STOP */
