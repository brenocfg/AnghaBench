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
typedef  int /*<<< orphan*/  vlc_meta_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
typedef  int /*<<< orphan*/  input_attachment_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_4__ {int i_attachment; int /*<<< orphan*/  p_es_out; TYPE_1__* p_item; int /*<<< orphan*/ ** attachment_demux; int /*<<< orphan*/ * attachment; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AppendAttachment (int*,int /*<<< orphan*/ **,int /*<<< orphan*/ ***,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEMUX_GET_ATTACHMENTS ; 
 int /*<<< orphan*/  DEMUX_GET_META ; 
 int /*<<< orphan*/  demux_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,...) ; 
 int /*<<< orphan*/  es_out_ControlSetMeta (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* input_priv (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_input_attachment_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_meta_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_meta_New () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void InputUpdateMeta( input_thread_t *p_input, demux_t *p_demux )
{
    vlc_meta_t *p_meta = vlc_meta_New();
    if( unlikely(p_meta == NULL) )
        return;

    demux_Control( p_demux, DEMUX_GET_META, p_meta );

    /* If metadata changed, then the attachments might have changed.
       We need to update them in case they contain album art. */
    input_attachment_t **attachment;
    int i_attachment;

    if( !demux_Control( p_demux, DEMUX_GET_ATTACHMENTS,
                        &attachment, &i_attachment ) )
    {
        vlc_mutex_lock( &input_priv(p_input)->p_item->lock );
        if( input_priv(p_input)->i_attachment > 0 )
        {
            int j = 0;
            for( int i = 0; i < input_priv(p_input)->i_attachment; i++ )
            {
                if( input_priv(p_input)->attachment_demux[i] == p_demux )
                    vlc_input_attachment_Delete( input_priv(p_input)->attachment[i] );
                else
                {
                    input_priv(p_input)->attachment[j] = input_priv(p_input)->attachment[i];
                    input_priv(p_input)->attachment_demux[j] = input_priv(p_input)->attachment_demux[i];
                    j++;
                }
            }
            input_priv(p_input)->i_attachment = j;
        }
        AppendAttachment( &input_priv(p_input)->i_attachment, &input_priv(p_input)->attachment, &input_priv(p_input)->attachment_demux,
                          i_attachment, attachment, p_demux );
        vlc_mutex_unlock( &input_priv(p_input)->p_item->lock );
    }

    es_out_ControlSetMeta( input_priv(p_input)->p_es_out, p_meta );
    vlc_meta_Delete( p_meta );
}