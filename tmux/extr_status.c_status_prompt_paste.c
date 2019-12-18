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
typedef  size_t u_int ;
struct utf8_data {scalar_t__ size; scalar_t__ have; } ;
struct paste_buffer {int dummy; } ;
struct client {size_t prompt_index; struct utf8_data* prompt_saved; struct utf8_data* prompt_buffer; } ;
typedef  enum utf8_state { ____Placeholder_utf8_state } utf8_state ;

/* Variables and functions */
 int UTF8_DONE ; 
 int UTF8_MORE ; 
 int /*<<< orphan*/  free (struct utf8_data*) ; 
 int /*<<< orphan*/  memcpy (struct utf8_data*,struct utf8_data*,size_t) ; 
 int /*<<< orphan*/  memmove (struct utf8_data*,struct utf8_data*,size_t) ; 
 char* paste_buffer_data (struct paste_buffer*,size_t*) ; 
 struct paste_buffer* paste_get_top (int /*<<< orphan*/ *) ; 
 int utf8_append (struct utf8_data*,char const) ; 
 int utf8_open (struct utf8_data*,char const) ; 
 int /*<<< orphan*/  utf8_set (struct utf8_data*,char const) ; 
 size_t utf8_strlen (struct utf8_data*) ; 
 void* xreallocarray (struct utf8_data*,size_t,int) ; 

__attribute__((used)) static int
status_prompt_paste(struct client *c)
{
	struct paste_buffer	*pb;
	const char		*bufdata;
	size_t			 size, n, bufsize;
	u_int			 i;
	struct utf8_data	*ud, *udp;
	enum utf8_state		 more;

	size = utf8_strlen(c->prompt_buffer);
	if (c->prompt_saved != NULL) {
		ud = c->prompt_saved;
		n = utf8_strlen(c->prompt_saved);
	} else {
		if ((pb = paste_get_top(NULL)) == NULL)
			return (0);
		bufdata = paste_buffer_data(pb, &bufsize);
		ud = xreallocarray(NULL, bufsize + 1, sizeof *ud);
		udp = ud;
		for (i = 0; i != bufsize; /* nothing */) {
			more = utf8_open(udp, bufdata[i]);
			if (more == UTF8_MORE) {
				while (++i != bufsize && more == UTF8_MORE)
					more = utf8_append(udp, bufdata[i]);
				if (more == UTF8_DONE) {
					udp++;
					continue;
				}
				i -= udp->have;
			}
			if (bufdata[i] <= 31 || bufdata[i] >= 127)
				break;
			utf8_set(udp, bufdata[i]);
			udp++;
			i++;
		}
		udp->size = 0;
		n = udp - ud;
	}
	if (n == 0)
		return (0);

	c->prompt_buffer = xreallocarray(c->prompt_buffer, size + n + 1,
	    sizeof *c->prompt_buffer);
	if (c->prompt_index == size) {
		memcpy(c->prompt_buffer + c->prompt_index, ud,
		    n * sizeof *c->prompt_buffer);
		c->prompt_index += n;
		c->prompt_buffer[c->prompt_index].size = 0;
	} else {
		memmove(c->prompt_buffer + c->prompt_index + n,
		    c->prompt_buffer + c->prompt_index,
		    (size + 1 - c->prompt_index) * sizeof *c->prompt_buffer);
		memcpy(c->prompt_buffer + c->prompt_index, ud,
		    n * sizeof *c->prompt_buffer);
		c->prompt_index += n;
	}

	if (ud != c->prompt_saved)
		free(ud);
	return (1);
}