# bspwmbar

# build current pacakage
./configure
make config
make
make install

# debug build with AddressSanitizer
make debug

# static analyze with clang
scan-build make debug

