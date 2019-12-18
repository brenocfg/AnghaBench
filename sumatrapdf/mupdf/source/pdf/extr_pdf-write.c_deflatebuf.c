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
typedef  scalar_t__ uLongf ;
typedef  scalar_t__ uLong ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int Z_OK ; 
 int compress (unsigned char*,scalar_t__*,unsigned char const*,scalar_t__) ; 
 size_t compressBound (scalar_t__) ; 
 int /*<<< orphan*/  fz_drop_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* fz_malloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * fz_new_buffer_from_data (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  fz_resize_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static fz_buffer *deflatebuf(fz_context *ctx, const unsigned char *p, size_t n)
{
	fz_buffer *buf;
	uLongf csize;
	int t;
	uLong longN = (uLong)n;
	unsigned char *data;
	size_t cap;

	if (n != (size_t)longN)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Buffer too large to deflate");

	cap = compressBound(longN);
	data = fz_malloc(ctx, cap);
	buf = fz_new_buffer_from_data(ctx, data, cap);
	csize = (uLongf)cap;
	t = compress(data, &csize, p, longN);
	if (t != Z_OK)
	{
		fz_drop_buffer(ctx, buf);
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot deflate buffer");
	}
	fz_resize_buffer(ctx, buf, csize);
	return buf;
}