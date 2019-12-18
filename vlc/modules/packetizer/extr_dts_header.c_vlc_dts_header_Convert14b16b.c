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
typedef  int ssize_t ;
typedef  enum vlc_dts_syncword_e { ____Placeholder_vlc_dts_syncword_e } vlc_dts_syncword_e ;

/* Variables and functions */
 int Buf14To16 (void*,void const*,size_t,int,int) ; 
 int DTS_SYNC_CORE_14BITS_BE ; 
 int DTS_SYNC_CORE_14BITS_LE ; 
 int DTS_SYNC_NONE ; 
 size_t VLC_DTS_HEADER_SIZE ; 
 int dts_header_getSyncword (void const*) ; 

ssize_t vlc_dts_header_Convert14b16b( void *p_dst, size_t i_dst,
                                      const void *p_src, size_t i_src,
                                      bool b_out_le )
{
    size_t i_size = i_src * 14 / 16;
    if( i_src <= VLC_DTS_HEADER_SIZE || i_size > i_dst )
        return -1;

    enum vlc_dts_syncword_e syncword = dts_header_getSyncword( p_src );
    if( syncword == DTS_SYNC_NONE )
        return -1;

    if( syncword != DTS_SYNC_CORE_14BITS_BE
     && syncword != DTS_SYNC_CORE_14BITS_LE )
        return -1;

    int i_ret = Buf14To16( p_dst, p_src, i_src,
                           syncword == DTS_SYNC_CORE_14BITS_LE, b_out_le );
    return i_ret;
}