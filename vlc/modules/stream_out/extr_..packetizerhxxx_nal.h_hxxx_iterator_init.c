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
typedef  int uint8_t ;
struct TYPE_3__ {int const* p_head; int const* p_tail; int i_nal_length_size; } ;
typedef  TYPE_1__ hxxx_iterator_ctx_t ;

/* Variables and functions */
 int vlc_popcount (int) ; 

__attribute__((used)) static inline void hxxx_iterator_init( hxxx_iterator_ctx_t *p_ctx, const uint8_t *p_data, size_t i_data,
                                       uint8_t i_nal_length_size )
{
    p_ctx->p_head = p_data;
    p_ctx->p_tail = p_data + i_data;
    if( vlc_popcount(i_nal_length_size) == 1 && i_nal_length_size <= 4 )
        p_ctx->i_nal_length_size = i_nal_length_size;
    else
        p_ctx->i_nal_length_size = 0;
}