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
struct TYPE_4__ {int /*<<< orphan*/  info_ptr; int /*<<< orphan*/  png_ptr; } ;
typedef  TYPE_1__* PNGWriteInfoRef ;
typedef  int /*<<< orphan*/  MMBitmapRef ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_TRANSFORM_IDENTITY ; 
 TYPE_1__* createPNGWriteInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroyPNGWriteInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  png_init_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_write_png (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int saveMMBitmapAsPNG(MMBitmapRef bitmap, const char *path)
{
	FILE *fp = fopen(path, "wb");
	PNGWriteInfoRef info;
	if (fp == NULL) return -1;

	if ((info = createPNGWriteInfo(bitmap)) == NULL) {
		fclose(fp);
		return -1;
	}

	png_init_io(info->png_ptr, fp);
	png_write_png(info->png_ptr, info->info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
	fclose(fp);

	destroyPNGWriteInfo(info);
	return 0;
}