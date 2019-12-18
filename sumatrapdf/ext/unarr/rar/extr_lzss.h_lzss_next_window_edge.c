#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  position; } ;
typedef  TYPE_1__ LZSS ;

/* Variables and functions */
 int /*<<< orphan*/  lzss_next_window_edge_after_position (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int64_t lzss_next_window_edge(LZSS *self) { return lzss_next_window_edge_after_position(self, self->position); }