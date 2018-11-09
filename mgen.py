#!/usr/bin/python3
import msquared as m2

mgen = m2.MGen("./", project_include_dirs="./include")

# Main library.
sources = m2.wrap("src/", ["ArgumentParser"], ".cpp")
# Link libstealthcore.so for String
mgen.add_library("libsargs.so", sources=sources, install_directory="/usr/local/lib/", libraries="stealthcore")

# Install header
mgen.add_install("./include/interfaces/SArgs", install_directory="/usr/local/include/Stealth/")

# Add test executable
mgen.add_executable("test", sources="test/test.cpp", libraries="libsargs.so")

# Write a makefile.
mgen.write()
