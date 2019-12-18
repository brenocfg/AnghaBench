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
struct TYPE_4__ {int i_slave; scalar_t__ i_attachment; int /*<<< orphan*/ * p_resource; int /*<<< orphan*/  p_sout; TYPE_2__* p_item; int /*<<< orphan*/ * attachment_demux; int /*<<< orphan*/ * attachment; int /*<<< orphan*/ * stats; scalar_t__ p_es_out_display; scalar_t__ p_es_out; scalar_t__ i_seekpoint_offset; scalar_t__ i_title_offset; int /*<<< orphan*/  master; int /*<<< orphan*/ * slave; } ;
typedef  TYPE_1__ input_thread_private_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  p_stats; } ;
typedef  TYPE_2__ input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  END_S ; 
 int /*<<< orphan*/  ES_OUT_MODE_END ; 
 int /*<<< orphan*/  ES_OUT_MODE_NONE ; 
 int /*<<< orphan*/  InputSourceDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_CLEAN (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  es_out_Delete (scalar_t__) ; 
 int /*<<< orphan*/  es_out_SetMode (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_ChangeState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_resource_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_resource_RequestSout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_resource_SetInput (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_stats_Compute (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_input_attachment_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void End( input_thread_t * p_input )
{
    input_thread_private_t *priv = input_priv(p_input);

    /* We are at the end */
    input_ChangeState( p_input, END_S, VLC_TICK_INVALID );

    /* Stop es out activity */
    es_out_SetMode( priv->p_es_out, ES_OUT_MODE_NONE );

    /* Delete slave */
    for( int i = 0; i < priv->i_slave; i++ )
        InputSourceDestroy( priv->slave[i] );
    free( priv->slave );

    /* Clean up master */
    InputSourceDestroy( priv->master );
    priv->i_title_offset = 0;
    priv->i_seekpoint_offset = 0;

    /* Unload all modules */
    if( priv->p_es_out )
        es_out_Delete( priv->p_es_out );
    es_out_SetMode( priv->p_es_out_display, ES_OUT_MODE_END );

    if( priv->stats != NULL )
    {
        input_item_t *item = priv->p_item;
        /* make sure we are up to date */
        vlc_mutex_lock( &item->lock );
        input_stats_Compute( priv->stats, item->p_stats );
        vlc_mutex_unlock( &item->lock );
    }

    vlc_mutex_lock( &priv->p_item->lock );
    if( priv->i_attachment > 0 )
    {
        for( int i = 0; i < priv->i_attachment; i++ )
            vlc_input_attachment_Delete( priv->attachment[i] );
        TAB_CLEAN( priv->i_attachment, priv->attachment );
        free( priv->attachment_demux);
        priv->attachment_demux = NULL;
    }

    vlc_mutex_unlock( &input_priv(p_input)->p_item->lock );

    /* */
    input_resource_RequestSout( input_priv(p_input)->p_resource,
                                 input_priv(p_input)->p_sout, NULL );
    input_resource_SetInput( input_priv(p_input)->p_resource, NULL );
    if( input_priv(p_input)->p_resource )
    {
        input_resource_Release( input_priv(p_input)->p_resource );
        input_priv(p_input)->p_resource = NULL;
    }
}