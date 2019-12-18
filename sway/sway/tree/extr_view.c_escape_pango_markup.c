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

/* Variables and functions */
 char* calloc (size_t,int) ; 
 size_t escape_markup_text (char const*,char*) ; 

__attribute__((used)) static char *escape_pango_markup(const char *buffer) {
	size_t length = escape_markup_text(buffer, NULL);
	char *escaped_title = calloc(length + 1, sizeof(char));
	escape_markup_text(buffer, escaped_title);
	return escaped_title;
}