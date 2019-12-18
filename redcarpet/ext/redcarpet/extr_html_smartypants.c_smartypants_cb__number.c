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
struct smartypants_data {int dummy; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFPUTSL (struct buf*,char*) ; 
 int /*<<< orphan*/  bufputc (struct buf*,char const) ; 
 scalar_t__ fraction_boundary (char const) ; 
 char tolower (char const) ; 

__attribute__((used)) static size_t
smartypants_cb__number(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
	if (fraction_boundary(previous_char) && size >= 3) {
		if (text[0] == '1' && text[1] == '/' && text[2] == '2') {
			if (size == 3 || fraction_boundary(text[3])) {
				BUFPUTSL(ob, "&frac12;");
				return 2;
			}
		}

		if (text[0] == '1' && text[1] == '/' && text[2] == '4') {
			if (size == 3 || fraction_boundary(text[3]) ||
				(size >= 5 && tolower(text[3]) == 't' && tolower(text[4]) == 'h')) {
				BUFPUTSL(ob, "&frac14;");
				return 2;
			}
		}

		if (text[0] == '3' && text[1] == '/' && text[2] == '4') {
			if (size == 3 || fraction_boundary(text[3]) ||
				(size >= 6 && tolower(text[3]) == 't' && tolower(text[4]) == 'h' && tolower(text[5]) == 's')) {
				BUFPUTSL(ob, "&frac34;");
				return 2;
			}
		}
	}

	bufputc(ob, text[0]);
	return 0;
}