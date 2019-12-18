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
typedef  int /*<<< orphan*/  vlc_meta_t ;
struct decoder_owner {int /*<<< orphan*/  lock; scalar_t__ p_description; int /*<<< orphan*/  fmt; int /*<<< orphan*/  b_fmt_description; } ;
typedef  int /*<<< orphan*/  es_format_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_exchange_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memory_order_acquire ; 
 int /*<<< orphan*/  vlc_meta_Merge (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * vlc_meta_New () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

bool input_DecoderHasFormatChanged( decoder_t *p_dec, es_format_t *p_fmt, vlc_meta_t **pp_meta )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    if( !atomic_exchange_explicit( &p_owner->b_fmt_description, false,
                                   memory_order_acquire ) )
        return false;

    vlc_mutex_lock( &p_owner->lock );
    if( p_fmt != NULL )
        es_format_Copy( p_fmt, &p_owner->fmt );

    if( pp_meta )
    {
        *pp_meta = NULL;
        if( p_owner->p_description )
        {
            *pp_meta = vlc_meta_New();
            if( *pp_meta )
                vlc_meta_Merge( *pp_meta, p_owner->p_description );
        }
    }
    vlc_mutex_unlock( &p_owner->lock );
    return true;
}