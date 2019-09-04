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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  time; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DateInstance ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*,double) ; 
 int /*<<< orphan*/  JS_E_DATE_EXPECTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ date_from_time (int /*<<< orphan*/ ) ; 
 TYPE_1__* date_this (int /*<<< orphan*/ *) ; 
 scalar_t__ hour_from_time (int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/ * jsstr_alloc (char*) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 scalar_t__ min_from_time (int /*<<< orphan*/ ) ; 
 scalar_t__ month_from_time (int /*<<< orphan*/ ) ; 
 scalar_t__ ms_from_time (int /*<<< orphan*/ ) ; 
 scalar_t__ sec_from_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int,...) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 double year_from_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT Date_toISOString(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    DateInstance *date;
    WCHAR buf[64], *p = buf;
    double year;

    static const WCHAR short_year_formatW[] = {'%','0','4','d',0};
    static const WCHAR long_year_formatW[] = {'%','0','6','d',0};
    static const WCHAR formatW[] = {'-','%','0','2','d','-','%','0','2','d',
        'T','%','0','2','d',':','%','0','2','d',':','%','0','2','d','.','%','0','3','d','Z',0};

    TRACE("\n");

    if(!(date = date_this(jsthis)))
        return throw_type_error(ctx, JS_E_DATE_EXPECTED, NULL);

    year = year_from_time(date->time);
    if(isnan(year) || year > 999999 || year < -999999) {
        FIXME("year %lf should throw an exception\n", year);
        return E_FAIL;
    }

    if(year < 0) {
        *p++ = '-';
        p += sprintfW(p, long_year_formatW, -(int)year);
    }else if(year > 9999) {
        *p++ = '+';
        p += sprintfW(p, long_year_formatW, (int)year);
    }else {
        p += sprintfW(p, short_year_formatW, (int)year);
    }

    sprintfW(p, formatW, (int)month_from_time(date->time) + 1, (int)date_from_time(date->time),
             (int)hour_from_time(date->time), (int)min_from_time(date->time),
             (int)sec_from_time(date->time), (int)ms_from_time(date->time));

    if(r) {
        jsstr_t *ret;
        if(!(ret = jsstr_alloc(buf)))
            return E_OUTOFMEMORY;
        *r = jsval_string(ret);
    }
    return S_OK;
}