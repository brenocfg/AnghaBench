#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_4__ {int /*<<< orphan*/ * FreeCredentialsHandle; scalar_t__ Initialize; } ;
typedef  TYPE_1__* PSECPKG_FUNCTION_TABLE ;
typedef  scalar_t__ PBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t SECPKG_FUNCTION_TABLE_SIZE_1 ; 
 size_t SECPKG_FUNCTION_TABLE_SIZE_2 ; 
 size_t SECPKG_FUNCTION_TABLE_SIZE_3 ; 
 size_t SECPKG_FUNCTION_TABLE_SIZE_4 ; 
 size_t SECPKG_FUNCTION_TABLE_SIZE_5 ; 
 size_t SECPKG_FUNCTION_TABLE_SIZE_6 ; 
 size_t SECPKG_FUNCTION_TABLE_SIZE_7 ; 
 scalar_t__ SECPKG_INTERFACE_VERSION ; 
 scalar_t__ SECPKG_INTERFACE_VERSION_2 ; 
 scalar_t__ SECPKG_INTERFACE_VERSION_3 ; 
 scalar_t__ SECPKG_INTERFACE_VERSION_4 ; 
 scalar_t__ SECPKG_INTERFACE_VERSION_5 ; 
 scalar_t__ SECPKG_INTERFACE_VERSION_6 ; 
 scalar_t__ SECPKG_INTERFACE_VERSION_7 ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static PSECPKG_FUNCTION_TABLE getNextSecPkgTable(PSECPKG_FUNCTION_TABLE pTable,
                                                 ULONG Version)
{
    size_t size;
    PSECPKG_FUNCTION_TABLE pNextTable;

    if (Version == SECPKG_INTERFACE_VERSION)
        size = SECPKG_FUNCTION_TABLE_SIZE_1;
    else if (Version == SECPKG_INTERFACE_VERSION_2)
        size = SECPKG_FUNCTION_TABLE_SIZE_2;
    else if (Version == SECPKG_INTERFACE_VERSION_3)
        size = SECPKG_FUNCTION_TABLE_SIZE_3;
    else if (Version == SECPKG_INTERFACE_VERSION_4)
        size = SECPKG_FUNCTION_TABLE_SIZE_4;
    else if (Version == SECPKG_INTERFACE_VERSION_5)
        size = SECPKG_FUNCTION_TABLE_SIZE_5;
    else if (Version == SECPKG_INTERFACE_VERSION_6)
        size = SECPKG_FUNCTION_TABLE_SIZE_6;
    else if (Version == SECPKG_INTERFACE_VERSION_7)
        size = SECPKG_FUNCTION_TABLE_SIZE_7;
    else {
        ok(FALSE, "Unknown package version 0x%x\n", Version);
        return NULL;
    }

    pNextTable = (PSECPKG_FUNCTION_TABLE)((PBYTE)pTable + size);
    /* Win7 function tables appear to be SECPKG_INTERFACE_VERSION_6 format,
       but unfortunately SpLsaModeInitialize returns SECPKG_INTERFACE_VERSION_3.
       We detect that by comparing the "Initialize" pointer from the old table
       to the "FreeCredentialsHandle" pointer of the new table. These functions
       have different numbers of arguments, so they can't possibly point to the
       same implementation */
    if (broken((void *) pTable->Initialize == (void *) pNextTable->FreeCredentialsHandle &&
               pNextTable->FreeCredentialsHandle != NULL))
    {
        win_skip("Invalid function pointers for next package\n");
        return NULL;
    }

    return pNextTable;
}