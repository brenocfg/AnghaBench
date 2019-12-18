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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int u_char ;
struct utf8_data {int have; int size; int width; int* data; } ;
typedef  enum utf8_state { ____Placeholder_utf8_state } utf8_state ;

/* Variables and functions */
 scalar_t__ UTF8_DONE ; 
 int UTF8_ERROR ; 
 int UTF8_MORE ; 
 int /*<<< orphan*/  fatalx (char*) ; 
 scalar_t__ utf8_combine (struct utf8_data*,int /*<<< orphan*/ *) ; 
 int utf8_width (int /*<<< orphan*/ ) ; 

enum utf8_state
utf8_append(struct utf8_data *ud, u_char ch)
{
	wchar_t	wc;
	int	width;

	if (ud->have >= ud->size)
		fatalx("UTF-8 character overflow");
	if (ud->size > sizeof ud->data)
		fatalx("UTF-8 character size too large");

	if (ud->have != 0 && (ch & 0xc0) != 0x80)
		ud->width = 0xff;

	ud->data[ud->have++] = ch;
	if (ud->have != ud->size)
		return (UTF8_MORE);

	if (ud->width == 0xff)
		return (UTF8_ERROR);

	if (utf8_combine(ud, &wc) != UTF8_DONE)
		return (UTF8_ERROR);
	if ((width = utf8_width(wc)) < 0)
		return (UTF8_ERROR);
	ud->width = width;

	return (UTF8_DONE);
}