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
typedef  int /*<<< orphan*/  EdonRState ;

/* Variables and functions */
 int /*<<< orphan*/  EdonRUpdate (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static int
edonr_incremental(void *buf, size_t size, void *arg)
{
	EdonRState *ctx = arg;
	EdonRUpdate(ctx, buf, size * 8);
	return (0);
}