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
struct TYPE_3__ {int type; int /*<<< orphan*/  direction; int /*<<< orphan*/  vertical; } ;
typedef  TYPE_1__ fz_transition ;
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
#define  FZ_TRANSITION_BLINDS 130 
#define  FZ_TRANSITION_FADE 129 
#define  FZ_TRANSITION_WIPE 128 
 int blind_horiz (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int blind_vertical (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int fade (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int wipe_lr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int wipe_tb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int fz_generate_transition(fz_context *ctx, fz_pixmap *tpix, fz_pixmap *opix, fz_pixmap *npix, int time, fz_transition *trans)
{
	switch (trans->type)
	{
	default:
	case FZ_TRANSITION_FADE:
		return fade(tpix, opix, npix, time);
	case FZ_TRANSITION_BLINDS:
		if (trans->vertical)
			return blind_vertical(tpix, opix, npix, time);
		else
			return blind_horiz(tpix, opix, npix, time);
	case FZ_TRANSITION_WIPE:
		switch (((trans->direction + 45 + 360) % 360) / 90)
		{
		default:
		case 0: return wipe_lr(tpix, opix, npix, time);
		case 1: return wipe_tb(tpix, npix, opix, 256-time);
		case 2: return wipe_lr(tpix, npix, opix, 256-time);
		case 3: return wipe_tb(tpix, opix, npix, time);
		}
	}
}