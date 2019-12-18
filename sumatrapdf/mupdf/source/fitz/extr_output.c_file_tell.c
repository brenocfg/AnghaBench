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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int _ftelli64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int ftello (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t
file_tell(fz_context *ctx, void *opaque)
{
	FILE *file = opaque;
#ifdef _WIN32
	int64_t off = _ftelli64(file);
#else
	int64_t off = ftello(file);
#endif
	if (off == -1)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot ftell: %s", strerror(errno));
	return off;
}