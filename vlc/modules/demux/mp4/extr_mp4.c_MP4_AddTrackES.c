#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ i_cat; } ;
struct TYPE_4__ {scalar_t__ b_forced_spu; TYPE_2__ fmt; } ;
typedef  TYPE_1__ mp4_track_t ;
typedef  int /*<<< orphan*/  es_out_t ;
typedef  int /*<<< orphan*/  es_out_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ES_OUT_SET_ES_DEFAULT ; 
 scalar_t__ SPU_ES ; 
 int /*<<< orphan*/ * es_out_Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static es_out_id_t * MP4_AddTrackES( es_out_t *out, mp4_track_t *p_track )
{
    es_out_id_t *p_es = es_out_Add( out, &p_track->fmt );
    /* Force SPU which isn't selected/defaulted */
    if( p_track->fmt.i_cat == SPU_ES && p_es && p_track->b_forced_spu )
        es_out_Control( out, ES_OUT_SET_ES_DEFAULT, p_es );

    return p_es;
}