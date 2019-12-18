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
struct TYPE_4__ {int mask; scalar_t__ position; int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ LZSS ;

/* Variables and functions */
 int /*<<< orphan*/  lzss_size (TYPE_1__*) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool lzss_initialize(LZSS *self, int windowsize) {
    self->window = malloc(windowsize);
    if (!self->window)
        return false;

    self->mask = windowsize - 1; /* Assume windows are power-of-two sized! */
    memset(self->window, 0, lzss_size(self));
    self->position = 0;
    return true;
}