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

__attribute__((used)) static size_t
smartypants_cb__period(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
	if (size >= 3 && text[1] == '.' && text[2] == '.') {
		BUFPUTSL(ob, "&hellip;");
		return 2;
	}

	if (size >= 5 && text[1] == ' ' && text[2] == '.' && text[3] == ' ' && text[4] == '.') {
		BUFPUTSL(ob, "&hellip;");
		return 4;
	}

	bufputc(ob, text[0]);
	return 0;
}