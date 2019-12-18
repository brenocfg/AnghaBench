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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * fz_fopen_utf8 (char const*,char*) ; 
 int /*<<< orphan*/ * fz_open_file_ptr_progressive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void (*) (void*,int),void*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 

fz_stream *
fz_open_file_progressive(fz_context *ctx, const char *name, int kbps, void (*on_data)(void*,int), void *opaque)
{
	FILE *f;
#ifdef _WIN32
	f = fz_fopen_utf8(name, "rb");
#else
	f = fopen(name, "rb");
#endif
	if (f == NULL)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot open %s", name);
	return fz_open_file_ptr_progressive(ctx, f, kbps, on_data, opaque);
}