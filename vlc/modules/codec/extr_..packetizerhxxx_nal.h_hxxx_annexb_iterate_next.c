#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ const* p_head; scalar_t__* p_tail; } ;
typedef  TYPE_1__ hxxx_iterator_ctx_t ;

/* Variables and functions */
 int hxxx_strip_AnnexB_startcode (scalar_t__ const**,size_t*) ; 
 void* startcode_FindAnnexB (scalar_t__ const*,scalar_t__*) ; 

__attribute__((used)) static inline bool hxxx_annexb_iterate_next( hxxx_iterator_ctx_t *p_ctx, const uint8_t **pp_start, size_t *pi_size )
{
    if( !p_ctx->p_head )
        return false;

    p_ctx->p_head = startcode_FindAnnexB( p_ctx->p_head, p_ctx->p_tail );
    if( !p_ctx->p_head )
        return false;

    const uint8_t *p_end = startcode_FindAnnexB( p_ctx->p_head + 3, p_ctx->p_tail );
    if( !p_end )
        p_end = p_ctx->p_tail;

    /* fix 3 to 4 startcode offset and strip any trailing zeros */
    while( p_end > p_ctx->p_head && p_end[-1] == 0 )
        p_end--;

    *pp_start = p_ctx->p_head;
    *pi_size = p_end - p_ctx->p_head;
    p_ctx->p_head = p_end;

    return hxxx_strip_AnnexB_startcode( pp_start, pi_size );
}