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
typedef  int /*<<< orphan*/  PACMDRVSTREAMINSTANCE ;
typedef  scalar_t__* LPDWORD ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ulaw2alaw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cvtXXulawalawK(PACMDRVSTREAMINSTANCE adsi,
                           const unsigned char* src, LPDWORD srcsize,
                           unsigned char* dst, LPDWORD dstsize)
{
    DWORD       len = min(*srcsize, *dstsize);
    DWORD       i;

    *srcsize = len;
    *dstsize = len;

    for (i = 0; i < len; i++)
        *dst++ = ulaw2alaw(*src++);
}