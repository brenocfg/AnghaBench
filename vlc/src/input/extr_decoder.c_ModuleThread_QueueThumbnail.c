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
struct decoder_owner {int b_first; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decoder_Notify (struct decoder_owner*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_thumbnail_ready ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ModuleThread_QueueThumbnail( decoder_t *p_dec, picture_t *p_pic )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );
    bool b_first;

    vlc_mutex_lock( &p_owner->lock );
    b_first = p_owner->b_first;
    p_owner->b_first = false;
    vlc_mutex_unlock( &p_owner->lock );

    if( b_first )
        decoder_Notify(p_owner, on_thumbnail_ready, p_pic);
    picture_Release( p_pic );

}