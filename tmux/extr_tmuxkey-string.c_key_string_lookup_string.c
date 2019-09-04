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
typedef  int wchar_t ;
typedef  int u_int ;
typedef  int u_char ;
struct utf8_data {int size; } ;
typedef  int key_code ;
typedef  enum utf8_state { ____Placeholder_utf8_state } utf8_state ;

/* Variables and functions */
 int KEYC_ANY ; 
 int KEYC_BASE ; 
 int KEYC_BSPACE ; 
 int KEYC_CTRL ; 
 int KEYC_NONE ; 
 int KEYC_UNKNOWN ; 
 int UTF8_DONE ; 
 int UTF8_MORE ; 
 int key_string_get_modifiers (char const**) ; 
 int key_string_search_table (char const*) ; 
 int sscanf (char const*,char*,int*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strchr (char const*,int) ; 
 int strlen (char const*) ; 
 int utf8_append (struct utf8_data*,int) ; 
 int utf8_combine (struct utf8_data*,int*) ; 
 int utf8_open (struct utf8_data*,int) ; 

key_code
key_string_lookup_string(const char *string)
{
	static const char	*other = "!#()+,-.0123456789:;<=>?'\r\t";
	key_code		 key;
	u_int			 u;
	key_code		 modifiers;
	struct utf8_data	 ud;
	u_int			 i;
	enum utf8_state		 more;
	wchar_t			 wc;

	/* Is this no key or any key? */
	if (strcasecmp(string, "None") == 0)
		return (KEYC_NONE);
	if (strcasecmp(string, "Any") == 0)
		return (KEYC_ANY);

	/* Is this a hexadecimal value? */
	if (string[0] == '0' && string[1] == 'x') {
	        if (sscanf(string + 2, "%x", &u) != 1)
	                return (KEYC_UNKNOWN);
		if (u > 0x1fffff)
	                return (KEYC_UNKNOWN);
	        return (u);
	}

	/* Check for modifiers. */
	modifiers = 0;
	if (string[0] == '^' && string[1] != '\0') {
		modifiers |= KEYC_CTRL;
		string++;
	}
	modifiers |= key_string_get_modifiers(&string);
	if (string == NULL || string[0] == '\0')
		return (KEYC_UNKNOWN);

	/* Is this a standard ASCII key? */
	if (string[1] == '\0' && (u_char)string[0] <= 127) {
		key = (u_char)string[0];
		if (key < 32 || key == 127)
			return (KEYC_UNKNOWN);
	} else {
		/* Try as a UTF-8 key. */
		if ((more = utf8_open(&ud, (u_char)*string)) == UTF8_MORE) {
			if (strlen(string) != ud.size)
				return (KEYC_UNKNOWN);
			for (i = 1; i < ud.size; i++)
				more = utf8_append(&ud, (u_char)string[i]);
			if (more != UTF8_DONE)
				return (KEYC_UNKNOWN);
			if (utf8_combine(&ud, &wc) != UTF8_DONE)
				return (KEYC_UNKNOWN);
			return (wc | modifiers);
		}

		/* Otherwise look the key up in the table. */
		key = key_string_search_table(string);
		if (key == KEYC_UNKNOWN)
			return (KEYC_UNKNOWN);
	}

	/* Convert the standard control keys. */
	if (key < KEYC_BASE && (modifiers & KEYC_CTRL) && !strchr(other, key)) {
		if (key >= 97 && key <= 122)
			key -= 96;
		else if (key >= 64 && key <= 95)
			key -= 64;
		else if (key == 32)
			key = 0;
		else if (key == 63)
			key = KEYC_BSPACE;
		else
			return (KEYC_UNKNOWN);
		modifiers &= ~KEYC_CTRL;
	}

	return (key | modifiers);
}