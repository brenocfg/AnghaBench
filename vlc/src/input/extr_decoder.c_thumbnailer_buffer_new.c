#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct decoder_owner {int /*<<< orphan*/  lock; int /*<<< orphan*/  b_first; } ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_5__ {int /*<<< orphan*/  video; } ;
struct TYPE_6__ {TYPE_1__ fmt_out; } ;
typedef  TYPE_2__ decoder_t ;

/* Variables and functions */
 struct decoder_owner* dec_get_owner (TYPE_2__*) ; 
 int /*<<< orphan*/ * picture_NewFromFormat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_t *thumbnailer_buffer_new( decoder_t *p_dec )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );
    /* Avoid decoding more than one frame when a thumbnail was
     * already generated */
    vlc_mutex_lock( &p_owner->lock );
    if( !p_owner->b_first )
    {
        vlc_mutex_unlock( &p_owner->lock );
        return NULL;
    }
    vlc_mutex_unlock( &p_owner->lock );
    return picture_NewFromFormat( &p_dec->fmt_out.video );
}