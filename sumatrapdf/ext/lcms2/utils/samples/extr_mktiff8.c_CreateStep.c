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

/* Variables and functions */
 double DecodeAbTIFF (double) ; 
 scalar_t__* calloc (int,int) ; 
 int /*<<< orphan*/ * cmsBuildTabulatedToneCurve16 (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ floor (double) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 

__attribute__((used)) static
cmsToneCurve* CreateStep(void)
{
	cmsToneCurve* Gamma;
	cmsUInt16Number* Table;
	int i;
	double a;

	Table = calloc(4096, sizeof(cmsUInt16Number));
	if (Table == NULL) return NULL;

	for (i=0; i < 4096; i++) {

		a = (double) i * 255. / 4095.;

		a = DecodeAbTIFF(a);

		Table[i] = (cmsUInt16Number) floor(a * 257. + 0.5);
	}

	Gamma = cmsBuildTabulatedToneCurve16(0, 4096, Table);
	free(Table);

	return Gamma;
}