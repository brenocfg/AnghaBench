#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  avi_chunk_t ;
struct TYPE_7__ {int /*<<< orphan*/  p_bih; } ;
struct TYPE_6__ {scalar_t__ i_cat; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_wf; } ;
struct TYPE_8__ {TYPE_3__ vids; TYPE_2__ common; TYPE_1__ auds; } ;
typedef  TYPE_4__ avi_chunk_strf_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int /*<<< orphan*/  FREENULL (int /*<<< orphan*/ ) ; 
 scalar_t__ VIDEO_ES ; 

__attribute__((used)) static void AVI_ChunkFree_strf( avi_chunk_t *p_chk )
{
    avi_chunk_strf_t *p_strf = (avi_chunk_strf_t*)p_chk;
    if( p_strf->common.i_cat == AUDIO_ES )
    {
        FREENULL( p_strf->auds.p_wf );
    }
    else if( p_strf->common.i_cat == VIDEO_ES )
    {
        FREENULL( p_strf->vids.p_bih );
    }
}