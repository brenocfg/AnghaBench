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
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 unsigned char* fz_malloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * fz_new_buffer_from_data (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

__attribute__((used)) static fz_buffer *hexbuf(fz_context *ctx, const unsigned char *p, size_t n)
{
	static const char hex[17] = "0123456789abcdef";
	int x = 0;
	size_t len = n * 2 + (n / 32) + 1;
	unsigned char *data = fz_malloc(ctx, len);
	fz_buffer *buf = fz_new_buffer_from_data(ctx, data, len);

	while (n--)
	{
		*data++ = hex[*p >> 4];
		*data++ = hex[*p & 15];
		if (++x == 32)
		{
			*data++ = '\n';
			x = 0;
		}
		p++;
	}

	*data++ = '>';

	return buf;
}