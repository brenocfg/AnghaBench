#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tjtransform ;
struct TYPE_4__ {int w; int h; } ;
typedef  TYPE_1__ tjregion ;

/* Variables and functions */

int dummyDCTFilter(short *coeffs, tjregion arrayRegion, tjregion planeRegion,
	int componentIndex, int transformIndex, tjtransform *transform)
{
	int i;
	for(i=0; i<arrayRegion.w*arrayRegion.h; i++) coeffs[i]=-coeffs[i];
	return 0;
}