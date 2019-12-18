#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_term {TYPE_2__* codes; } ;
typedef  enum tty_code_code { ____Placeholder_tty_code_code } tty_code_code ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {char* number; int /*<<< orphan*/  flag; int /*<<< orphan*/  string; } ;
struct TYPE_5__ {int type; TYPE_1__ value; } ;

/* Variables and functions */
#define  TTYCODE_FLAG 131 
#define  TTYCODE_NONE 130 
#define  TTYCODE_NUMBER 129 
#define  TTYCODE_STRING 128 
 int VIS_CSTYLE ; 
 int VIS_NL ; 
 int VIS_OCTAL ; 
 int VIS_TAB ; 
 int /*<<< orphan*/  strnvis (char*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* tty_term_codes ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int,int /*<<< orphan*/ ,...) ; 

const char *
tty_term_describe(struct tty_term *term, enum tty_code_code code)
{
	static char	 s[256];
	char		 out[128];

	switch (term->codes[code].type) {
	case TTYCODE_NONE:
		xsnprintf(s, sizeof s, "%4u: %s: [missing]",
		    code, tty_term_codes[code].name);
		break;
	case TTYCODE_STRING:
		strnvis(out, term->codes[code].value.string, sizeof out,
		    VIS_OCTAL|VIS_CSTYLE|VIS_TAB|VIS_NL);
		xsnprintf(s, sizeof s, "%4u: %s: (string) %s",
		    code, tty_term_codes[code].name,
		    out);
		break;
	case TTYCODE_NUMBER:
		xsnprintf(s, sizeof s, "%4u: %s: (number) %d",
		    code, tty_term_codes[code].name,
		    term->codes[code].value.number);
		break;
	case TTYCODE_FLAG:
		xsnprintf(s, sizeof s, "%4u: %s: (flag) %s",
		    code, tty_term_codes[code].name,
		    term->codes[code].value.flag ? "true" : "false");
		break;
	}
	return (s);
}