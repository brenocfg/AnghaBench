#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* i_frame_size; void* i_substream_header_size; int /*<<< orphan*/  syncword; } ;
typedef  TYPE_1__ vlc_dts_header_t ;
typedef  scalar_t__ uint8_t ;
typedef  void* uint32_t ;
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTS_SYNC_SUBSTREAM ; 
 int /*<<< orphan*/  VLC_DTS_HEADER_SIZE ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  bs_init (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bs_read1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dts_header_ParseSubstream( vlc_dts_header_t *p_header,
                                      const void *p_buffer )
{
    bs_t s;
    bs_init( &s, p_buffer, VLC_DTS_HEADER_SIZE );
    bs_skip( &s, 32 /*SYNCEXTSSH*/ + 8 /*UserDefinedBits*/ + 2 /*nExtSSIndex*/ );
    uint8_t bHeaderSizeType = bs_read1( &s );
    uint32_t nuBits4ExSSFsize;
    uint16_t nuExtSSHeaderSize;
    if( bHeaderSizeType == 0 )
    {
        nuExtSSHeaderSize = bs_read( &s, 8 /*nuBits4Header*/ );
        nuBits4ExSSFsize = bs_read( &s, 16 );
    }
    else
    {
        nuExtSSHeaderSize = bs_read( &s, 12 /*nuBits4Header*/ );
        nuBits4ExSSFsize = bs_read( &s, 20 );
    }
    memset( p_header, 0, sizeof(*p_header) );
    p_header->syncword = DTS_SYNC_SUBSTREAM;
    p_header->i_substream_header_size = nuExtSSHeaderSize + 1;
    p_header->i_frame_size = nuBits4ExSSFsize + 1;
    return VLC_SUCCESS;
}