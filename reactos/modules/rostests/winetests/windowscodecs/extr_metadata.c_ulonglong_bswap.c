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
typedef  int ULONGLONG ;
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */
 int ulong_bswap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ULONGLONG ulonglong_bswap(ULONGLONG ll)
{
    return ((ULONGLONG)ulong_bswap((ULONG)ll) << 32) | ulong_bswap((ULONG)(ll >> 32));
}