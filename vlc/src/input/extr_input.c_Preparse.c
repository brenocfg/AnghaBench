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
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_4__ {TYPE_1__* master; int /*<<< orphan*/  p_item; int /*<<< orphan*/  interrupt; int /*<<< orphan*/  input; } ;
typedef  TYPE_2__ input_thread_private_t ;
struct TYPE_3__ {int /*<<< orphan*/  p_demux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUX_IS_PLAYLIST ; 
 int /*<<< orphan*/  End (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MainLoop (int /*<<< orphan*/ *,int) ; 
 scalar_t__ demux_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  input_SendEventDead (int /*<<< orphan*/ *) ; 
 scalar_t__ input_item_ShouldPreparseSubItems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_interrupt_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *Preparse( void *data )
{
    input_thread_private_t *priv = data;
    input_thread_t *p_input = &priv->input;

    vlc_interrupt_set(&priv->interrupt);

    if( !Init( p_input ) )
    {   /* if the demux is a playlist, call Mainloop that will call
         * demux_Demux in order to fetch sub items */
        bool b_is_playlist = false;

        if ( input_item_ShouldPreparseSubItems( priv->p_item )
          && demux_Control( priv->master->p_demux, DEMUX_IS_PLAYLIST,
                            &b_is_playlist ) )
            b_is_playlist = false;
        if( b_is_playlist )
            MainLoop( p_input, false );
        End( p_input );
    }

    input_SendEventDead( p_input );
    return NULL;
}