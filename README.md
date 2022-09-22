NAIF, C SPICE Toolkit
=====================

This mirror of NAIF SPICE Toolkit adds support for meson builds.

Headers
-------

I have eliminated header duplication and placed all headers under `include/cspice`.

Programs
--------

`cspice` and `csupport` are static libraries. For each of the program subdirectories in `src`, all `.pgm` files are grouped in local static libraries, and the `main.x` programs are renamed appropriately and linked against the local library, as well as the base `cspice` and `csupport` libraries. The process is described in the original Makefile-like scripts.
