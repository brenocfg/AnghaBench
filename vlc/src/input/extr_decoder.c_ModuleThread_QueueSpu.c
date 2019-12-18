#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ i_start; scalar_t__ i_stop; } ;
typedef  TYPE_1__ subpicture_t ;
struct decoder_owner {scalar_t__ i_preroll_end; int /*<<< orphan*/  lock; TYPE_1__* p_vout; } ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  ModuleThread_PlaySpu (struct decoder_owner*,TYPE_1__*) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subpicture_Delete (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ModuleThread_QueueSpu( decoder_t *p_dec, subpicture_t *p_spu )
{
    assert( p_spu );
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    /* The vout must be created from a previous decoder_NewSubpicture call. */
    assert( p_owner->p_vout );

    /* Preroll does not work very well with subtitle */
    vlc_mutex_lock( &p_owner->lock );
    if( p_spu->i_start != VLC_TICK_INVALID &&
        p_spu->i_start < p_owner->i_preroll_end &&
        ( p_spu->i_stop == VLC_TICK_INVALID || p_spu->i_stop < p_owner->i_preroll_end ) )
    {
        vlc_mutex_unlock( &p_owner->lock );
        subpicture_Delete( p_spu );
    }
    else
    {
        vlc_mutex_unlock( &p_owner->lock );
        ModuleThread_PlaySpu( p_owner, p_spu );
    }
}