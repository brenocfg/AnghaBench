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
struct table {scalar_t__ num_rows; scalar_t__ data; } ;
struct record_pnpentity {int /*<<< orphan*/  device_id; } ;
struct expr {int dummy; } ;
typedef  enum fill_status { ____Placeholder_fill_status } fill_status ;
typedef  int /*<<< orphan*/  devinfo ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int cbSize; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SP_DEVINFO_DATA ;
typedef  int /*<<< orphan*/  HDEVINFO ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int DIGCF_ALLCLASSES ; 
 int DIGCF_PRESENT ; 
 int FILL_STATUS_UNFILTERED ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetupDiDestroyDeviceInfoList (int /*<<< orphan*/ ) ; 
 scalar_t__ SetupDiEnumDeviceInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SetupDiGetClassDevsW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SetupDiGetDeviceInstanceIdW (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_row_values (struct table*,scalar_t__) ; 
 int /*<<< orphan*/  heap_strdupW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  match_row (struct table*,scalar_t__,struct expr const*,int*) ; 
 int /*<<< orphan*/  resize_table (struct table*,scalar_t__,int) ; 

__attribute__((used)) static enum fill_status fill_pnpentity( struct table *table, const struct expr *cond )
{
    struct record_pnpentity *rec;
    enum fill_status status = FILL_STATUS_UNFILTERED;
    HDEVINFO device_info_set;
    SP_DEVINFO_DATA devinfo = {0};
    DWORD idx;

    device_info_set = SetupDiGetClassDevsW( NULL, NULL, NULL, DIGCF_ALLCLASSES|DIGCF_PRESENT );

    devinfo.cbSize = sizeof(devinfo);

    idx = 0;
    while (SetupDiEnumDeviceInfo( device_info_set, idx++, &devinfo ))
    {
        /* noop */
    }

    resize_table( table, idx, sizeof(*rec) );
    table->num_rows = 0;
    rec = (struct record_pnpentity *)table->data;

    idx = 0;
    while (SetupDiEnumDeviceInfo( device_info_set, idx++, &devinfo ))
    {
        WCHAR device_id[MAX_PATH];
        if (SetupDiGetDeviceInstanceIdW( device_info_set, &devinfo, device_id,
                    ARRAY_SIZE(device_id), NULL ))
        {
            rec->device_id = heap_strdupW( device_id );

            table->num_rows++;
            if (!match_row( table, table->num_rows - 1, cond, &status ))
            {
                free_row_values( table, table->num_rows - 1 );
                table->num_rows--;
            }
            else
                rec++;
        }
    }

    SetupDiDestroyDeviceInfoList( device_info_set );

    return status;
}