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
typedef  int /*<<< orphan*/  fz_context ;
typedef  int fz_bidi_level ;
typedef  scalar_t__ fz_bidi_chartype ;
typedef  int fz_bidi_action ;

/* Variables and functions */
 scalar_t__ BDI_BN ; 
 int IX ; 
 scalar_t__ XX ; 
 int** action_weak ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ embedding_direction (int) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,size_t,scalar_t__) ; 
 scalar_t__ get_deferred_type (int) ; 
 scalar_t__ get_resolved_type (int) ; 
 scalar_t__ odd (int) ; 
 int /*<<< orphan*/  set_deferred_run (scalar_t__*,size_t,size_t,scalar_t__) ; 
 int** state_weak ; 
 int xl ; 
 int xr ; 

void fz_bidi_resolve_weak(fz_context *ctx, fz_bidi_level baselevel, fz_bidi_chartype *pcls, fz_bidi_level *plevel, size_t cch)
{
	int state = odd(baselevel) ? xr : xl;
	fz_bidi_chartype cls;
	size_t ich;
	fz_bidi_action action;
	fz_bidi_chartype cls_run;
	fz_bidi_chartype cls_new;

	fz_bidi_level level = baselevel;

	size_t cch_run = 0;

	for (ich = 0; ich < cch; ich++)
	{
		if (pcls[ich] > BDI_BN) {
			fz_warn(ctx, "error: pcls[%zu] > BN (%d)\n", ich, pcls[ich]);
		}

		// ignore boundary neutrals
		if (pcls[ich] == BDI_BN)
		{
			// must flatten levels unless at a level change;
			plevel[ich] = level;

			// lookahead for level changes
			if (ich + 1 == cch && level != baselevel)
			{
				// have to fixup last BN before end of the loop, since
				// its fix-upped value will be needed below the assert
				pcls[ich] = embedding_direction(level);
			}
			else if (ich + 1 < cch && level != plevel[ich+1] && pcls[ich+1] != BDI_BN)
			{
				// fixup LAST BN in front / after a level run to make
				// it act like the SOR/EOR in rule X10
				int newlevel = plevel[ich+1];
				if (level > newlevel) {
					newlevel = level;
				}
				plevel[ich] = newlevel;

				// must match assigned level
				pcls[ich] = embedding_direction(newlevel);
				level = plevel[ich+1];
			}
			else
			{
				// don't interrupt runs
				if (cch_run)
				{
					cch_run++;
				}
				continue;
			}
		}

		assert(pcls[ich] <= BDI_BN);
		cls = pcls[ich];

		action = action_weak[state][cls];

		// resolve the directionality for deferred runs
		cls_run = get_deferred_type(action);
		if (cls_run != XX)
		{
			set_deferred_run(pcls, cch_run, ich, cls_run);
			cch_run = 0;
		}

		// resolve the directionality class at the current location
		cls_new = get_resolved_type(action);
		if (cls_new != XX)
			pcls[ich] = cls_new;

		// increment a deferred run
		if (IX & action)
			cch_run++;

		state = state_weak[state][cls];
	}

	// resolve any deferred runs
	// use the direction of the current level to emulate PDF
	cls = embedding_direction(level);

	// resolve the directionality for deferred runs
	cls_run = get_deferred_type(action_weak[state][cls]);
	if (cls_run != XX)
		set_deferred_run(pcls, cch_run, ich, cls_run);
}