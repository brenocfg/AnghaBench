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
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int len; int cap; scalar_t__ unused_bits; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_ensure_buffer (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int fz_runetochar (char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 

void
fz_append_rune(fz_context *ctx, fz_buffer *buf, int c)
{
	char data[10];
	int len = fz_runetochar(data, c);
	if (buf->len + len > buf->cap)
		fz_ensure_buffer(ctx, buf, buf->len + len);
	memcpy(buf->data + buf->len, data, len);
	buf->len += len;
	buf->unused_bits = 0;
}