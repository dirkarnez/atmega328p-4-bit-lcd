EIE3105_ATmega328P_Application
==============================
### Reference
- [Optimize Options (Using the GNU Compiler Collection (GCC))](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)

### Notes
- GoogleTest does not support C project, therefore
    - Force CMake to compile C source (`main.c`) with as C++ source:
        - `set_source_files_properties("main.c" PROPERTIES LANGUAGE CXX)`