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

/* Variables and functions */
 int /*<<< orphan*/  CheckOneLab (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ MaxDE ; 

__attribute__((used)) static
cmsInt32Number CheckSeveralLab(cmsHTRANSFORM xform)
{
    cmsInt32Number L, a, b;

    MaxDE = 0;
    for (L=0; L < 65536; L += 1311) {

        for (a = 0; a < 65536; a += 1232) {

            for (b = 0; b < 65536; b += 1111) {

                if (!CheckOneLab(xform, (L * 100.0) / 65535.0,
                                        (a  / 257.0) - 128, (b / 257.0) - 128))
                    return 0;
            }

        }

    }
    return 1;
}