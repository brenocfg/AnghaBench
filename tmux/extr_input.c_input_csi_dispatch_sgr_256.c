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
typedef  scalar_t__ u_int ;
struct input_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ input_csi_dispatch_sgr_256_do (struct input_ctx*,int,int) ; 
 int input_get (struct input_ctx*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
input_csi_dispatch_sgr_256(struct input_ctx *ictx, int fgbg, u_int *i)
{
	int	c;

	c = input_get(ictx, (*i) + 1, 0, -1);
	if (input_csi_dispatch_sgr_256_do(ictx, fgbg, c))
		(*i)++;
}