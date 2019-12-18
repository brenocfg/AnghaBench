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
typedef  scalar_t__ cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int cmsInt32Number ;

/* Variables and functions */
 int /*<<< orphan*/  CheckGammaEstimation (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Fail (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * cmsBuildGamma (int /*<<< orphan*/ ,double) ; 
 scalar_t__ cmsEvalToneCurve16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckGammaCreation16(void)
{
    cmsToneCurve* LinGamma = cmsBuildGamma(DbgThread(), 1.0);
    cmsInt32Number i;
    cmsUInt16Number in, out;

    for (i=0; i < 0xffff; i++) {

        in = (cmsUInt16Number) i;
        out = cmsEvalToneCurve16(DbgThread(), LinGamma, in);
        if (in != out) {
            Fail("(lin gamma): Must be %x, But is %x : ", in, out);
            cmsFreeToneCurve(DbgThread(), LinGamma);
            return 0;
        }
    }

    if (!CheckGammaEstimation(LinGamma, 1.0)) return 0;

    cmsFreeToneCurve(DbgThread(), LinGamma);
    return 1;

}