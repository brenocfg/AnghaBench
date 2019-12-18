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
struct ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  test_end_prestop_buffering (struct ctx*) ; 
 int /*<<< orphan*/  test_end_prestop_capabilities (struct ctx*) ; 
 int /*<<< orphan*/  test_end_prestop_length (struct ctx*) ; 
 int /*<<< orphan*/  test_end_prestop_rate (struct ctx*) ; 

__attribute__((used)) static void
test_prestop(struct ctx *ctx)
{
    test_end_prestop_rate(ctx);
    test_end_prestop_length(ctx);
    test_end_prestop_capabilities(ctx);
    test_end_prestop_buffering(ctx);
}