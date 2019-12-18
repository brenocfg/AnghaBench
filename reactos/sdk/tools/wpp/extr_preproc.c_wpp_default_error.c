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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  generic_msg (char const*,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpp_default_error(const char *file, int line, int col, const char *near, const char *msg, va_list ap)
{
	generic_msg(msg, "Error", near, ap);
	exit(1);
}