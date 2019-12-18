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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * fz_fopen_utf8 (char const*,char*) ; 

int
fz_file_exists(fz_context *ctx, const char *path)
{
	FILE *file;
#ifdef _WIN32
	file = fz_fopen_utf8(path, "rb");
#else
	file = fopen(path, "rb");
#endif
	if (file)
		fclose(file);
	return !!file;
}