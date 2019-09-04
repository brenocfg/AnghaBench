#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int num_langids; int /*<<< orphan*/ * langids; void* platform; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  MSISUMMARYINFO ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  LANGID ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INSTALL_PLATFORM_UNSUPPORTED ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  ERROR_PATCH_PACKAGE_INVALID ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  PID_PAGECOUNT ; 
 int /*<<< orphan*/  PID_TEMPLATE ; 
 void* PLATFORM_UNKNOWN ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoiW (scalar_t__*) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (scalar_t__*) ; 
 scalar_t__* msi_suminfo_dup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_suminfo_get_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* parse_platform (scalar_t__*) ; 
 scalar_t__* strchrW (scalar_t__*,char) ; 

__attribute__((used)) static UINT parse_suminfo( MSISUMMARYINFO *si, MSIPACKAGE *package )
{
    WCHAR *template, *p, *q, *platform;
    DWORD i, count;

    package->version = msi_suminfo_get_int32( si, PID_PAGECOUNT );
    TRACE("version: %d\n", package->version);

    template = msi_suminfo_dup_string( si, PID_TEMPLATE );
    if (!template)
        return ERROR_SUCCESS; /* native accepts missing template property */

    TRACE("template: %s\n", debugstr_w(template));

    p = strchrW( template, ';' );
    if (!p)
    {
        WARN("invalid template string %s\n", debugstr_w(template));
        msi_free( template );
        return ERROR_PATCH_PACKAGE_INVALID;
    }
    *p = 0;
    platform = template;
    if ((q = strchrW( platform, ',' ))) *q = 0;
    package->platform = parse_platform( platform );
    while (package->platform == PLATFORM_UNKNOWN && q)
    {
        platform = q + 1;
        if ((q = strchrW( platform, ',' ))) *q = 0;
        package->platform = parse_platform( platform );
    }
    if (package->platform == PLATFORM_UNKNOWN)
    {
        WARN("unknown platform %s\n", debugstr_w(template));
        msi_free( template );
        return ERROR_INSTALL_PLATFORM_UNSUPPORTED;
    }
    p++;
    if (!*p)
    {
        msi_free( template );
        return ERROR_SUCCESS;
    }
    count = 1;
    for (q = p; (q = strchrW( q, ',' )); q++) count++;

    package->langids = msi_alloc( count * sizeof(LANGID) );
    if (!package->langids)
    {
        msi_free( template );
        return ERROR_OUTOFMEMORY;
    }

    i = 0;
    while (*p)
    {
        q = strchrW( p, ',' );
        if (q) *q = 0;
        package->langids[i] = atoiW( p );
        if (!q) break;
        p = q + 1;
        i++;
    }
    package->num_langids = i + 1;

    msi_free( template );
    return ERROR_SUCCESS;
}