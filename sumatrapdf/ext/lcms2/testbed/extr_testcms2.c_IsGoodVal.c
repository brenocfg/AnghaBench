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
typedef  scalar_t__ cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Fail (char*,char const*,scalar_t__,scalar_t__) ; 
 scalar_t__ MaxErr ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ fabs (scalar_t__) ; 

cmsBool IsGoodVal(const char *title, cmsFloat64Number in, cmsFloat64Number out, cmsFloat64Number max)
{
    cmsFloat64Number Err = fabs(in - out);

    if (Err > MaxErr) MaxErr = Err;

        if ((Err > max )) {

              Fail("(%s): Must be %f, But is %f ", title, in, out);
              return FALSE;
              }

       return TRUE;
}