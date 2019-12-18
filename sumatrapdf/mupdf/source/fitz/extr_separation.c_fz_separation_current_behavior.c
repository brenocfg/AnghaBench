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
typedef  int /*<<< orphan*/  fz_separations ;
typedef  int fz_separation_behavior ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int FZ_SEPARATION_DISABLED ; 
 int FZ_SEPARATION_DISABLED_RENDER ; 
 int fz_separation_current_behavior_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

fz_separation_behavior fz_separation_current_behavior(fz_context *ctx, const fz_separations *sep, int separation)
{
	int beh = fz_separation_current_behavior_internal(ctx, sep, separation);

	if (beh == FZ_SEPARATION_DISABLED_RENDER)
		return FZ_SEPARATION_DISABLED;
	return beh;
}