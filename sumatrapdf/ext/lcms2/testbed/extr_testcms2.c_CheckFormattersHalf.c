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
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  Fail (char*,int,int) ; 
 int _cmsFloat2Half (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsHalf2Float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_isfinite (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsInt32Number CheckFormattersHalf(void)
{
    int i, j;


    for (i=0; i < 0xffff; i++) {

        cmsFloat32Number f = _cmsHalf2Float((cmsUInt16Number) i);

        if (!my_isfinite(f))  {

            j = _cmsFloat2Half(f);

            if (i != j) {
                Fail("%d != %d in Half float support!\n", i, j);
                return 0;
            }
        }
    }

    return 1;
}