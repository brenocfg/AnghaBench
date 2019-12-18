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
typedef  int uint8_t ;
struct smartypants_data {int dummy; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bufputc (struct buf*,int const) ; 

__attribute__((used)) static size_t
smartypants_cb__escape(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
	if (size < 2)
		return 0;

	switch (text[1]) {
	case '\\':
	case '"':
	case '\'':
	case '.':
	case '-':
	case '`':
		bufputc(ob, text[1]);
		return 1;

	default:
		bufputc(ob, '\\');
		return 0;
	}
}