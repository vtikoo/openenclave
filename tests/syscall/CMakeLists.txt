# Copyright (c) Open Enclave SDK contributors.
# Licensed under the MIT License.

add_subdirectory(cpio)
add_subdirectory(resolver)
add_subdirectory(socket)
add_subdirectory(tool)

# Skip the filesystem-related tests when doing code coverage tests.
if (NOT CODE_COVERAGE)
    add_subdirectory(dup)
    add_subdirectory(fs)
    add_subdirectory(hostfs)
endif()

if(UNIX)
    add_subdirectory(datagram)
    add_subdirectory(epoll)
    add_subdirectory(ids)
    add_subdirectory(poller)
    add_subdirectory(sendmsg)
    add_subdirectory(socketpair)
endif()
