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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int FindJpegMarker (int*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static bool IsJfif(stream_t *s)
{
    const uint8_t *header;
    int size = vlc_stream_Peek(s, &header, 256);
    int position = 0;

    if (FindJpegMarker(&position, header, size) != 0xd8)
        return false;
    if (FindJpegMarker(&position, header, size) != 0xe0)
        return false;
    position += 2;  /* Skip size */
    if (position + 5 > size)
        return false;
    if (memcmp(&header[position], "JFIF\0", 5))
        return false;
    return true;
}