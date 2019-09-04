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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int WORD ;
struct TYPE_9__ {int /*<<< orphan*/  time; } ;
struct TYPE_8__ {int dwLowDateTime; int /*<<< orphan*/  dwHighDateTime; } ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ FILETIME ;
typedef  TYPE_2__ DateInstance ;

/* Variables and functions */
#define  DISPATCH_CONSTRUCT 129 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  FileTimeToLocalFileTime (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_1__*) ; 
#define  INVOKE_FUNC 128 
 int /*<<< orphan*/  NO_HINT ; 
 int /*<<< orphan*/  S_OK ; 
 int TIME_EPOCH ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  create_date (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,int /*<<< orphan*/ **) ; 
 TYPE_2__* date_from_jsdisp (int /*<<< orphan*/ *) ; 
 double date_now () ; 
 int /*<<< orphan*/  date_parse (int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  date_to_string (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_utc (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 double time_clip (double) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  to_primitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utc (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static HRESULT DateConstr_value(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsdisp_t *date;
    HRESULT hres;

    TRACE("\n");

    switch(flags) {
    case DISPATCH_CONSTRUCT:
        switch(argc) {
        /* ECMA-262 3rd Edition    15.9.3.3 */
        case 0:
            hres = create_date(ctx, NULL, date_now(), &date);
            if(FAILED(hres))
                return hres;
            break;

        /* ECMA-262 3rd Edition    15.9.3.2 */
        case 1: {
            jsval_t prim;
            double n;

            hres = to_primitive(ctx, argv[0], &prim, NO_HINT);
            if(FAILED(hres))
                return hres;

            if(is_string(prim))
                hres = date_parse(get_string(prim), &n);
            else
                hres = to_number(ctx, prim, &n);

            jsval_release(prim);
            if(FAILED(hres))
                return hres;

            hres = create_date(ctx, NULL, time_clip(n), &date);
            if(FAILED(hres))
                return hres;
            break;
        }

        /* ECMA-262 3rd Edition    15.9.3.1 */
        default: {
            double ret_date;
            DateInstance *di;

            hres = date_utc(ctx, argc, argv, &ret_date);
            if(FAILED(hres))
                return hres;

            hres = create_date(ctx, NULL, ret_date, &date);
            if(FAILED(hres))
                return hres;

            di = date_from_jsdisp(date);
            di->time = utc(di->time, di);
        }
        }

        *r = jsval_obj(date);
        return S_OK;

    case INVOKE_FUNC: {
        FILETIME system_time, local_time;
        LONGLONG lltime;

        GetSystemTimeAsFileTime(&system_time);
        FileTimeToLocalFileTime(&system_time, &local_time);
        lltime = ((LONGLONG)local_time.dwHighDateTime<<32)
            + local_time.dwLowDateTime;

        return date_to_string(lltime/10000-TIME_EPOCH, FALSE, 0, r);
    }

    default:
        FIXME("unimplemented flags %x\n", flags);
        return E_NOTIMPL;
    }

    return S_OK;
}