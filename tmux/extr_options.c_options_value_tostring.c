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
union options_value {size_t number; char* string; int /*<<< orphan*/  style; int /*<<< orphan*/  cmdlist; } ;
struct options_entry {TYPE_1__* tableentry; } ;
struct TYPE_2__ {int type; char** choices; } ;

/* Variables and functions */
 scalar_t__ OPTIONS_IS_COMMAND (struct options_entry*) ; 
 scalar_t__ OPTIONS_IS_NUMBER (struct options_entry*) ; 
 scalar_t__ OPTIONS_IS_STRING (struct options_entry*) ; 
 scalar_t__ OPTIONS_IS_STYLE (struct options_entry*) ; 
#define  OPTIONS_TABLE_CHOICE 135 
#define  OPTIONS_TABLE_COLOUR 134 
#define  OPTIONS_TABLE_COMMAND 133 
#define  OPTIONS_TABLE_FLAG 132 
#define  OPTIONS_TABLE_KEY 131 
#define  OPTIONS_TABLE_NUMBER 130 
#define  OPTIONS_TABLE_STRING 129 
#define  OPTIONS_TABLE_STYLE 128 
 char* cmd_list_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* colour_tostring (size_t) ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 char* key_string_lookup_key (size_t) ; 
 char* style_tostring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,size_t) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
options_value_tostring(struct options_entry *o, union options_value *ov,
    int numeric)
{
	char	*s;

	if (OPTIONS_IS_COMMAND(o))
		return (cmd_list_print(ov->cmdlist, 0));
	if (OPTIONS_IS_STYLE(o))
		return (xstrdup(style_tostring(&ov->style)));
	if (OPTIONS_IS_NUMBER(o)) {
		switch (o->tableentry->type) {
		case OPTIONS_TABLE_NUMBER:
			xasprintf(&s, "%lld", ov->number);
			break;
		case OPTIONS_TABLE_KEY:
			s = xstrdup(key_string_lookup_key(ov->number));
			break;
		case OPTIONS_TABLE_COLOUR:
			s = xstrdup(colour_tostring(ov->number));
			break;
		case OPTIONS_TABLE_FLAG:
			if (numeric)
				xasprintf(&s, "%lld", ov->number);
			else
				s = xstrdup(ov->number ? "on" : "off");
			break;
		case OPTIONS_TABLE_CHOICE:
			s = xstrdup(o->tableentry->choices[ov->number]);
			break;
		case OPTIONS_TABLE_STRING:
		case OPTIONS_TABLE_STYLE:
		case OPTIONS_TABLE_COMMAND:
			fatalx("not a number option type");
		}
		return (s);
	}
	if (OPTIONS_IS_STRING(o))
		return (xstrdup(ov->string));
	return (xstrdup(""));
}