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
typedef  scalar_t__ u_int ;
struct utf8_data {char const* data; int size; scalar_t__ width; int /*<<< orphan*/  have; } ;
typedef  enum utf8_state { ____Placeholder_utf8_state } utf8_state ;

/* Variables and functions */
 int UTF8_DONE ; 
 int UTF8_MORE ; 
 char* format_skip (char const*,char*) ; 
 scalar_t__ format_width (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 
 int utf8_append (struct utf8_data*,char const) ; 
 int utf8_open (struct utf8_data*,char const) ; 
 char* xmalloc (scalar_t__) ; 
 char* xstrdup (char const*) ; 

char *
format_trim_right(const char *expanded, u_int limit)
{
	char			*copy, *out;
	const char		*cp = expanded, *end;
	u_int			 width = 0, total_width, skip;
	struct utf8_data	 ud;
	enum utf8_state		 more;

	total_width = format_width(expanded);
	if (total_width <= limit)
		return (xstrdup(expanded));
	skip = total_width - limit;

	out = copy = xmalloc(strlen(expanded) + 1);
	while (*cp != '\0') {
		if (cp[0] == '#' && cp[1] == '[') {
			end = format_skip(cp + 2, "]");
			if (end == NULL)
				break;
			memcpy(out, cp, end + 1 - cp);
			out += (end + 1 - cp);
			cp = end + 1;
		} else if ((more = utf8_open(&ud, *cp)) == UTF8_MORE) {
			while (*++cp != '\0' && more == UTF8_MORE)
				more = utf8_append(&ud, *cp);
			if (more == UTF8_DONE) {
				if (width >= skip) {
					memcpy(out, ud.data, ud.size);
					out += ud.size;
				}
				width += ud.width;
			} else
				cp -= ud.have;
		} else if (*cp > 0x1f && *cp < 0x7f) {
			if (width >= skip)
				*out++ = *cp;
			width++;
			cp++;
		} else
			cp++;
	}
	*out = '\0';
	return (copy);
}