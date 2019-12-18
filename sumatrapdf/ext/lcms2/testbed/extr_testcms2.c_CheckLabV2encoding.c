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
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsCIELab ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsFloat2LabEncodedV2 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsLabEncoded2FloatV2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static
cmsInt32Number CheckLabV2encoding(void)
{
    cmsInt32Number n2, i, j;
    cmsUInt16Number Inw[3], aw[3];
    cmsCIELab Lab;

    n2=0;

    for (j=0; j < 65535; j++) {

        Inw[0] = Inw[1] = Inw[2] = (cmsUInt16Number) j;

        cmsLabEncoded2FloatV2(DbgThread(), &Lab, Inw);
        cmsFloat2LabEncodedV2(DbgThread(), aw, &Lab);

        for (i=0; i < 3; i++) {

        if (aw[i] != j) {
            n2++;
        }
        }

    }

    return (n2 == 0);
}