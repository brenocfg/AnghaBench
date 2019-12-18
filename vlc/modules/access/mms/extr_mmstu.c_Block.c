#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_9__ {int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_2__ block_t ;
struct TYPE_10__ {scalar_t__ i_position; scalar_t__ i_header; scalar_t__ i_media_used; size_t i_media; size_t i_packet_length; int /*<<< orphan*/ * p_media; int /*<<< orphan*/ * p_header; scalar_t__ b_eof; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMS_PACKET_MEDIA ; 
 scalar_t__ __MAX (size_t,size_t) ; 
 TYPE_2__* block_Alloc (size_t const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mms_HeaderMediaRead (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *Block( stream_t *p_access, bool *restrict eof )
{
    access_sys_t *p_sys = p_access->p_sys;

    if( p_sys->b_eof )
    {
        *eof = true;
        return NULL;
    }

    if( p_sys->i_position < p_sys->i_header )
    {
        const size_t i_copy = p_sys->i_header - p_sys->i_position;

        block_t *p_block = block_Alloc( i_copy );
        if( !p_block )
            return NULL;

        memcpy( p_block->p_buffer, &p_sys->p_header[p_sys->i_position], i_copy );
        p_sys->i_position += i_copy;
        return p_block;
    }
    else if( p_sys->p_media && p_sys->i_media_used < __MAX( p_sys->i_media, p_sys->i_packet_length ) )
    {
        size_t i_copy = 0;
        size_t i_padding = 0;

        if( p_sys->i_media_used < p_sys->i_media )
            i_copy = p_sys->i_media - p_sys->i_media_used;
        if( __MAX( p_sys->i_media, p_sys->i_media_used ) < p_sys->i_packet_length )
            i_padding = p_sys->i_packet_length - __MAX( p_sys->i_media, p_sys->i_media_used );

        block_t *p_block = block_Alloc( i_copy + i_padding );
        if( !p_block )
            return NULL;

        if( i_copy > 0 )
            memcpy( &p_block->p_buffer[0], &p_sys->p_media[p_sys->i_media_used], i_copy );
        if( i_padding > 0 )
            memset( &p_block->p_buffer[i_copy], 0, i_padding );

        p_sys->i_media_used += i_copy + i_padding;
        p_sys->i_position += i_copy + i_padding;
        return p_block;
    }

    mms_HeaderMediaRead( p_access, MMS_PACKET_MEDIA );
    return NULL;
}