#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ncum; int ustart; } ;

/* Variables and functions */
 int UV_NDIVS ; 
 int UV_NVS ; 
 int UV_SQSIZ ; 
 int UV_VSTART ; 
 TYPE_1__* uv_row ; 

__attribute__((used)) static int
uv_decode(float *up, float *vp, int c)	/* decode (u',v') index */
{
	int	upper, lower;
	register int	ui, vi;

	if (c < 0 || c >= UV_NDIVS)
		return (-1);
	lower = 0;				/* binary search */
	upper = UV_NVS;
	while (upper - lower > 1) {
		vi = (lower + upper) >> 1;
		ui = c - uv_row[vi].ncum;
		if (ui > 0)
			lower = vi;
		else if (ui < 0)
			upper = vi;
		else {
			lower = vi;
			break;
		}
	}
	vi = lower;
	ui = c - uv_row[vi].ncum;
	*up = uv_row[vi].ustart + (ui+.5f)*UV_SQSIZ;
	*vp = UV_VSTART + (vi+.5f)*UV_SQSIZ;
	return (0);
}