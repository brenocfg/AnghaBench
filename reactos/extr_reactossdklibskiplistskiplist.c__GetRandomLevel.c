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
typedef  unsigned long ULONGLONG ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  BitScanForward (int*,int) ; 
 int SKIPLIST_LEVELS ; 

__attribute__((used)) static __inline CHAR
_GetRandomLevel()
{
    // Using a simple fixed seed and the Park-Miller Lehmer Minimal Standard Random Number Generator gives an acceptable distribution for our "random" levels.
    static DWORD dwRandom = 1;

    DWORD dwLevel = 0;
    DWORD dwShifted;

    // Generate 31 uniformly distributed pseudo-random bits using the Park-Miller Lehmer Minimal Standard Random Number Generator.
    dwRandom = (DWORD)(((ULONGLONG)dwRandom * 48271UL) % 2147483647UL);

    // Shift out (31 - SKIPLIST_LEVELS) bits to the right to have no more than SKIPLIST_LEVELS bits set.
    dwShifted = dwRandom >> (31 - SKIPLIST_LEVELS);

    // BitScanForward doesn't operate on a zero input value.
    if (dwShifted)
    {
        // BitScanForward sets dwLevel to the zero-based position of the first set bit (from LSB to MSB).
        // This makes dwLevel a geometrically distributed value between 0 and SKIPLIST_LEVELS - 1 for p = 0.5.
        BitScanForward(&dwLevel, dwShifted);
    }

    // dwLevel can't have a value higher than 30 this way, so a CHAR is more than enough.
    return (CHAR)dwLevel;
}