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
typedef  enum vlc_dts_syncword_e { ____Placeholder_vlc_dts_syncword_e } vlc_dts_syncword_e ;

/* Variables and functions */
 int DTS_SYNC_CORE_14BITS_BE ; 
 int DTS_SYNC_CORE_14BITS_LE ; 
 int DTS_SYNC_CORE_BE ; 
 int DTS_SYNC_CORE_LE ; 
 int DTS_SYNC_NONE ; 
 int DTS_SYNC_SUBSTREAM ; 
 int DTS_SYNC_SUBSTREAM_LBR ; 
 scalar_t__ memcmp (int const*,char*,int) ; 

__attribute__((used)) static enum vlc_dts_syncword_e dts_header_getSyncword( const uint8_t *p_buf )
{
    if( memcmp( p_buf, "\x7F\xFE\x80\x01", 4 ) == 0 )
        return DTS_SYNC_CORE_BE;
    else
    if( memcmp( p_buf, "\xFE\x7F\x01\x80", 4 ) == 0 )
        return DTS_SYNC_CORE_LE;
    else
    if( memcmp( p_buf, "\x64\x58\x20\x25", 4 ) == 0 )
        return DTS_SYNC_SUBSTREAM;
    else
    if( memcmp( p_buf, "\x1F\xFF\xE8\x00", 4 ) == 0
     && p_buf[4] == 0x07 && (p_buf[5] & 0xf0) == 0xf0 )
        return DTS_SYNC_CORE_14BITS_BE;
    else
    if( memcmp( p_buf, "\xFF\x1F\x00\xE8", 4 ) == 0
     && (p_buf[4] & 0xf0) == 0xf0 && p_buf[5] == 0x07 )
        return DTS_SYNC_CORE_14BITS_LE;
    else
    if( memcmp( p_buf, "\x0A\x80\x19\x21", 4 ) == 0 )
        return DTS_SYNC_SUBSTREAM_LBR;
    else
        return DTS_SYNC_NONE;
}