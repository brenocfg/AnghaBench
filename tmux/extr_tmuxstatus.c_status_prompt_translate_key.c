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
struct client {scalar_t__ prompt_mode; int /*<<< orphan*/  flags; } ;
typedef  int key_code ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_REDRAWSTATUS ; 
#define  KEYC_BSPACE 135 
#define  KEYC_DC 134 
#define  KEYC_DOWN 133 
#define  KEYC_END 132 
 char KEYC_ESCAPE ; 
#define  KEYC_HOME 131 
#define  KEYC_LEFT 130 
#define  KEYC_RIGHT 129 
#define  KEYC_UP 128 
 scalar_t__ PROMPT_COMMAND ; 
 scalar_t__ PROMPT_ENTRY ; 

__attribute__((used)) static int
status_prompt_translate_key(struct client *c, key_code key, key_code *new_key)
{
	if (c->prompt_mode == PROMPT_ENTRY) {
		switch (key) {
		case '\003': /* C-c */
		case '\010': /* C-h */
		case '\011': /* Tab */
		case '\025': /* C-u */
		case '\027': /* C-w */
		case '\n':
		case '\r':
		case KEYC_BSPACE:
		case KEYC_DC:
		case KEYC_DOWN:
		case KEYC_END:
		case KEYC_HOME:
		case KEYC_LEFT:
		case KEYC_RIGHT:
		case KEYC_UP:
			*new_key = key;
			return (1);
		case '\033': /* Escape */
			c->prompt_mode = PROMPT_COMMAND;
			c->flags |= CLIENT_REDRAWSTATUS;
			return (0);
		}
		*new_key = key;
		return (2);
	}

	switch (key) {
	case 'A':
	case 'I':
	case 'C':
	case 's':
	case 'a':
		c->prompt_mode = PROMPT_ENTRY;
		c->flags |= CLIENT_REDRAWSTATUS;
		break; /* switch mode and... */
	case 'S':
		c->prompt_mode = PROMPT_ENTRY;
		c->flags |= CLIENT_REDRAWSTATUS;
		*new_key = '\025'; /* C-u */
		return (1);
	case 'i':
	case '\033': /* Escape */
		c->prompt_mode = PROMPT_ENTRY;
		c->flags |= CLIENT_REDRAWSTATUS;
		return (0);
	}

	switch (key) {
	case 'A':
	case '$':
		*new_key = KEYC_END;
		return (1);
	case 'I':
	case '0':
	case '^':
		*new_key = KEYC_HOME;
		return (1);
	case 'C':
	case 'D':
		*new_key = '\013'; /* C-k */
		return (1);
	case KEYC_BSPACE:
	case 'X':
		*new_key = KEYC_BSPACE;
		return (1);
	case 'b':
	case 'B':
		*new_key = 'b'|KEYC_ESCAPE;
		return (1);
	case 'd':
		*new_key = '\025';
		return (1);
	case 'e':
	case 'E':
	case 'w':
	case 'W':
		*new_key = 'f'|KEYC_ESCAPE;
		return (1);
	case 'p':
		*new_key = '\031'; /* C-y */
		return (1);
	case 's':
	case KEYC_DC:
	case 'x':
		*new_key = KEYC_DC;
		return (1);
	case KEYC_DOWN:
	case 'j':
		*new_key = KEYC_DOWN;
		return (1);
	case KEYC_LEFT:
	case 'h':
		*new_key = KEYC_LEFT;
		return (1);
	case 'a':
	case KEYC_RIGHT:
	case 'l':
		*new_key = KEYC_RIGHT;
		return (1);
	case KEYC_UP:
	case 'k':
		*new_key = KEYC_UP;
		return (1);
	case '\010' /* C-h */:
	case '\003' /* C-c */:
	case '\n':
	case '\r':
		return (1);
	}
	return (0);
}