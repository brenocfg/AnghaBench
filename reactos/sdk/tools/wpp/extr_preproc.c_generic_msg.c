#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_2__ {char* input; int line_number; int char_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isprint (char) ; 
 TYPE_1__ pp_status ; 
 char* pp_xstrdup (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generic_msg(const char *s, const char *t, const char *n, va_list ap)
{
	fprintf(stderr, "%s:%d:%d: %s: ", pp_status.input ? pp_status.input : "stdin",
                pp_status.line_number, pp_status.char_number, t);
	vfprintf(stderr, s, ap);
#ifdef WANT_NEAR_INDICATION
	{
		char *cpy, *p;
		if(n)
		{
			cpy = pp_xstrdup(n);
			if(!cpy)
				goto end;
			for (p = cpy; *p; p++) if(!isprint(*p)) *p = ' ';
			fprintf(stderr, " near '%s'", cpy);
			free(cpy);
		}
	}
end:
#endif
	fprintf(stderr, "\n");
}