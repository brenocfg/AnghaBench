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
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int cmsInt32Number ;
typedef  float cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsPipelineEvalFloat (int /*<<< orphan*/ ,float*,float*,int /*<<< orphan*/ *) ; 
 scalar_t__ floor (float) ; 

__attribute__((used)) static
cmsInt32Number CheckFloatLUT(cmsPipeline* lut)
{
    cmsInt32Number n1, i, j;
    cmsFloat32Number Inf[3], Outf[3];

    n1=0;

    for (j=0; j < 65535; j++) {

        cmsInt32Number af[3];

        Inf[0] = Inf[1] = Inf[2] = (cmsFloat32Number) j / 65535.0F;
        cmsPipelineEvalFloat(DbgThread(), Inf, Outf, lut);

        af[0] = (cmsInt32Number) floor(Outf[0]*65535.0 + 0.5);
        af[1] = (cmsInt32Number) floor(Outf[1]*65535.0 + 0.5);
        af[2] = (cmsInt32Number) floor(Outf[2]*65535.0 + 0.5);

        for (i=0; i < 3; i++) {

            if (af[i] != j) {
                n1++;
            }
        }

    }

    return (n1 == 0);
}