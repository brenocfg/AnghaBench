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
struct TYPE_3__ {int bidx; int word; int /*<<< orphan*/  chain; } ;
typedef  TYPE_1__ fz_faxd ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int EOF ; 
 int fz_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fill_bits(fz_context *ctx, fz_faxd *fax)
{
	/* The longest length of bits we'll ever need is 13. Never read more
	 * than we need to avoid unnecessary overreading of the end of the
	 * stream. */
	while (fax->bidx > (32-13))
	{
		int c = fz_read_byte(ctx, fax->chain);
		if (c == EOF)
			return EOF;
		fax->bidx -= 8;
		fax->word |= c << fax->bidx;
	}
	return 0;
}