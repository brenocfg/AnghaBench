#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t rp; } ;
typedef  TYPE_1__ fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 size_t fz_available (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,size_t,size_t) ; 

size_t
fz_read(fz_context *ctx, fz_stream *stm, unsigned char *buf, size_t len)
{
	size_t count, n;

	count = 0;
	do
	{
		n = fz_available(ctx, stm, len);
		if (n > len)
			n = len;
		if (n == 0)
			break;

		memcpy(buf, stm->rp, n);
		stm->rp += n;
		buf += n;
		count += n;
		len -= n;
	}
	while (len > 0);

	return count;
}