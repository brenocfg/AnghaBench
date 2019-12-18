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
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  char const* DWORD ;

/* Variables and functions */
 char const* ERROR_INVALID_PARAMETER ; 
 char* GetLastError () ; 
 char* get_string_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,char const*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static const char *check_key( INFCONTEXT *context, const char *wanted )
{
    const char *key = get_string_field( context, 0 );
    DWORD err = GetLastError();

    if (!key)
    {
        ok( !wanted, "missing key %s\n", wanted );
        ok( err == 0 || err == ERROR_INVALID_PARAMETER, "last error set to %u\n", err );
    }
    else
    {
        ok( !strcmp( key, wanted ), "bad key %s/%s\n", key, wanted );
        ok( err == 0, "last error set to %u\n", err );
    }
    return key;
}