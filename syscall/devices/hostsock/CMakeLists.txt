# Copyright (c) Open Enclave SDK contributors.
# Licensed under the MIT License.

add_enclave_library(oehostsock STATIC hostsock.c)

maybe_build_using_clangw(oehostsock)

enclave_include_directories(oehostsock PRIVATE
    ${CMAKE_BINARY_DIR}/syscall
    ${PROJECT_SOURCE_DIR}/include/openenclave/corelibc)

if (CODE_COVERAGE)
    # Enable code coverage.
    enclave_compile_options(oehostsock PRIVATE -g -O0 -fprofile-arcs -ftest-coverage)
    # Link against libgcov.
    enclave_link_libraries(oehostsock PRIVATE gcov)
endif()

enclave_link_libraries(oehostsock PRIVATE oesyscall)

install_enclaves(TARGETS oehostsock EXPORT openenclave-targets ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/openenclave/enclave)
