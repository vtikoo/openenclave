// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

#include <limits.h>
#include <openenclave/enclave.h>
#include <stdio.h>

#include "child_process_t.h"

void get_magic_ecall(void* pdata)
{
    if (pdata != 0)
    {
        *((uint32_t*)pdata) = 0x1234;
    }
}

OE_SET_ENCLAVE_SGX(
    1,    /* ProductID */
    1,    /* SecurityVersion */
    true, /* AllowDebug */
    1024, /* HeapPageCount */
    1024, /* StackPageCount */
    1);   /* TCSCount */
