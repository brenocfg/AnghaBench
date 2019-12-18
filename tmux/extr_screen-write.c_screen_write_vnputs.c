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
typedef  int /*<<< orphan*/  va_list ;
typedef  char u_char ;
struct utf8_data {size_t width; scalar_t__ size; } ;
struct screen_write_ctx {int dummy; } ;
struct grid_cell {int /*<<< orphan*/  attr; struct utf8_data data; } ;
typedef  scalar_t__ ssize_t ;
typedef  enum utf8_state { ____Placeholder_utf8_state } utf8_state ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_ATTR_CHARSET ; 
 int UTF8_DONE ; 
 scalar_t__ UTF8_MORE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (struct grid_cell*,struct grid_cell const*,int) ; 
 int /*<<< orphan*/  screen_write_cell (struct screen_write_ctx*,struct grid_cell*) ; 
 int /*<<< orphan*/  screen_write_putc (struct screen_write_ctx*,struct grid_cell*,char) ; 
 size_t strlen (char*) ; 
 int utf8_append (struct utf8_data*,char) ; 
 scalar_t__ utf8_open (struct utf8_data*,char) ; 
 int /*<<< orphan*/  xvasprintf (char**,char const*,int /*<<< orphan*/ ) ; 

void
screen_write_vnputs(struct screen_write_ctx *ctx, ssize_t maxlen,
    const struct grid_cell *gcp, const char *fmt, va_list ap)
{
	struct grid_cell	gc;
	struct utf8_data       *ud = &gc.data;
	char   		       *msg;
	u_char 		       *ptr;
	size_t		 	left, size = 0;
	enum utf8_state		more;

	memcpy(&gc, gcp, sizeof gc);
	xvasprintf(&msg, fmt, ap);

	ptr = msg;
	while (*ptr != '\0') {
		if (*ptr > 0x7f && utf8_open(ud, *ptr) == UTF8_MORE) {
			ptr++;

			left = strlen(ptr);
			if (left < (size_t)ud->size - 1)
				break;
			while ((more = utf8_append(ud, *ptr)) == UTF8_MORE)
				ptr++;
			ptr++;

			if (more != UTF8_DONE)
				continue;
			if (maxlen > 0 && size + ud->width > (size_t)maxlen) {
				while (size < (size_t)maxlen) {
					screen_write_putc(ctx, &gc, ' ');
					size++;
				}
				break;
			}
			size += ud->width;
			screen_write_cell(ctx, &gc);
		} else {
			if (maxlen > 0 && size + 1 > (size_t)maxlen)
				break;

			if (*ptr == '\001')
				gc.attr ^= GRID_ATTR_CHARSET;
			else if (*ptr > 0x1f && *ptr < 0x7f) {
				size++;
				screen_write_putc(ctx, &gc, *ptr);
			}
			ptr++;
		}
	}

	free(msg);
}