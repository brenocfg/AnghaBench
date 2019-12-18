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
typedef  int UINT8 ;
typedef  int UINT32 ;

/* Variables and functions */
 int* crc32_tab ; 

__attribute__((used)) static inline UINT32 crc32_add_char(UINT32 crc, UINT8 c) {
        return crc32_tab[(crc ^ c) & 0xff] ^ (crc >> 8);
}