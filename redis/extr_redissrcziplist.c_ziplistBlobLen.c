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

/* Variables and functions */
 int /*<<< orphan*/  ZIPLIST_BYTES (unsigned char*) ; 
 size_t intrev32ifbe (int /*<<< orphan*/ ) ; 

size_t ziplistBlobLen(unsigned char *zl) {
    return intrev32ifbe(ZIPLIST_BYTES(zl));
}