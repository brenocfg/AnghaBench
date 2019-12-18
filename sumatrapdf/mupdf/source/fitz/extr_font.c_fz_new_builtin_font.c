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
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 unsigned char* fz_lookup_builtin_font (int /*<<< orphan*/ *,char const*,int,int,int*) ; 
 int /*<<< orphan*/ * fz_new_font_from_memory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 

fz_font *
fz_new_builtin_font(fz_context *ctx, const char *name, int is_bold, int is_italic)
{
	const unsigned char *data;
	int size;
	data = fz_lookup_builtin_font(ctx, name, is_bold, is_italic, &size);
	if (!data)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find builtin font with name '%s'", name);
	return fz_new_font_from_memory(ctx, NULL, data, size, 0, 0);
}