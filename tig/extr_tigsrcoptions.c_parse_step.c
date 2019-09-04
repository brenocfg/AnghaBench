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
 int SUCCESS ; 
 int atoi (char const*) ; 
 int error (char*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 

enum status_code
parse_step(double *opt, const char *arg)
{
	int value = atoi(arg);

	if (!value && !isdigit(*arg))
		return error("Invalid double or percentage");

	*opt = value;
	if (!strchr(arg, '%'))
		return SUCCESS;

	/* "Shift down" so 100% and 1 does not conflict. */
	*opt /= 100;
	if (*opt >= 1.0) {
		*opt = 0.99;
		return error("Percentage is larger than 100%%");
	}
	if (*opt < 0.0) {
		*opt = 1;
		return error("Percentage is less than 0%%");
	}
	return SUCCESS;
}