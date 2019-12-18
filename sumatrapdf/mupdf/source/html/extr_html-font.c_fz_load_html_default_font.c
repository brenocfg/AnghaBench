#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** fonts; } ;
typedef  TYPE_1__ fz_html_font_set ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int is_serif; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 TYPE_3__* fz_font_flags (int /*<<< orphan*/ *) ; 
 unsigned char* fz_lookup_builtin_font (int /*<<< orphan*/ *,char const*,int,int,int*) ; 
 int /*<<< orphan*/ * fz_new_font_from_memory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static fz_font *
fz_load_html_default_font(fz_context *ctx, fz_html_font_set *set, const char *family, int is_bold, int is_italic)
{
	int is_mono = !strcmp(family, "monospace");
	int is_sans = !strcmp(family, "sans-serif");
	const char *real_family = is_mono ? "Courier" : is_sans ? "Helvetica" : "Charis SIL";
	const char *backup_family = is_mono ? "Courier" : is_sans ? "Helvetica" : "Times";
	int idx = (is_mono ? 8 : is_sans ? 4 : 0) + is_bold * 2 + is_italic;
	if (!set->fonts[idx])
	{
		const unsigned char *data;
		int size;

		data = fz_lookup_builtin_font(ctx, real_family, is_bold, is_italic, &size);
		if (!data)
			data = fz_lookup_builtin_font(ctx, backup_family, is_bold, is_italic, &size);
		if (!data)
			fz_throw(ctx, FZ_ERROR_GENERIC, "cannot load html font: %s", real_family);
		set->fonts[idx] = fz_new_font_from_memory(ctx, NULL, data, size, 0, 1);
		fz_font_flags(set->fonts[idx])->is_serif = !is_sans;
	}
	return set->fonts[idx];
}