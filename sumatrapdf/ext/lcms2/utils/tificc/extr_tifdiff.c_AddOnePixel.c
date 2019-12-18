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
struct TYPE_3__ {double x; double x2; double n; double Peak; double Min; } ;
typedef  TYPE_1__* LPSTAT ;

/* Variables and functions */

__attribute__((used)) static
void AddOnePixel(LPSTAT st, double dE)
{

    st-> x += dE; st ->x2 += (dE * dE); st->n  += 1.0;
    if (dE > st ->Peak) st ->Peak = dE;
    if (dE < st ->Min)  st ->Min= dE;
}