#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {TYPE_1__* package; } ;
struct TYPE_9__ {int len; } ;
struct TYPE_8__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ FORMSTR ;
typedef  TYPE_3__ FORMAT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  get_formstr_data (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 scalar_t__ msi_get_property (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static WCHAR *deformat_property( FORMAT *format, FORMSTR *str, int *ret_len )
{
    WCHAR *prop, *ret;
    DWORD len = 0;
    UINT r;

    if (!(prop = msi_alloc( (str->len + 1) * sizeof(WCHAR) ))) return NULL;
    lstrcpynW( prop, get_formstr_data(format, str), str->len + 1 );

    r = msi_get_property( format->package->db, prop, NULL, &len );
    if (r != ERROR_SUCCESS && r != ERROR_MORE_DATA)
    {
        msi_free( prop );
        return NULL;
    }
    len++;
    if ((ret = msi_alloc( len * sizeof(WCHAR) )))
        msi_get_property( format->package->db, prop, ret, &len );
    msi_free( prop );
    *ret_len = len;
    return ret;
}