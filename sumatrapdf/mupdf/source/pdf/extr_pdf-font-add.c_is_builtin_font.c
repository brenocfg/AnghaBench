#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_buffer_storage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char**) ; 
 unsigned char* fz_lookup_base14_font (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pdf_clean_font_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_builtin_font(fz_context *ctx, fz_font *font)
{
	int size;
	unsigned char *data;
	if (!font->buffer)
		return 0;
	fz_buffer_storage(ctx, font->buffer, &data);
	return fz_lookup_base14_font(ctx, pdf_clean_font_name(font->name), &size) == data;
}