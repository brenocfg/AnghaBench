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
struct refTables {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int LZ4_64KLIMIT ; 
 int LZ4_compress64kCtx (void*,char const*,char*,int,int) ; 
 int LZ4_compressCtx (void*,char const*,char*,int,int) ; 
 void* kmem_cache_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * lz4_cache ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
real_LZ4_compress(const char *source, char *dest, int isize, int osize)
{
	void *ctx;
	int result;

	ASSERT(lz4_cache != NULL);
	ctx = kmem_cache_alloc(lz4_cache, KM_SLEEP);

	/*
	 * out of kernel memory, gently fall through - this will disable
	 * compression in zio_compress_data
	 */
	if (ctx == NULL)
		return (0);

	memset(ctx, 0, sizeof (struct refTables));

	if (isize < LZ4_64KLIMIT)
		result = LZ4_compress64kCtx(ctx, source, dest, isize, osize);
	else
		result = LZ4_compressCtx(ctx, source, dest, isize, osize);

	kmem_cache_free(lz4_cache, ctx);
	return (result);
}