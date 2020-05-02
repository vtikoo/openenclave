# Copyright (c) Open Enclave SDK contributors.
# Licensed under the MIT License.

add_enclave_library(gcov STATIC
  # Only the following three files are required to support GCOV-based code coverage analysis.
  src/GCDAProfiling.c
  src/InstrProfiling.c
  src/InstrProfilingUtil.c)

maybe_build_using_clangw(gcov)

enclave_compile_options(gcov PRIVATE -Wno-error)

enclave_link_libraries(gcov PRIVATE oelibc oehostfs)

enclave_include_directories(gcov PRIVATE src)

install(TARGETS gcov
    EXPORT openenclave-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/openenclave/enclave)
