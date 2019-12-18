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
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 size_t fz_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  fz_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char const*,size_t) ; 
 size_t nelem (unsigned char const*) ; 

int
fz_is_zip_archive(fz_context *ctx, fz_stream *file)
{
	const unsigned char signature[4] = { 'P', 'K', 0x03, 0x04 };
	unsigned char data[4];
	size_t n;

	fz_seek(ctx, file, 0, 0);
	n = fz_read(ctx, file, data, nelem(data));
	if (n != nelem(signature))
		return 0;
	if (memcmp(data, signature, nelem(signature)))
		return 0;

	return 1;
}