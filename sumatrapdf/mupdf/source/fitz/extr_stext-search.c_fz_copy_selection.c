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
struct callbacks {int /*<<< orphan*/ * arg; int /*<<< orphan*/  on_line; int /*<<< orphan*/  on_char; } ;
typedef  int /*<<< orphan*/  fz_stext_page ;
typedef  int /*<<< orphan*/  fz_point ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_buffer_extract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  fz_drop_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_enumerate_selection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct callbacks*) ; 
 int /*<<< orphan*/ * fz_new_buffer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_terminate_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_copy_char ; 
 int /*<<< orphan*/  on_copy_line_crlf ; 
 int /*<<< orphan*/  on_copy_line_lf ; 

char *
fz_copy_selection(fz_context *ctx, fz_stext_page *page, fz_point a, fz_point b, int crlf)
{
	struct callbacks cb;
	fz_buffer *buffer;
	unsigned char *s;

	buffer = fz_new_buffer(ctx, 1024);

	cb.on_char = on_copy_char;
	cb.on_line = crlf ? on_copy_line_crlf : on_copy_line_lf;
	cb.arg = buffer;

	fz_enumerate_selection(ctx, page, a, b, &cb);

	fz_terminate_buffer(ctx, buffer);
	fz_buffer_extract(ctx, buffer, &s); /* take over the data */
	fz_drop_buffer(ctx, buffer);
	return (char*)s;
}