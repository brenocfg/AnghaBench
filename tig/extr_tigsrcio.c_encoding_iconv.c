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
struct buffer {char* member_0; size_t member_1; char const* data; } ;
typedef  int /*<<< orphan*/  iconv_t ;

/* Variables and functions */
 scalar_t__ encoding_convert_string (int /*<<< orphan*/ ,struct buffer*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strndup (char const*,size_t) ; 

const char *
encoding_iconv(iconv_t iconv_cd, const char *string, size_t length)
{
	char *instr = strndup(string, length);
	struct buffer buf = { instr, length };
	const char *ret = buf.data && encoding_convert_string(iconv_cd, &buf) ? buf.data : string;

	free(instr);
	return ret == instr ? string : ret;
}