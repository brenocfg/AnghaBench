#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fraction; } ;
struct TYPE_9__ {int stereo; int single; int jsbound; scalar_t__ mode; int mode_ext; scalar_t__ (* synth_stereo ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ;scalar_t__ (* synth_mono ) (int /*<<< orphan*/ ,TYPE_2__*) ;TYPE_1__ layer1; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
 scalar_t__ I_step_one (unsigned int*,unsigned int**,TYPE_2__*) ; 
 int /*<<< orphan*/  I_step_two (int /*<<< orphan*/ *,unsigned int*,unsigned int**,TYPE_2__*) ; 
 scalar_t__ MPG_MD_JOINT_STEREO ; 
 scalar_t__ NOQUIET ; 
 int SBLIMIT ; 
 int SCALE_BLOCK ; 
 int SINGLE_LEFT ; 
 int SINGLE_MIX ; 
 int SINGLE_STEREO ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * fraction ; 
 int /*<<< orphan*/ * real (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

int do_layer1(mpg123_handle *fr)
{
	int clip=0;
	int i,stereo = fr->stereo;
	unsigned int balloc[2*SBLIMIT];
	unsigned int scale_index[2][SBLIMIT];
	real (*fraction)[SBLIMIT] = fr->layer1.fraction; /* fraction[2][SBLIMIT] */
	int single = fr->single;

	fr->jsbound = (fr->mode == MPG_MD_JOINT_STEREO) ? (fr->mode_ext<<2)+4 : 32;

	if(stereo == 1 || single == SINGLE_MIX) /* I don't see mixing handled here */
	single = SINGLE_LEFT;

	if(I_step_one(balloc,scale_index,fr))
	{
		if(NOQUIET) error("Aborting layer I decoding after step one.\n");
		return clip;
	}

	for(i=0;i<SCALE_BLOCK;i++)
	{
		I_step_two(fraction,balloc,scale_index,fr);

		if(single != SINGLE_STEREO)
		clip += (fr->synth_mono)(fraction[single], fr);
		else
		clip += (fr->synth_stereo)(fraction[0], fraction[1], fr);
	}

	return clip;
}