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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int PREC ; 

__attribute__((used)) static inline const byte *sample_nearest(const byte *s, int w, int h, int str, int n, int u, int v)
{
	if (u < 0) u = 0;
	if (v < 0) v = 0;
	if (u >= (w>>PREC)) u = (w>>PREC) - 1;
	if (v >= (h>>PREC)) v = (h>>PREC) - 1;
	return s + v * str + u * n;
}