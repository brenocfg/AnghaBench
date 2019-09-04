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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_4__ {int /*<<< orphan*/  time; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DateInstance ;
typedef  int DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  JS_E_DATE_EXPECTED ; 
 int NAN ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 TYPE_1__* date_this (int /*<<< orphan*/ *) ; 
 scalar_t__ isnan (int) ; 
 int /*<<< orphan*/  jsval_number (int) ; 
 int local_time (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int year_from_time (int) ; 

__attribute__((used)) static HRESULT Date_getYear(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    DateInstance *date;
    DOUBLE t, year;

    TRACE("\n");

    if(!(date = date_this(jsthis)))
        return throw_type_error(ctx, JS_E_DATE_EXPECTED, NULL);

    t = local_time(date->time, date);
    if(isnan(t)) {
        if(r)
            *r = jsval_number(NAN);
        return S_OK;
    }

    year = year_from_time(t);
    if(r)
        *r = jsval_number((1900<=year && year<2000)?year-1900:year);
    return S_OK;
}