exhaustive32
============

Empirically prove whether a math function is float32-commutative or not by an exhaustive search on the float32 space

The "float32 commutativity property" is the following one: for a given float F, for a given function f64 with the
signature (double) -> double, and the float32 equivalent f32 (float) -> float, do we have:

`f32(F) == ToFloat32(f64(ToFloat64(F)))`

For more context, see also [this blog post](https://blog.mozilla.org/javascript/2013/11/07/efficient-float32-arithmetic-in-javascript/).

modes
=====

There are two modes:

- `CHECK_PROPERTY` begins to iterate over all floats and stops at the first error it can find, if there are any. It allows to just verify whether the property holds or not, for a given function.

- `COUNT` iterates over the entire float32 space and counts the number of errors made by approximating the function by the float function.

For now, the mode has to be changed by hand in the main function.

compile
=======

Compile with `g++ -std=c++11 main.cpp`

license
===

MIT
