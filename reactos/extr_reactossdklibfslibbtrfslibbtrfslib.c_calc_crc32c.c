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
typedef  size_t ULONG ;
typedef  int UINT8 ;
typedef  int UINT32 ;

/* Variables and functions */
 int* crctable ; 

__attribute__((used)) static UINT32 calc_crc32c(UINT32 seed, UINT8* msg, ULONG msglen) {
    UINT32 rem;
    ULONG i;

    rem = seed;

    for (i = 0; i < msglen; i++) {
        rem = crctable[(rem ^ msg[i]) & 0xff] ^ (rem >> 8);
    }

    return rem;
}