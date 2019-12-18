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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int /*<<< orphan*/ * window; } ;
typedef  TYPE_1__ LZSS ;

/* Variables and functions */
 int lzss_offset_for_position (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int lzss_size (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void lzss_copy_bytes_from_window(LZSS *self, uint8_t *buffer, int64_t startpos, int length) {
    int windowoffs = lzss_offset_for_position(self, startpos);
    int firstpart = lzss_size(self) - windowoffs;
    if (length <= firstpart) {
        /* Request fits inside window */
        memcpy(buffer, &self->window[windowoffs], length);
    }
    else {
        /* Request wraps around window */
        memcpy(buffer, &self->window[windowoffs], firstpart);
        memcpy(buffer + firstpart, &self->window[0], length - firstpart);
    }
}