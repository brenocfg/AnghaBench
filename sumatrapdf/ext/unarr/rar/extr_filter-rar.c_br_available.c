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
struct MemBitReader {int available; int /*<<< orphan*/  at_eof; } ;

/* Variables and functions */
 scalar_t__ br_fill (struct MemBitReader*,int) ; 

__attribute__((used)) static inline bool br_available(struct MemBitReader *br, int bits)
{
    return !br->at_eof && (bits <= br->available || br_fill(br, bits));
}