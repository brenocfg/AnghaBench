#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int position; int /*<<< orphan*/ * window; } ;
typedef  TYPE_1__ LZSS ;

/* Variables and functions */
 int lzss_current_window_offset (TYPE_1__*) ; 
 int lzss_mask (TYPE_1__*) ; 

__attribute__((used)) static inline void lzss_emit_match(LZSS *self, int offset, int length) {
    int windowoffs = lzss_current_window_offset(self);
    int i;
    for (i = 0; i < length; i++) {
        self->window[(windowoffs + i) & lzss_mask(self)] = self->window[(windowoffs + i - offset) & lzss_mask(self)];
    }
    self->position += length;
}