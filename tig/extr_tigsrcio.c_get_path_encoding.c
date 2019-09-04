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
struct encoding {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CHARSET_SEP ; 
 int /*<<< orphan*/  ENCODING_SEP ; 
 char* ENCODING_UTF8 ; 
 int SIZEOF_STR ; 
 int /*<<< orphan*/  STRING_SIZE (int /*<<< orphan*/ ) ; 
 struct encoding* encoding_open (char*) ; 
 int /*<<< orphan*/  io_run_buf (char const**,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 

struct encoding *
get_path_encoding(const char *path, struct encoding *default_encoding)
{
	const char *check_attr_argv[] = {
		"git", "check-attr", "encoding", "--", path, NULL
	};
	char buf[SIZEOF_STR];
	char *encoding;

	/* <path>: encoding: <encoding> */

	if (!*path || !io_run_buf(check_attr_argv, buf, sizeof(buf), NULL, false)
	    || !(encoding = strstr(buf, ENCODING_SEP)))
		return default_encoding;

	encoding += STRING_SIZE(ENCODING_SEP);
	if (!strcmp(encoding, ENCODING_UTF8)
	    || !strcmp(encoding, "unspecified")
	    || !strcmp(encoding, "set")) {
		const char *file_argv[] = {
			"file", "--mime", "--", path, NULL
		};

		if (!*path || !io_run_buf(file_argv, buf, sizeof(buf), NULL, false)
		    || !(encoding = strstr(buf, CHARSET_SEP)))
			return default_encoding;

		encoding += STRING_SIZE(CHARSET_SEP);
	}

	return encoding_open(encoding);
}