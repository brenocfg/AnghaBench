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
typedef  int WCHAR ;
struct TYPE_3__ {int value; } ;
typedef  TYPE_1__ NumberInstance ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DOUBLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  JS_E_INVALIDARG ; 
 int /*<<< orphan*/  JS_E_NUMBER_EXPECTED ; 
 int NUMBER_TOSTRING_BUF_SIZE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ TRUE ; 
 int floor (int) ; 
 int fmod (int,int) ; 
 int /*<<< orphan*/  is_finite (int) ; 
 int /*<<< orphan*/ * jsstr_alloc (int*) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int log (int) ; 
 TYPE_1__* number_this (int /*<<< orphan*/ *) ; 
 int pow (int,int) ; 
 int /*<<< orphan*/  sprintfW (int*,int const*,int,int) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT Number_toString(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    NumberInstance *number;
    INT radix = 10;
    DOUBLE val;
    jsstr_t *str;
    HRESULT hres;

    TRACE("\n");

    if(!(number = number_this(jsthis)))
        return throw_type_error(ctx, JS_E_NUMBER_EXPECTED, NULL);

    if(argc) {
        hres = to_int32(ctx, argv[0], &radix);
        if(FAILED(hres))
            return hres;

        if(radix<2 || radix>36)
            return throw_type_error(ctx, JS_E_INVALIDARG, NULL);
    }

    val = number->value;

    if(radix==10 || !is_finite(val)) {
        hres = to_string(ctx, jsval_number(val), &str);
        if(FAILED(hres))
            return hres;
    }else {
        INT idx = 0;
        DOUBLE integ, frac, log_radix = 0;
        WCHAR buf[NUMBER_TOSTRING_BUF_SIZE+16];
        BOOL exp = FALSE;

        if(val<0) {
            val = -val;
            buf[idx++] = '-';
        }

        while(1) {
            integ = floor(val);
            frac = val-integ;

            if(integ == 0)
                buf[idx++] = '0';
            while(integ>=1 && idx<NUMBER_TOSTRING_BUF_SIZE) {
                buf[idx] = fmod(integ, radix);
                if(buf[idx]<10) buf[idx] += '0';
                else buf[idx] += 'a'-10;
                integ /= radix;
                idx++;
            }

            if(idx<NUMBER_TOSTRING_BUF_SIZE) {
                INT beg = buf[0]=='-'?1:0;
                INT end = idx-1;
                WCHAR wch;

                while(end > beg) {
                    wch = buf[beg];
                    buf[beg++] = buf[end];
                    buf[end--] = wch;
                }
            }

            if(idx != NUMBER_TOSTRING_BUF_SIZE) buf[idx++] = '.';

            while(frac>0 && idx<NUMBER_TOSTRING_BUF_SIZE) {
                frac *= radix;
                buf[idx] = fmod(frac, radix);
                frac -= buf[idx];
                if(buf[idx]<10) buf[idx] += '0';
                else buf[idx] += 'a'-10;
                idx++;
            }

            if(idx==NUMBER_TOSTRING_BUF_SIZE && !exp) {
                exp = TRUE;
                idx = (buf[0]=='-') ? 1 : 0;
                log_radix = floor(log(val)/log(radix));
                val *= pow(radix, -log_radix);
                continue;
            }

            break;
        }

        while(buf[idx-1] == '0') idx--;
        if(buf[idx-1] == '.') idx--;

        if(exp) {
            if(log_radix==0)
                buf[idx] = 0;
            else {
                static const WCHAR formatW[] = {'(','e','%','c','%','d',')',0};
                WCHAR ch;

                if(log_radix<0) {
                    log_radix = -log_radix;
                    ch = '-';
                }
                else ch = '+';
                sprintfW(&buf[idx], formatW, ch, (int)log_radix);
            }
        }
        else buf[idx] = '\0';

        str = jsstr_alloc(buf);
        if(!str)
            return E_OUTOFMEMORY;
    }

    if(r)
        *r = jsval_string(str);
    else
        jsstr_release(str);
    return S_OK;
}