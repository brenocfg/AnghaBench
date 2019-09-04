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
typedef  int /*<<< orphan*/  vbdisp_t ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  VarWeekdayName (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  return_bstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_int (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static HRESULT Global_WeekdayName(vbdisp_t *This, VARIANT *args, unsigned args_cnt, VARIANT *res)
{
    int weekday, first_day = 1, abbrev = 0;
    BSTR ret;
    HRESULT hres;

    TRACE("\n");

    assert(1 <= args_cnt && args_cnt <= 3);

    hres = to_int(args, &weekday);
    if(FAILED(hres))
        return hres;

    if(args_cnt > 1) {
        hres = to_int(args+1, &abbrev);
        if(FAILED(hres))
            return hres;

        if(args_cnt == 3) {
            hres = to_int(args+2, &first_day);
            if(FAILED(hres))
                return hres;
        }
    }

    hres = VarWeekdayName(weekday, abbrev, first_day, 0, &ret);
    if(FAILED(hres))
        return hres;

    return return_bstr(res, ret);
}