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
typedef  int /*<<< orphan*/  insert ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ run_query (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char const*,char const*,scalar_t__,char const*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static UINT add_reglocator_entry( MSIHANDLE hdb, const char *sig, UINT root, const char *path,
                                  const char *name, UINT type )
{
    const char insert[] =
        "INSERT INTO `RegLocator` (`Signature_`, `Root`, `Key`, `Name`, `Type`) "
        "VALUES( '%s', %u, '%s', '%s', %u )";
    char *query;
    UINT sz, r;

    sz = strlen( sig ) + 10 + strlen( path ) + strlen( name ) + 10 + sizeof( insert );
    query = HeapAlloc( GetProcessHeap(), 0, sz );
    sprintf( query, insert, sig, root, path, name, type );
    r = run_query( hdb, query );
    HeapFree( GetProcessHeap(), 0, query );
    ok(r == ERROR_SUCCESS, "failed to insert into reglocator table: %u\n", r); \
    return r;
}