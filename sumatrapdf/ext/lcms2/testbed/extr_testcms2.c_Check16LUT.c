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
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int cmsInt32Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsPipelineEval16 (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number Check16LUT(cmsPipeline* lut)
{
    cmsInt32Number n2, i, j;
    cmsUInt16Number Inw[3], Outw[3];

    n2=0;

    for (j=0; j < 65535; j++) {

        cmsInt32Number aw[3];

        Inw[0] = Inw[1] = Inw[2] = (cmsUInt16Number) j;
        cmsPipelineEval16(DbgThread(), Inw, Outw, lut);
        aw[0] = Outw[0];
        aw[1] = Outw[1];
        aw[2] = Outw[2];

        for (i=0; i < 3; i++) {

        if (aw[i] != j) {
            n2++;
        }
        }

    }

    return (n2 == 0);
}