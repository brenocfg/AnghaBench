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
typedef  int DWORD ;

/* Variables and functions */

__attribute__((used)) static void cvtMS88C(const DWORD srcRate, const unsigned char *src, DWORD *nsrc,
                     const DWORD dstRate, unsigned char *dst, DWORD *ndst)
{
    DWORD error = srcRate / 2;
    DWORD maxSrc = *nsrc, maxDst = *ndst;
    *ndst = 0;
    for (*nsrc = 0; *nsrc < maxSrc; (*nsrc)++) {
        error += dstRate;
        while (error > srcRate) {
            if (*ndst == maxDst)
                return;
            (*ndst)++;
            error -= srcRate;

            *dst++ = src[0];
            *dst++ = src[0];
        }
        src += 1;
    }
}