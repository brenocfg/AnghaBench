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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  position; } ;
typedef  TYPE_1__ LZSS ;

/* Variables and functions */
 int /*<<< orphan*/ * lzss_current_window_pointer (TYPE_1__*) ; 

__attribute__((used)) static inline void lzss_emit_literal(LZSS *self, uint8_t literal) {
    /* self->window[(self->position & self->mask)] = literal; */
    *lzss_current_window_pointer(self) = literal;
    self->position++;
}