# Copyright (c) Open Enclave SDK contributors.
# Licensed under the MIT License.

add_enclave_library(oehostepoll STATIC hostepoll.c)

maybe_build_using_clangw(oehostepoll)

enclave_include_directories(oehostepoll PRIVATE
    ${CMAKE_BINARY_DIR}/syscall
    ${PROJECT_SOURCE_DIR}/include/openenclave/corelibc)

if (CODE_COVERAGE)
    # Enable code coverage.
    enclave_compile_options(oehostepoll PRIVATE -g -O0 -fprofile-arcs -ftest-coverage)
    # Link against libgcov.
    enclave_link_libraries(oehostepoll PRIVATE gcov)
endif()

enclave_link_libraries(oehostepoll PRIVATE oesyscall)

install_enclaves(TARGETS oehostepoll EXPORT openenclave-targets ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/openenclave/enclave)
