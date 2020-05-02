# Copyright (c) Open Enclave SDK contributors.
# Licensed under the MIT License.

add_enclave_library(oehostresolver STATIC hostresolver.c)

maybe_build_using_clangw(oehostresolver)

enclave_include_directories(oehostresolver PRIVATE
    ${CMAKE_BINARY_DIR}/syscall
    ${PROJECT_SOURCE_DIR}/include/openenclave/corelibc)

if (CODE_COVERAGE)
    # Enable code coverage.
    enclave_compile_options(oehostresolver PRIVATE -fprofile-arcs -ftest-coverage)
    # Link against libgcov.
    enclave_link_libraries(oehostresolver PRIVATE gcov)
endif()

enclave_link_libraries(oehostresolver PRIVATE oesyscall)

install_enclaves(TARGETS oehostresolver EXPORT openenclave-targets ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/openenclave/enclave)
