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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  LZSS ;

/* Variables and functions */
 scalar_t__ lzss_mask (int /*<<< orphan*/ *) ; 
 int lzss_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int64_t lzss_next_window_edge_after_position(LZSS *self, int64_t pos) { return (pos + lzss_size(self)) & ~(int64_t)lzss_mask(self); }