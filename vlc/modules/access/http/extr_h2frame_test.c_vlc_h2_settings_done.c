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

/* Variables and functions */
 void* CTX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  settings_acked ; 

__attribute__((used)) static int vlc_h2_settings_done(void *ctx)
{
    assert(ctx == CTX);
    settings_acked++;
    (void) ctx;
    return 0;
}