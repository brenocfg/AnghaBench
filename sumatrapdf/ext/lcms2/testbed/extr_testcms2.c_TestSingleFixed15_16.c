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
typedef  int /*<<< orphan*/  cmsS15Fixed16Number ;
typedef  int cmsInt32Number ;
typedef  scalar_t__ cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 scalar_t__ FIXED_PRECISION_15_16 ; 
 scalar_t__ _cms15Fixed16toDouble (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsDoubleTo15Fixed16 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fabs (scalar_t__) ; 

__attribute__((used)) static
cmsInt32Number TestSingleFixed15_16(cmsFloat64Number d)
{
    cmsS15Fixed16Number f = _cmsDoubleTo15Fixed16(DbgThread(), d);
    cmsFloat64Number RoundTrip = _cms15Fixed16toDouble(DbgThread(), f);
    cmsFloat64Number Error     = fabs(d - RoundTrip);

    return ( Error <= FIXED_PRECISION_15_16);
}