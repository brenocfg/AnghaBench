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
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  scalar_t__ cmsS15Fixed16Number ;
typedef  int cmsInt32Number ;
typedef  scalar_t__ cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 scalar_t__ FIXED_PRECISION_8_8 ; 
 scalar_t__ _cms8Fixed8toDouble (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _cmsDoubleTo8Fixed8 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fabs (scalar_t__) ; 

__attribute__((used)) static
cmsInt32Number TestSingleFixed8_8(cmsFloat64Number d)
{
    cmsS15Fixed16Number f = _cmsDoubleTo8Fixed8(DbgThread(), d);
    cmsFloat64Number RoundTrip = _cms8Fixed8toDouble(DbgThread(), (cmsUInt16Number) f);
    cmsFloat64Number Error     = fabs(d - RoundTrip);

    return ( Error <= FIXED_PRECISION_8_8);
}