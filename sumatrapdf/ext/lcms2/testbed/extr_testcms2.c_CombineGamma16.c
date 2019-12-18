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
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int cmsInt32Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  _cmsQuantizeVal (int,int) ; 
 int /*<<< orphan*/ * cmsBuildTabulatedToneCurve16 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsEvalToneCurve16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsToneCurve* CombineGamma16(cmsToneCurve* g1, cmsToneCurve* g2)
{
    cmsUInt16Number Tab[256];

    cmsInt32Number i;

    for (i=0; i < 256; i++) {

        cmsUInt16Number wValIn;

        wValIn = _cmsQuantizeVal(i, 256);
        Tab[i] = cmsEvalToneCurve16(DbgThread(), g2, cmsEvalToneCurve16(DbgThread(), g1, wValIn));
    }

    return  cmsBuildTabulatedToneCurve16(DbgThread(), 256, Tab);
}