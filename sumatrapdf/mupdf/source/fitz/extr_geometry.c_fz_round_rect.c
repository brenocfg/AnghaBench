#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ y1; scalar_t__ x1; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_1__ fz_rect ;
struct TYPE_6__ {void* y1; void* x1; void* y0; void* x0; } ;
typedef  TYPE_2__ fz_irect ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SAFE_INT ; 
 int /*<<< orphan*/  MIN_SAFE_INT ; 
 int ceilf (scalar_t__) ; 
 int floorf (scalar_t__) ; 
 void* fz_clamp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

fz_irect
fz_round_rect(fz_rect r)
{
	fz_irect b;
	int i;

	i = floorf(r.x0 + 0.001f);
	b.x0 = fz_clamp(i, MIN_SAFE_INT, MAX_SAFE_INT);
	i = floorf(r.y0 + 0.001f);
	b.y0 = fz_clamp(i, MIN_SAFE_INT, MAX_SAFE_INT);
	i = ceilf(r.x1 - 0.001f);
	b.x1 = fz_clamp(i, MIN_SAFE_INT, MAX_SAFE_INT);
	i = ceilf(r.y1 - 0.001f);
	b.y1 = fz_clamp(i, MIN_SAFE_INT, MAX_SAFE_INT);

	return b;
}