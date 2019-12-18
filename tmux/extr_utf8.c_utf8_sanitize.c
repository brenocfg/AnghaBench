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
struct utf8_data {size_t width; int /*<<< orphan*/  have; } ;
typedef  enum utf8_state { ____Placeholder_utf8_state } utf8_state ;

/* Variables and functions */
 int UTF8_DONE ; 
 int UTF8_MORE ; 
 int utf8_append (struct utf8_data*,char const) ; 
 int utf8_open (struct utf8_data*,char const) ; 
 char* xreallocarray (char*,size_t,int) ; 

char *
utf8_sanitize(const char *src)
{
	char			*dst;
	size_t			 n;
	enum utf8_state		 more;
	struct utf8_data	 ud;
	u_int			 i;

	dst = NULL;

	n = 0;
	while (*src != '\0') {
		dst = xreallocarray(dst, n + 1, sizeof *dst);
		if ((more = utf8_open(&ud, *src)) == UTF8_MORE) {
			while (*++src != '\0' && more == UTF8_MORE)
				more = utf8_append(&ud, *src);
			if (more == UTF8_DONE) {
				dst = xreallocarray(dst, n + ud.width,
				    sizeof *dst);
				for (i = 0; i < ud.width; i++)
					dst[n++] = '_';
				continue;
			}
			src -= ud.have;
		}
		if (*src > 0x1f && *src < 0x7f)
			dst[n++] = *src;
		else
			dst[n++] = '_';
		src++;
	}

	dst = xreallocarray(dst, n + 1, sizeof *dst);
	dst[n] = '\0';
	return (dst);
}