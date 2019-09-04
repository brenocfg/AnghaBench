#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* bitsnum; int /*<<< orphan*/  sign; } ;
typedef  TYPE_2__ VARIANT_DI ;
struct TYPE_7__ {scalar_t__ m_lo; scalar_t__ m_hi; int exp_bias; int /*<<< orphan*/  sign; } ;
struct TYPE_9__ {double d; TYPE_1__ i; } ;
typedef  TYPE_3__ R8_FIELDS ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_BADVARTYPE ; 
 int /*<<< orphan*/  DISP_E_OVERFLOW ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VARIANT_DI_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  VARIANT_DI_normalize (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT VARIANT_DI_FromR8(double source, VARIANT_DI * dest)
{
    HRESULT hres = S_OK;
    R8_FIELDS fx;

    fx.d = source;

    /* Detect special cases */
    if (fx.i.m_lo == 0 && fx.i.m_hi == 0 && fx.i.exp_bias == 0) {
        /* Floating-point zero */
        VARIANT_DI_clear(dest);
    } else if (fx.i.m_lo == 0 && fx.i.m_hi == 0 && fx.i.exp_bias == 0x7FF) {
        /* Floating-point infinity */
        hres = DISP_E_OVERFLOW;
    } else if (fx.i.exp_bias == 0x7FF) {
        /* Floating-point NaN */
        hres = DISP_E_BADVARTYPE;
    } else {
        int exponent2;
        VARIANT_DI_clear(dest);

        exponent2 = fx.i.exp_bias - 1023;   /* Get unbiased exponent */
        dest->sign = fx.i.sign;             /* Sign is simply copied */

        /* Copy significant bits to VARIANT_DI mantissa */
        dest->bitsnum[0] = fx.i.m_lo;
        dest->bitsnum[1] = fx.i.m_hi;
        dest->bitsnum[1] &= 0x000FFFFF;
        if (fx.i.exp_bias == 0) {
            /* Denormalized number - correct exponent */
            exponent2++;
        } else {
            /* Add hidden bit to mantissa */
            dest->bitsnum[1] |= 0x00100000;
        }

        /* The act of copying a FP mantissa as integer bits is equivalent to
           shifting left the mantissa 52 bits. The exponent2 is reduced to
           compensate. */
        exponent2 -= 52;

        hres = VARIANT_DI_normalize(dest, exponent2, TRUE);
    }

    return hres;
}