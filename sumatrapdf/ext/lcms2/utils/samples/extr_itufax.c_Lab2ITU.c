#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_3__ {int L; int a; int b; } ;
typedef  TYPE_1__* LPcmsCIELab ;

/* Variables and functions */
 scalar_t__ floor (double) ; 

__attribute__((used)) static
void Lab2ITU(LPcmsCIELab Lab, WORD Out[3])
{
	Out[0] = (WORD) floor((double) (Lab -> L / 100.)* 65535. + 0.5);
    Out[1] = (WORD) floor((double) (Lab -> a / 170.)* 65535. + 32768. + 0.5);
    Out[2] = (WORD) floor((double) (Lab -> b / 200.)* 65535. + 24576. + 0.5);
}