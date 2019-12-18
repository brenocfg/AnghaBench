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
struct encoding {int dummy; } ;

/* Variables and functions */
 scalar_t__ SUCCESS ; 
 scalar_t__* encoding_arg ; 
 scalar_t__ parse_encoding (struct encoding**,char const*,int) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static void
set_encoding(struct encoding **encoding_ref, const char *arg, bool priority)
{
	if (!strcasecmp(arg, "utf-8") || !strcasecmp(arg, "utf8"))
		return;
	if (parse_encoding(encoding_ref, arg, priority) == SUCCESS)
		encoding_arg[0] = 0;
}