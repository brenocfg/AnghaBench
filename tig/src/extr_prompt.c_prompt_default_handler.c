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
struct key {int dummy; } ;
struct input {int /*<<< orphan*/ * buf; int /*<<< orphan*/  allow_empty; } ;
typedef  enum input_status { ____Placeholder_input_status } input_status ;

/* Variables and functions */
 int INPUT_CANCEL ; 
 int INPUT_DELETE ; 
 int INPUT_SKIP ; 
 int INPUT_STOP ; 
#define  KEY_BACKSPACE 131 
#define  KEY_ENTER 130 
#define  KEY_ESC 129 
#define  KEY_RETURN 128 
 int key_to_value (struct key*) ; 

enum input_status
prompt_default_handler(struct input *input, struct key *key)
{
	switch (key_to_value(key)) {
	case KEY_RETURN:
	case KEY_ENTER:
	case '\n':
		return *input->buf || input->allow_empty ? INPUT_STOP : INPUT_CANCEL;

	case KEY_BACKSPACE:
		return *input->buf ? INPUT_DELETE : INPUT_CANCEL;

	case KEY_ESC:
		return INPUT_CANCEL;

	default:
		return INPUT_SKIP;
	}
}