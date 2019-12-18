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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint16_t unaligned_read_le16(const void *_u) {
        const struct __attribute__((__packed__, __may_alias__)) { uint16_t x; } *u = _u;

        return le16toh(u->x);
}