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
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 float measure_simple_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  write_stamp_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
write_stamp(fz_context *ctx, fz_buffer *buf, fz_font *font, const char *text, float y, float h)
{
	float tw = measure_simple_string(ctx, font, text) * h;
	fz_append_string(ctx, buf, "BT\n");
	fz_append_printf(ctx, buf, "/Times %g Tf\n", h);
	fz_append_printf(ctx, buf, "%g %g Td\n", (190-tw)/2, y);
	write_stamp_string(ctx, buf, font, text);
	fz_append_string(ctx, buf, " Tj\n");
	fz_append_string(ctx, buf, "ET\n");
}