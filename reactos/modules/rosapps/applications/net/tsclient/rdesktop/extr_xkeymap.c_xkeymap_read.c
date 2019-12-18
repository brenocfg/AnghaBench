#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8 ;
typedef  scalar_t__ uint16 ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_5__ {void* keyboard_functionkeys; void* keyboard_subtype; void* keyboard_type; void* enable_compose; int /*<<< orphan*/  keylayout; } ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  FILE ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KBD (char*) ; 
 void* False ; 
 int KEYMAP_MAX_LINE_LENGTH ; 
 int /*<<< orphan*/  MASK_ADD_BITS (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MapAltGrMask ; 
 int /*<<< orphan*/  MapInhibitMask ; 
 int /*<<< orphan*/  MapLeftShiftMask ; 
 int /*<<< orphan*/  MapLocalStateMask ; 
 int /*<<< orphan*/  MapNumLockMask ; 
 void* True ; 
 int /*<<< orphan*/  add_sequence (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  add_to_keymap (TYPE_1__*,char*,void*,scalar_t__,char*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ str_startswith (char*,char*) ; 
 char* strchr (char*,char) ; 
 unsigned int strlen (char*) ; 
 unsigned int strspn (char*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 void* strtol (char*,char**,int) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int) ; 
 char toupper (int) ; 
 int /*<<< orphan*/ * xkeymap_open (char*) ; 

__attribute__((used)) static BOOL
xkeymap_read(RDPCLIENT * This, char *mapname)
{
	FILE *fp;
	char line[KEYMAP_MAX_LINE_LENGTH];
	unsigned int line_num = 0;
	unsigned int line_length = 0;
	char *keyname, *p;
	char *line_rest;
	uint8 scancode;
	uint16 modifiers;

	fp = xkeymap_open(mapname);
	if (fp == NULL)
	{
		error("Failed to open keymap %s\n", mapname);
		return False;
	}

	/* FIXME: More tolerant on white space */
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		line_num++;

		/* Replace the \n with \0 */
		p = strchr(line, '\n');
		if (p != NULL)
			*p = 0;

		line_length = strlen(line);

		/* Completely empty line */
		if (strspn(line, " \t\n\r\f\v") == line_length)
		{
			continue;
		}

		/* Include */
		if (str_startswith(line, "include "))
		{
			if (!xkeymap_read(This, line + sizeof("include ") - 1))
				return False;
			continue;
		}

		/* map */
		if (str_startswith(line, "map "))
		{
			This->keylayout = strtoul(line + sizeof("map ") - 1, NULL, 16);
			DEBUG_KBD(("Keylayout 0x%x\n", This->keylayout));
			continue;
		}

		/* compose */
		if (str_startswith(line, "enable_compose"))
		{
			DEBUG_KBD(("Enabling compose handling\n"));
			This->enable_compose = True;
			continue;
		}

		/* sequence */
		if (str_startswith(line, "sequence"))
		{
			add_sequence(This, line + sizeof("sequence") - 1, mapname);
			continue;
		}

		/* keyboard_type */
		if (str_startswith(line, "keyboard_type "))
		{
			This->keyboard_type = strtol(line + sizeof("keyboard_type ") - 1, NULL, 16);
			DEBUG_KBD(("keyboard_type 0x%x\n", This->keyboard_type));
			continue;
		}

		/* keyboard_subtype */
		if (str_startswith(line, "keyboard_subtype "))
		{
			This->keyboard_subtype =
				strtol(line + sizeof("keyboard_subtype ") - 1, NULL, 16);
			DEBUG_KBD(("keyboard_subtype 0x%x\n", This->keyboard_subtype));
			continue;
		}

		/* keyboard_functionkeys */
		if (str_startswith(line, "keyboard_functionkeys "))
		{
			This->keyboard_functionkeys =
				strtol(line + sizeof("keyboard_functionkeys ") - 1, NULL, 16);
			DEBUG_KBD(("keyboard_functionkeys 0x%x\n", This->keyboard_functionkeys));
			continue;
		}

		/* Comment */
		if (line[0] == '#')
		{
			continue;
		}

		/* Normal line */
		keyname = line;
		p = strchr(line, ' ');
		if (p == NULL)
		{
			error("Bad line %d in keymap %s\n", line_num, mapname);
			continue;
		}
		else
		{
			*p = 0;
		}

		/* scancode */
		p++;
		scancode = strtol(p, &line_rest, 16);

		/* flags */
		/* FIXME: Should allow case-insensitive flag names.
		   Fix by using lex+yacc... */
		modifiers = 0;
		if (strstr(line_rest, "altgr"))
		{
			MASK_ADD_BITS(modifiers, MapAltGrMask);
		}

		if (strstr(line_rest, "shift"))
		{
			MASK_ADD_BITS(modifiers, MapLeftShiftMask);
		}

		if (strstr(line_rest, "numlock"))
		{
			MASK_ADD_BITS(modifiers, MapNumLockMask);
		}

		if (strstr(line_rest, "localstate"))
		{
			MASK_ADD_BITS(modifiers, MapLocalStateMask);
		}

		if (strstr(line_rest, "inhibit"))
		{
			MASK_ADD_BITS(modifiers, MapInhibitMask);
		}

		add_to_keymap(This, keyname, scancode, modifiers, mapname);

		if (strstr(line_rest, "addupper"))
		{
			/* Automatically add uppercase key, with same modifiers
			   plus shift */
			for (p = keyname; *p; p++)
				*p = toupper((int) *p);
			MASK_ADD_BITS(modifiers, MapLeftShiftMask);
			add_to_keymap(This, keyname, scancode, modifiers, mapname);
		}
	}

	fclose(fp);
	return True;
}