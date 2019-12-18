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
struct TYPE_3__ {int rtl; char const* start; char const* end; char const* s; int script; int language; int small_caps; int /*<<< orphan*/ * next_font; int /*<<< orphan*/ * font; int /*<<< orphan*/ * base_font; int /*<<< orphan*/ * hb_buf; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ string_walker ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static void init_string_walker(fz_context *ctx, string_walker *walker, hb_buffer_t *hb_buf, int rtl, fz_font *font, int script, int language, int small_caps, const char *text)
{
	walker->ctx = ctx;
	walker->hb_buf = hb_buf;
	walker->rtl = rtl;
	walker->start = text;
	walker->end = text;
	walker->s = text;
	walker->base_font = font;
	walker->script = script;
	walker->language = language;
	walker->font = NULL;
	walker->next_font = NULL;
	walker->small_caps = small_caps;
}