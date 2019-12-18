#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_4__ {int b_no_skip; int current_pts; int i_frame_rate; scalar_t__ i_pic; scalar_t__ i_not_chosen_pic; scalar_t__ i_trashed_pic; scalar_t__ i_backward_period; scalar_t__ i_current_period; int /*<<< orphan*/  backward_pts; scalar_t__ i_dec_nb_ref; scalar_t__ i_trash_nb_ref; scalar_t__ i_nb_ref; int /*<<< orphan*/  pi_meaningful; int /*<<< orphan*/  p_tau; int /*<<< orphan*/  i_eta_b; int /*<<< orphan*/  i_n_b; int /*<<< orphan*/  i_eta_p; int /*<<< orphan*/  i_n_p; scalar_t__ b_quiet; int /*<<< orphan*/ * p_dec; } ;
typedef  TYPE_1__ decoder_synchro_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_NB_B ; 
 int /*<<< orphan*/  DEFAULT_NB_P ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 

decoder_synchro_t * decoder_SynchroInit( decoder_t *p_dec, int i_frame_rate )
{
    decoder_synchro_t * p_synchro = calloc( 1, sizeof(*p_synchro) );
    if( !p_synchro )
        return NULL;

    p_synchro->p_dec = p_dec;
    p_synchro->b_no_skip = !var_InheritBool( p_dec, "skip-frames" );
    p_synchro->b_quiet = var_InheritBool( p_dec, "quiet-synchro" );

    /* We use a fake stream pattern, which is often right. */
    p_synchro->i_n_p = p_synchro->i_eta_p = DEFAULT_NB_P;
    p_synchro->i_n_b = p_synchro->i_eta_b = DEFAULT_NB_B;
    memset( p_synchro->p_tau, 0, 4 * sizeof(vlc_tick_t) );
    memset( p_synchro->pi_meaningful, 0, 4 * sizeof(unsigned int) );
    p_synchro->i_nb_ref = 0;
    p_synchro->i_trash_nb_ref = p_synchro->i_dec_nb_ref = 0;
    p_synchro->current_pts = 1,
    p_synchro->backward_pts = VLC_TICK_INVALID;
    p_synchro->i_current_period = p_synchro->i_backward_period = 0;
    p_synchro->i_trashed_pic = p_synchro->i_not_chosen_pic =
        p_synchro->i_pic = 0;

    p_synchro->i_frame_rate = i_frame_rate;

    return p_synchro;
}