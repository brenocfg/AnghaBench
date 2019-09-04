#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  char WCHAR ;
struct TYPE_5__ {int bias; int /*<<< orphan*/  time; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DateInstance ;
typedef  int /*<<< orphan*/  DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  JS_E_DATE_EXPECTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 TYPE_1__* date_this (int /*<<< orphan*/ *) ; 
 int daylight_saving_ta (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ hour_from_time (int /*<<< orphan*/ ) ; 
 scalar_t__ isnan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsstr_alloc (char*) ; 
 int /*<<< orphan*/ * jsstr_nan () ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_time (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ min_from_time (int /*<<< orphan*/ ) ; 
 scalar_t__ sec_from_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int,int,int,...) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Date_toTimeString(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    static const WCHAR formatW[] = { '%','0','2','d',':','%','0','2','d',':','%','0','2','d',
        ' ','U','T','C','%','c','%','0','2','d','%','0','2','d',0 };
    static const WCHAR formatUTCW[] = { '%','0','2','d',':','%','0','2','d',
        ':','%','0','2','d',' ','U','T','C',0 };
    DateInstance *date;
    jsstr_t *date_str;
    WCHAR buf[32];
    DOUBLE time;
    WCHAR sign;
    int offset;

    TRACE("\n");

    if(!(date = date_this(jsthis)))
        return throw_type_error(ctx, JS_E_DATE_EXPECTED, NULL);

    if(isnan(date->time)) {
        if(r)
            *r = jsval_string(jsstr_nan());
        return S_OK;
    }

    time = local_time(date->time, date);

    if(r) {
        offset = date->bias +
            daylight_saving_ta(time, date);

        if(offset < 0) {
            sign = '+';
            offset = -offset;
        }
        else sign = '-';

        if(offset)
            sprintfW(buf, formatW, (int)hour_from_time(time),
                    (int)min_from_time(time), (int)sec_from_time(time),
                    sign, offset/60, offset%60);
        else
            sprintfW(buf, formatUTCW, (int)hour_from_time(time),
                    (int)min_from_time(time), (int)sec_from_time(time));

        date_str = jsstr_alloc(buf);
        if(!date_str)
            return E_OUTOFMEMORY;

        *r = jsval_string(date_str);
    }
    return S_OK;
}