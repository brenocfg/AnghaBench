#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* buf; size_t len; } ;
typedef  TYPE_1__ parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  MALLOCX_TCACHE_NONE ; 
 char* mallocx (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* rallocx (char*,size_t,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static bool
parser_append(parser_t *parser, const char *str) {
	size_t len = strlen(str);
	char *buf = (parser->buf == NULL) ? mallocx(len + 1,
	    MALLOCX_TCACHE_NONE) : rallocx(parser->buf, parser->len + len + 1,
	    MALLOCX_TCACHE_NONE);
	if (buf == NULL) {
		return true;
	}
	memcpy(&buf[parser->len], str, len + 1);
	parser->buf = buf;
	parser->len += len;
	return false;
}