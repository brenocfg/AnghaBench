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
typedef  int /*<<< orphan*/  u_char ;
struct utf8_data {size_t size; int /*<<< orphan*/  have; int /*<<< orphan*/ * data; } ;
typedef  enum utf8_state { ____Placeholder_utf8_state } utf8_state ;

/* Variables and functions */
 int UTF8_DONE ; 
 int UTF8_MORE ; 
 scalar_t__ isalpha (int /*<<< orphan*/ ) ; 
 int utf8_append (struct utf8_data*,char const) ; 
 int utf8_open (struct utf8_data*,char const) ; 
 char* vis (char*,char const,int,char const) ; 

int
utf8_strvis(char *dst, const char *src, size_t len, int flag)
{
	struct utf8_data	 ud;
	const char		*start, *end;
	enum utf8_state		 more;
	size_t			 i;

	start = dst;
	end = src + len;

	while (src < end) {
		if ((more = utf8_open(&ud, *src)) == UTF8_MORE) {
			while (++src < end && more == UTF8_MORE)
				more = utf8_append(&ud, *src);
			if (more == UTF8_DONE) {
				/* UTF-8 character finished. */
				for (i = 0; i < ud.size; i++)
					*dst++ = ud.data[i];
				continue;
			}
			/* Not a complete, valid UTF-8 character. */
			src -= ud.have;
		}
		if (src[0] == '$' && src < end - 1) {
			if (isalpha((u_char)src[1]) ||
			    src[1] == '_' ||
			    src[1] == '{')
				*dst++ = '\\';
			*dst++ = '$';
		} else if (src < end - 1)
			dst = vis(dst, src[0], flag, src[1]);
		else if (src < end)
			dst = vis(dst, src[0], flag, '\0');
		src++;
	}

	*dst = '\0';
	return (dst - start);
}