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
typedef  int Rune ;

/* Variables and functions */
 int toupperrune (int) ; 

__attribute__((used)) static int canon(Rune c)
{
	Rune u = toupperrune(c);
	if (c >= 128 && u < 128)
		return c;
	return u;
}