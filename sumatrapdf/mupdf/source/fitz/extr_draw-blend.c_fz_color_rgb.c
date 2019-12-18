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

/* Variables and functions */
 int /*<<< orphan*/  fz_luminosity_rgb (unsigned char*,unsigned char*,unsigned char*,int,int,int,int,int,int) ; 

__attribute__((used)) static void
fz_color_rgb(unsigned char *rr, unsigned char *rg, unsigned char *rb, int br, int bg, int bb, int sr, int sg, int sb)
{
	fz_luminosity_rgb(rr, rg, rb, sr, sg, sb, br, bg, bb);
}