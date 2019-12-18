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
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool IsWebP(stream_t *s)
{
    const uint8_t *header;
    if (vlc_stream_Peek(s, &header, 20) < 20) /* WebP header size */
        return false;
    if (memcmp(&header[0], "RIFF", 4))
        return false;
    /* TODO: support other chunk types */
    if (memcmp(&header[8], "WEBPVP8 ", 8))
        return false;
    /* skip headers */
    return vlc_stream_Seek(s, 20) == 0;
}