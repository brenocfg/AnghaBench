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
struct TYPE_4__ {int rc; float coeff; float rate; int output_dejitter; int abort; int /*<<< orphan*/  coeff_avg; int /*<<< orphan*/  input_dejitter; void* pause_date; void* last; void* wait_sync_ref; int /*<<< orphan*/  wait_sync_ref_priority; void* first_pcr; scalar_t__ delay; void* offset; int /*<<< orphan*/ * master; int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_clock_main_t ;

/* Variables and functions */
 int AOUT_MAX_PTS_ADVANCE ; 
 int /*<<< orphan*/  AvgInit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DEFAULT_PTS_DELAY ; 
 int /*<<< orphan*/  UINT_MAX ; 
 void* VLC_TICK_INVALID ; 
 void* clock_point_Create (void*,void*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

vlc_clock_main_t *vlc_clock_main_New(void)
{
    vlc_clock_main_t *main_clock = malloc(sizeof(vlc_clock_main_t));

    if (main_clock == NULL)
        return NULL;

    vlc_mutex_init(&main_clock->lock);
    vlc_cond_init(&main_clock->cond);
    main_clock->master = NULL;
    main_clock->rc = 1;

    main_clock->coeff = 1.0f;
    main_clock->rate = 1.0f;
    main_clock->offset = VLC_TICK_INVALID;
    main_clock->delay = 0;

    main_clock->first_pcr =
        clock_point_Create(VLC_TICK_INVALID, VLC_TICK_INVALID);
    main_clock->wait_sync_ref_priority = UINT_MAX;
    main_clock->wait_sync_ref = main_clock->last =
        clock_point_Create(VLC_TICK_INVALID, VLC_TICK_INVALID);

    main_clock->pause_date = VLC_TICK_INVALID;
    main_clock->input_dejitter = DEFAULT_PTS_DELAY;
    main_clock->output_dejitter = AOUT_MAX_PTS_ADVANCE * 2;
    main_clock->abort = false;

    AvgInit(&main_clock->coeff_avg, 10);

    return main_clock;
}