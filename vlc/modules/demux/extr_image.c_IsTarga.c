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
typedef  int /*<<< orphan*/  stream_t ;
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ GetWLE (int const*) ; 
 int /*<<< orphan*/  STREAM_CAN_SEEK ; 
 scalar_t__ memcmp (int const*,char*,int) ; 
 int stream_Size (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_stream_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ *,int const**,int) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ *,int const) ; 
 int vlc_stream_Tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool IsTarga(stream_t *s)
{
    /* The header is not enough to ensure proper detection, we need
     * to have a look at the footer. But doing so can be slow. So
     * try to avoid it when possible */
    const uint8_t *header;
    if (vlc_stream_Peek(s, &header, 18) < 18)   /* Targa fixed header */
        return false;
    if (header[1] > 1)                      /* Color Map Type */
        return false;
    if ((header[1] != 0 || header[3 + 4] != 0) &&
        header[3 + 4] != 8  &&
        header[3 + 4] != 15 && header[3 + 4] != 16 &&
        header[3 + 4] != 24 && header[3 + 4] != 32)
        return false;
    if ((header[2] > 3 && header[2] < 9) || header[2] > 11) /* Image Type */
        return false;
    if (GetWLE(&header[8 + 4]) <= 0 ||      /* Width */
        GetWLE(&header[8 + 6]) <= 0)        /* Height */
        return false;
    if (header[8 + 8] != 8  &&
        header[8 + 8] != 15 && header[8 + 8] != 16 &&
        header[8 + 8] != 24 && header[8 + 8] != 32)
        return false;
    if (header[8 + 9] & 0xc0)               /* Reserved bits */
        return false;

    const int64_t size = stream_Size(s);
    if (size <= 18 + 26)
        return false;
    bool can_seek;
    if (vlc_stream_Control(s, STREAM_CAN_SEEK, &can_seek) || !can_seek)
        return false;

    const int64_t position = vlc_stream_Tell(s);
    if (vlc_stream_Seek(s, size - 26))
        return false;

    const uint8_t *footer;
    if (vlc_stream_Peek(s, &footer, 26) < 26
     || memcmp(&footer[8], "TRUEVISION-XFILE.\x00", 18))
        return false;

    return vlc_stream_Seek(s, position) == 0;
}