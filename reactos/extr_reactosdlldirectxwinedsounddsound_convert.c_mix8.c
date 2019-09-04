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
typedef  int /*<<< orphan*/  INT ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,char*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void mix8(signed char *src, INT *dst, unsigned len)
{
    TRACE("%p - %p %d\n", src, dst, len);
    while (len--)
        /* 8-bit WAV is unsigned, it's here converted to signed, normalize function will convert it back again */
        *(dst++) += (signed char)((BYTE)*(src++) - (BYTE)0x80);
}