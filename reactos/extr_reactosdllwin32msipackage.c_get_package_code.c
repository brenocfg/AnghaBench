#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  storage; } ;
struct TYPE_8__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSISUMMARYINFO ;
typedef  TYPE_2__ MSIDATABASE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  PID_REVNUMBER ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 scalar_t__ msi_get_db_suminfo (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ msi_get_suminfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/ * msi_suminfo_dup_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static WCHAR *get_package_code( MSIDATABASE *db )
{
    WCHAR *ret;
    MSISUMMARYINFO *si;
    UINT r;

    r = msi_get_suminfo( db->storage, 0, &si );
    if (r != ERROR_SUCCESS)
    {
        r = msi_get_db_suminfo( db, 0, &si );
        if (r != ERROR_SUCCESS)
        {
            WARN("failed to load summary info %u\n", r);
            return NULL;
        }
    }
    ret = msi_suminfo_dup_string( si, PID_REVNUMBER );
    msiobj_release( &si->hdr );
    return ret;
}