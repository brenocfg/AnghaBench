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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int int32_t ;

/* Variables and functions */
 int vlc_stream_Read (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int32_t ReadVarInt (stream_t *s)
{
    uint32_t val = 0;
    uint8_t byte;

    for (unsigned i = 0; i < 4; i++)
    {
        if (vlc_stream_Read (s, &byte, 1) < 1)
            return -1;

        val = (val << 7) | (byte & 0x7f);
        if ((byte & 0x80) == 0)
            return val;
    }

    return -1;
}