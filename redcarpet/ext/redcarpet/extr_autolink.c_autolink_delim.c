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
typedef  char uint8_t ;

/* Variables and functions */
 scalar_t__ isalpha (char) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

__attribute__((used)) static size_t
autolink_delim(uint8_t *data, size_t link_end, size_t max_rewind, size_t size)
{
	uint8_t cclose, copen = 0;
	size_t i;

	for (i = 0; i < link_end; ++i)
		if (data[i] == '<') {
			link_end = i;
			break;
		}

	while (link_end > 0) {
		if (strchr("?!.,", data[link_end - 1]) != NULL)
			link_end--;

		else if (data[link_end - 1] == ';') {
			size_t new_end = link_end - 2;

			while (new_end > 0 && isalpha(data[new_end]))
				new_end--;

			if (new_end < link_end - 2 && data[new_end] == '&')
				link_end = new_end;
			else
				link_end--;
		}
		else break;
	}

	if (link_end == 0)
		return 0;

	cclose = data[link_end - 1];

	switch (cclose) {
	case '"':	copen = '"'; break;
	case '\'':	copen = '\''; break;
	case ')':	copen = '('; break;
	case ']':	copen = '['; break;
	case '}':	copen = '{'; break;
	}

	if (copen != 0) {
		size_t closing = 0;
		size_t opening = 0;
		size_t i = 0;

		/* Try to close the final punctuation sign in this same line;
		 * if we managed to close it outside of the URL, that means that it's
		 * not part of the URL. If it closes inside the URL, that means it
		 * is part of the URL.
		 *
		 * Examples:
		 *
		 *	foo http://www.pokemon.com/Pikachu_(Electric) bar
		 *		=> http://www.pokemon.com/Pikachu_(Electric)
		 *
		 *	foo (http://www.pokemon.com/Pikachu_(Electric)) bar
		 *		=> http://www.pokemon.com/Pikachu_(Electric)
		 *
		 *	foo http://www.pokemon.com/Pikachu_(Electric)) bar
		 *		=> http://www.pokemon.com/Pikachu_(Electric))
		 *
		 *	(foo http://www.pokemon.com/Pikachu_(Electric)) bar
		 *		=> foo http://www.pokemon.com/Pikachu_(Electric)
		 */

		while (i < link_end) {
			if (data[i] == copen)
				opening++;
			else if (data[i] == cclose)
				closing++;

			i++;
		}

		if (closing != opening)
			link_end--;
	}

	return link_end;
}