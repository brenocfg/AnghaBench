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
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_4__ {TYPE_2__* master; } ;
typedef  TYPE_1__ input_thread_private_t ;
struct TYPE_5__ {scalar_t__ i_title; int b_title_demux; int /*<<< orphan*/  title; int /*<<< orphan*/  i_seekpoint_offset; int /*<<< orphan*/  i_title_offset; int /*<<< orphan*/  p_demux; } ;
typedef  TYPE_2__ input_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUX_GET_TITLE_INFO ; 
 int /*<<< orphan*/  InitTitle (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TAB_INIT (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ demux_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* input_priv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void UpdateTitleListfromDemux( input_thread_t *p_input )
{
    input_thread_private_t *priv = input_priv(p_input);
    input_source_t *in = priv->master;

    /* Delete the preexisting titles */
    bool had_titles = in->i_title > 0;

    /* Get the new title list */
    if( demux_Control( in->p_demux, DEMUX_GET_TITLE_INFO,
                       &in->title, &in->i_title,
                       &in->i_title_offset, &in->i_seekpoint_offset ) )
        TAB_INIT( in->i_title, in->title );
    else
        in->b_title_demux = true;

    InitTitle( p_input, had_titles );
}