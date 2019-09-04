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
struct TYPE_3__ {scalar_t__* ids; int id_cnt; int /*<<< orphan*/  tid; } ;
typedef  TYPE_1__ cp_static_data_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DISPID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_dispids (int /*<<< orphan*/ ,int*,scalar_t__**) ; 

__attribute__((used)) static BOOL is_cp_event(cp_static_data_t *data, DISPID dispid)
{
    int min, max, i;
    HRESULT hres;

    if(!data)
        return FALSE;

    if(!data->ids) {
        hres = get_dispids(data->tid, &data->id_cnt, &data->ids);
        if(FAILED(hres))
            return FALSE;
    }

    min = 0;
    max = data->id_cnt-1;
    while(min <= max) {
        i = (min+max)/2;
        if(data->ids[i] == dispid)
            return TRUE;

        if(data->ids[i] < dispid)
            min = i+1;
        else
            max = i-1;
    }

    return FALSE;
}