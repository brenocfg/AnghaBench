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
 int /*<<< orphan*/  M16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R16 (unsigned char const*) ; 
 int /*<<< orphan*/  W16 (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cvtSM1616C(const DWORD srcRate, const unsigned char *src, DWORD *nsrc,
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

            W16(dst, M16(R16(src), R16(src + 2))); dst += 2;
        }
        src += 4;
    }
}