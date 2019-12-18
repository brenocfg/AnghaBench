#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_mouse_t ;
struct decoder_owner {int /*<<< orphan*/  mouse_lock; int /*<<< orphan*/  mouse_opaque; int /*<<< orphan*/  (* mouse_event ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MouseEvent( const vlc_mouse_t *newmouse, void *user_data )
{
    decoder_t *dec = user_data;
    struct decoder_owner *owner = dec_get_owner( dec );

    vlc_mutex_lock( &owner->mouse_lock );
    if( owner->mouse_event )
        owner->mouse_event( newmouse, owner->mouse_opaque);
    vlc_mutex_unlock( &owner->mouse_lock );
}