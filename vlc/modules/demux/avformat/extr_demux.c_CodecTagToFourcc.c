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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_bswap32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vlc_fourcc_t CodecTagToFourcc( uint32_t codec_tag )
{
    // convert from little-endian avcodec codec_tag to VLC native-endian fourcc
#ifdef WORDS_BIGENDIAN
    return vlc_bswap32(codec_tag);
#else
    return codec_tag;
#endif
}