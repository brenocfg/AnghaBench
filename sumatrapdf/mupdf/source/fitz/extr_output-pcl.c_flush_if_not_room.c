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
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void flush_if_not_room(fz_context *ctx, fz_output *out, const unsigned char *comp, int *fill, int len)
{
	if (len + *fill >= 32767)
	{
		/* Can't fit any data, so flush */
		fz_write_printf(ctx, out, "\033*b%dW", *fill);
		fz_write_data(ctx, out, comp, *fill);
		*fill = 0;
	}
}