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
struct input {int dummy; } ;
typedef  enum input_status { ____Placeholder_input_status } input_status ;

/* Variables and functions */
 int INPUT_OK ; 
 int INPUT_STOP ; 
#define  KEY_ENTER 129 
#define  KEY_RETURN 128 
 int key_to_value (struct key*) ; 

__attribute__((used)) static enum input_status
prompt_script_handler(struct input *input, struct key *key)
{
	switch (key_to_value(key)) {
	case KEY_RETURN:
	case KEY_ENTER:
	case '\n':
		return INPUT_STOP;

	default:
		return INPUT_OK;
	}
}