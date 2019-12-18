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
typedef  scalar_t__ uint_fast32_t ;
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

struct vlc_h2_frame *
vlc_h2_frame_headers(uint_fast32_t id, uint_fast32_t mtu, bool eos,
                     unsigned count, const char *const tab[][2])
{
    (void) id; (void) mtu; (void) count, (void) tab;
    assert(!eos);
    return NULL;
}