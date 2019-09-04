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
 int INPUT_CANCEL ; 
 int INPUT_STOP ; 
 char key_to_control (struct key*) ; 
 unsigned long key_to_unicode (struct key*) ; 
 int prompt_default_handler (struct input*,struct key*) ; 

__attribute__((used)) static enum input_status
prompt_yesno_handler(struct input *input, struct key *key)
{
	unsigned long c = key_to_unicode(key);

	if (c == 'y' || c == 'Y')
		return INPUT_STOP;
	if (c == 'n' || c == 'N' || key_to_control(key) == 'C')
		return INPUT_CANCEL;
	return prompt_default_handler(input, key);
}