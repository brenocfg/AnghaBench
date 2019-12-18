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
typedef  int uint8_t ;
typedef  size_t uint32_t ;

/* Variables and functions */
 scalar_t__ ID3TAG_IsTag (int const*,int) ; 
 size_t ID3TAG_ReadSize (int const*,int const) ; 
 size_t VLC_FOURCC (int const,int const,int const,int const) ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static size_t ID3TAG_Parse( const uint8_t *p_peek, size_t i_peek,
                            int (*pf_callback)(uint32_t, const uint8_t *, size_t, void *), void *p_priv )
{
    size_t i_total_size = 0;
    uint32_t i_ID3size = 0;
    if( i_peek > 10 && ID3TAG_IsTag( p_peek, false ) )
    {
        const bool b_syncsafe = p_peek[5] & 0x80;
        i_ID3size = ID3TAG_ReadSize( &p_peek[6], true );
        if( i_ID3size > i_peek - 10 )
            return 0;
        i_total_size = i_ID3size + 10;
        const uint8_t *p_frame = &p_peek[10];
        while( i_ID3size > 10 )
        {
            uint32_t i_tagname = VLC_FOURCC( p_frame[0], p_frame[1], p_frame[2], p_frame[3] );
            uint32_t i_framesize = ID3TAG_ReadSize( &p_frame[4], b_syncsafe ) + 10;
            if( i_framesize > i_ID3size )
                return 0;

            if( i_framesize > 10 &&
                pf_callback( i_tagname, &p_frame[10], i_framesize - 10, p_priv ) != VLC_SUCCESS )
                break;

            p_frame += i_framesize;
            i_ID3size -= i_framesize;
        }
    }

    /* Count footer if any */
    if( i_total_size && i_peek - i_total_size >= 10 &&
        ID3TAG_IsTag( &p_peek[i_total_size], true ) )
    {
        i_total_size += 10;
    }

    return i_total_size;
}