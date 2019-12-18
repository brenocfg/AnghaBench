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
struct TYPE_3__ {unsigned int end; unsigned int p; } ;
typedef  TYPE_1__* STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  STRNCPY (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  hexdump (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  seamless_line_handler ; 
 int /*<<< orphan*/  str_handle_lines (int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (unsigned int) ; 

__attribute__((used)) static void
seamless_process(RDPCLIENT * This, STREAM s)
{
	unsigned int pkglen;
	static char *rest = NULL;
	char *buf;

	pkglen = s->end - s->p;
	/* str_handle_lines requires null terminated strings */
	buf = xmalloc(pkglen + 1);
	STRNCPY(buf, (char *) s->p, pkglen + 1);
#if 0
	printf("seamless recv:\n");
	hexdump(s->p, pkglen);
#endif

	str_handle_lines(This, buf, &rest, seamless_line_handler, NULL);

	xfree(buf);
}