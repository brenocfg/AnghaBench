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
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int ERROR_CUSTOM_MESSAGE ; 
 int SUCCESS ; 
 char* status_custom_message ; 
 char const** status_messages ; 
 int status_success_message ; 

const char *
get_status_message(enum status_code code)
{
	if (code == SUCCESS) {
		const char *message = status_success_message ? status_custom_message : "";

		status_success_message = false;
		return message;
	}
	if (code == ERROR_CUSTOM_MESSAGE)
		return status_custom_message;
	return status_messages[code];
}