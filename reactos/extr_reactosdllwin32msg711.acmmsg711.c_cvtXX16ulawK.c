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
typedef  int* LPDWORD ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  R16 (unsigned char const*) ; 
 int /*<<< orphan*/  linear2ulaw (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 

__attribute__((used)) static void cvtXX16ulawK(PACMDRVSTREAMINSTANCE adsi,
                         const unsigned char* src, LPDWORD srcsize,
                         unsigned char* dst, LPDWORD dstsize)
{
    DWORD       len = min(*srcsize / 2, *dstsize);
    DWORD       i;

    *srcsize = len * 2;
    *dstsize = len;
    for (i = 0; i < len; i++)
    {
        *dst++ = linear2ulaw(R16(src)); src += 2;
    }
}