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
struct TYPE_4__ {int /*<<< orphan*/  position; } ;
typedef  TYPE_1__ LZSS ;

/* Variables and functions */
 int lzss_offset_for_position (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int lzss_current_window_offset(LZSS *self) { return lzss_offset_for_position(self, self->position); }