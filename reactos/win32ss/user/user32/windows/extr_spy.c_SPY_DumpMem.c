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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const,...) ; 

__attribute__((used)) static void SPY_DumpMem (LPCSTR header, const UINT *q, INT len)
{
    int i;

    for(i=0; i<len-12; i+=16) {
        TRACE("%s [%04x] %08x %08x %08x %08x\n",
              header, i, *q, *(q+1), *(q+2), *(q+3));
        q += 4;
    }
    switch ((len - i + 3) & (~3)) {
    case 16:
        TRACE("%s [%04x] %08x %08x %08x %08x\n",
              header, i, *q, *(q+1), *(q+2), *(q+3));
        break;
    case 12:
        TRACE("%s [%04x] %08x %08x %08x\n",
              header, i, *q, *(q+1), *(q+2));
        break;
    case 8:
        TRACE("%s [%04x] %08x %08x\n",
              header, i, *q, *(q+1));
        break;
    case 4:
        TRACE("%s [%04x] %08x\n",
              header, i, *q);
        break;
    default:
        break;
    }
}