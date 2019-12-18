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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 void* CTX ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void vlc_h2_window_status(void *ctx, uint32_t *rcwd)
{
    assert(ctx == CTX);
    *rcwd = (1u << 31) - 1;
}