#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_3__ {int /*<<< orphan*/  max_bits; } ;
typedef  TYPE_1__ HUF_dtable ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_read_bits (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static inline void HUF_init_state(const HUF_dtable *const dtable,
                                  u16 *const state, const u8 *const src,
                                  i64 *const offset) {
    // Read in a full `dtable->max_bits` bits to initialize the state
    const u8 bits = dtable->max_bits;
    *state = STREAM_read_bits(src, bits, offset);
}