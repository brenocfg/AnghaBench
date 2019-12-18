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
 unsigned long lpCurrentEncodedSize (unsigned char*) ; 
 scalar_t__ lpEncodeBacklen (int /*<<< orphan*/ *,unsigned long) ; 

unsigned char *lpSkip(unsigned char *p) {
    unsigned long entrylen = lpCurrentEncodedSize(p);
    entrylen += lpEncodeBacklen(NULL,entrylen);
    p += entrylen;
    return p;
}