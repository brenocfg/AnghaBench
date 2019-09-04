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

/* Variables and functions */
 int /*<<< orphan*/  EDOM ; 
 scalar_t__ _isnan (double) ; 
 int /*<<< orphan*/  errno ; 

double ldexp (double value, int exp)
{
#ifdef __GNUC__
    register double result;
#endif

    /* Check for value correctness
     * and set errno if required
     */
    if (_isnan(value))
    {
        errno = EDOM;
    }

#ifdef __GNUC__
    asm ("fscale"
         : "=t" (result)
         : "0" (value), "u" ((double)exp)
         : "1");
    return result;
#else /* !__GNUC__ */
    __asm
    {
        fild exp
        fld value
        fscale
        fstp st(1)
    }

    /* "fstp st(1)" has copied st(0) to st(1), then popped the FPU stack,
     * so that the value is again in st(0) now. Effectively, we have reduced
     * the FPU stack by one element while preserving st(0).
     * st(0) is also the register used for returning a double value. */
#endif /* !__GNUC__ */
}