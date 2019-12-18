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
typedef  scalar_t__ uint_fast64_t ;

/* Variables and functions */
 void* CTX ; 
 scalar_t__ PING_VALUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pings ; 

__attribute__((used)) static int vlc_h2_ping(void *ctx, uint_fast64_t opaque)
{
    assert(ctx == CTX);
    assert(opaque == PING_VALUE);
    pings++;
    return 0;
}