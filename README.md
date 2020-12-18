http://en.wikipedia.org/wiki/Opaque_pointer#C

#cmake uses build and running
cd build/
cmake -I/lib ..
cmake --build .
./main


Debug build
cmake -DCMAKE_BUILD_TYPE=Debug <path>

Release build
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo <path>



#Upcoming warning for debug?
    Werror: Treat warnings as errors. I like this one because it forces me to fix warnings. Also it makes it impossible to miss a warning. Without that flag a warning is generated when compiling, but you might miss it. Later compilation doesn’t touch that file again, so the warnings is not emitted again.

    -pedantic-errors: This enables strict standard conformance, basically. Note that this is not equivalent to -Werror -pedantic, because why would it?

    -Wall: A better name would be -Wcommon. It enables common warnings like use of uninitialized variables.

    -Wextra: Some more common warnings not enabled by -Wall.

    -Wconversion: Enables warnings about conversions that might change the value like float to int.

    -Wsign-conversion: Enables warnings about conversions between signed and unsigned. Somewhat annoying, but still useful. Note that it is not covered by -Wconversion in C++ mode (for some reason).


#Sources
https://github.com/ttroy50/cmake-examples