#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * p_description; int /*<<< orphan*/  fmt_out; } ;
struct decoder_owner {int /*<<< orphan*/  b_fmt_description; int /*<<< orphan*/ * p_description; int /*<<< orphan*/  fmt; int /*<<< orphan*/  lock; TYPE_1__ dec; } ;
typedef  TYPE_1__ decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memory_order_release ; 
 int /*<<< orphan*/  vlc_meta_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DecoderUpdateFormatLocked( struct decoder_owner *p_owner )
{
    decoder_t *p_dec = &p_owner->dec;

    vlc_mutex_assert( &p_owner->lock );

    es_format_Clean( &p_owner->fmt );
    es_format_Copy( &p_owner->fmt, &p_dec->fmt_out );

    /* Move p_description */
    if( p_dec->p_description != NULL )
    {
        if( p_owner->p_description != NULL )
            vlc_meta_Delete( p_owner->p_description );
        p_owner->p_description = p_dec->p_description;
        p_dec->p_description = NULL;
    }

    atomic_store_explicit( &p_owner->b_fmt_description, true,
                           memory_order_release );
}