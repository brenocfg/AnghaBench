#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int /*<<< orphan*/  fmt; } ;
struct heif_private_t {int /*<<< orphan*/  p_title; TYPE_1__ current; scalar_t__ id; int /*<<< orphan*/  p_root; } ;
struct TYPE_4__ {int /*<<< orphan*/  out; scalar_t__ p_sys; } ;
typedef  TYPE_2__ demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BoxFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (struct heif_private_t*) ; 
 int /*<<< orphan*/  vlc_input_title_Delete (int /*<<< orphan*/ ) ; 

void CloseHEIF ( vlc_object_t * p_this )
{
    demux_t *p_demux = (demux_t *)p_this;
    struct heif_private_t *p_sys = (void *) p_demux->p_sys;
    MP4_BoxFree( p_sys->p_root );
    if( p_sys->id )
        es_out_Del( p_demux->out, p_sys->id );
    es_format_Clean( &p_sys->current.fmt );
    vlc_input_title_Delete( p_sys->p_title );
    free( p_sys );
}