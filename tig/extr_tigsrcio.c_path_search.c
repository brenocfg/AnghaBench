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

/* Variables and functions */
 int SIZEOF_STR ; 
 char* _PATH_DEFPATH ; 
 scalar_t__ access (char const*,int) ; 
 scalar_t__ strchr (char const*,char) ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  string_format (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  string_ncopy (char*,char const*,int) ; 
 int /*<<< orphan*/  string_ncopy_do (char*,size_t,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

bool
path_search(char *dst, size_t dstlen, const char *query, const char *colon_path, int access_flags)
{
	const char *_colon_path = _PATH_DEFPATH; /* emulate execlp() */
	char test[SIZEOF_STR];
	char elt[SIZEOF_STR];
	size_t elt_len;

	if (!query || !*query)
		return false;

	if (strchr(query, '/')) {
		if (access(query, access_flags))
			return false;
		string_ncopy_do(dst, dstlen, query, strlen(query));
		return true;
	}

	if (colon_path && *colon_path)
		_colon_path = colon_path;

	while (_colon_path && *_colon_path) {
		elt_len = strcspn(_colon_path, ":");
		if (elt_len)
			string_ncopy(elt, _colon_path, elt_len);
		else
			string_ncopy(elt, ".", 1);

		_colon_path += elt_len;
		if (*_colon_path)
			_colon_path += 1;

		string_format(test, "%s/%s", elt, query);
		if (!access(test, access_flags)) {
			string_ncopy_do(dst, dstlen, test, strlen(test));
			return true;
		}
	}
	return false;
}