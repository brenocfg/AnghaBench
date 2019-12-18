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
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  scalar_t__ cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  IsGoodFixed15_16 (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int) ; 
 int cmsMAXCHANNELS ; 

__attribute__((used)) static
cmsInt32Number CompareFloatXFORM(cmsHTRANSFORM xform1, cmsHTRANSFORM xform2, cmsInt32Number nChan)
{
    cmsInt32Number i, j;
    cmsFloat32Number In[cmsMAXCHANNELS], Out1[cmsMAXCHANNELS], Out2[cmsMAXCHANNELS];

    for (j=0; j < 0xFFFF; j++) {

        for (i=0; i < nChan; i++) In[i] = (cmsFloat32Number) (j / 65535.0);;

        cmsDoTransform(DbgThread(), xform1, In, Out1, 1);
        cmsDoTransform(DbgThread(), xform2, In, Out2, 1);

        for (i=0; i < nChan; i++) {

           // We allow no difference in floating point
            if (!IsGoodFixed15_16("linear xform cmsFloat32Number", Out1[i], Out2[i]))
                return 0;
        }

    }

    return 1;
}