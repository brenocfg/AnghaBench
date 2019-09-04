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
 int /*<<< orphan*/  C816 (unsigned char const) ; 
 int /*<<< orphan*/  W16 (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cvtMS816C(const DWORD srcRate, const unsigned char *src, DWORD *nsrc,
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

            W16(dst, C816(src[0])); dst += 2;
            W16(dst, C816(src[0])); dst += 2;
        }
        src += 1;
    }
}