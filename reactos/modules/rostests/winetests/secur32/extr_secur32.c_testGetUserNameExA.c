#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int ULONG ;
typedef  size_t UINT ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_NONE_MAPPED ; 
 scalar_t__ ERROR_NO_SUCH_USER ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ NameDnsDomain ; 
 scalar_t__ NameSamCompatible ; 
 scalar_t__ NameUnknown ; 
 int /*<<< orphan*/  ZeroMemory (char*,int) ; 
 scalar_t__ broken (int) ; 
 scalar_t__* formats ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pGetUserNameExA (scalar_t__,char*,int*) ; 

__attribute__((used)) static void testGetUserNameExA(void)
{
    char name[256];
    ULONG size;
    BOOLEAN rc;
    UINT i;

    for (i = 0; i < ARRAY_SIZE(formats); i++) {
        size = sizeof(name);
        ZeroMemory(name, sizeof(name));
        rc = pGetUserNameExA(formats[i], name, &size);
        ok(rc ||
           (formats[i] == NameUnknown &&
            GetLastError() == ERROR_NO_SUCH_USER) ||
           GetLastError() == ERROR_NONE_MAPPED ||
           broken(formats[i] == NameDnsDomain &&
                  GetLastError() == ERROR_INVALID_PARAMETER),
           "GetUserNameExW(%d) failed: %d\n",
           formats[i], GetLastError());
    }

    if (0) /* Crashes on Windows */
        pGetUserNameExA(NameSamCompatible, NULL, NULL);

    size = 0;
    rc = pGetUserNameExA(NameSamCompatible, NULL, &size);
    ok(! rc && GetLastError() == ERROR_MORE_DATA, "Expected fail with ERROR_MORE_DATA, got %d with %u\n", rc, GetLastError());
    ok(size != 0, "Expected size to be set to required size\n");

    if (0) /* Crashes on Windows with big enough size */
    {
        /* Returned size is already big enough */
        pGetUserNameExA(NameSamCompatible, NULL, &size);
    }

    size = 0;
    rc = pGetUserNameExA(NameSamCompatible, name, &size);
    ok(! rc && GetLastError() == ERROR_MORE_DATA, "Expected fail with ERROR_MORE_DATA, got %d with %u\n", rc, GetLastError());
    ok(size != 0, "Expected size to be set to required size\n");
    size = 1;
    name[0] = 0xff;
    rc = pGetUserNameExA(NameSamCompatible, name, &size);
    ok(! rc && GetLastError() == ERROR_MORE_DATA, "Expected fail with ERROR_MORE_DATA, got %d with %u\n", rc, GetLastError());
    ok(1 < size, "Expected size to be set to required size\n");
    ok(name[0] == (char) 0xff, "Expected unchanged buffer\n");
}