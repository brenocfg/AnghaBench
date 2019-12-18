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
struct fmt {int last; int len; int cap; int* buf; int* ptr; scalar_t__ col; scalar_t__ sep; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int* fz_malloc (int /*<<< orphan*/ *,int) ; 
 int* fz_realloc (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  isdelim (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static inline void fmt_putc(fz_context *ctx, struct fmt *fmt, int c)
{
	if (fmt->sep && !isdelim(fmt->last) && !isdelim(c)) {
		fmt->sep = 0;
		fmt_putc(ctx, fmt, ' ');
	}
	fmt->sep = 0;

	if (fmt->len >= fmt->cap)
	{
		fmt->cap *= 2;
		if (fmt->buf == fmt->ptr)
		{
			fmt->ptr = fz_malloc(ctx, fmt->cap);
			memcpy(fmt->ptr, fmt->buf, fmt->len);
		}
		else
		{
			fmt->ptr = fz_realloc(ctx, fmt->ptr, fmt->cap);
		}
	}

	fmt->ptr[fmt->len] = c;

	if (c == '\n')
		fmt->col = 0;
	else
		fmt->col ++;

	fmt->len ++;

	fmt->last = c;
}