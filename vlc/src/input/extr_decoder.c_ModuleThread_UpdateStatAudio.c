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
struct decoder_owner {int /*<<< orphan*/ * p_aout; } ;

/* Variables and functions */
 int /*<<< orphan*/  aout_DecGetResetStats (int /*<<< orphan*/ *,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  decoder_Notify (struct decoder_owner*,int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  on_new_audio_stats ; 

__attribute__((used)) static void ModuleThread_UpdateStatAudio( struct decoder_owner *p_owner,
                                          bool lost )
{
    unsigned played = 0;
    unsigned aout_lost = 0;
    if( p_owner->p_aout != NULL )
    {
        aout_DecGetResetStats( p_owner->p_aout, &aout_lost, &played );
    }
    if (lost) aout_lost++;

    decoder_Notify(p_owner, on_new_audio_stats, 1, aout_lost, played);
}