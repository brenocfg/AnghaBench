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
typedef  enum js_AstType { ____Placeholder_js_AstType } js_AstType ;

/* Variables and functions */
 char const** astname ; 
 int nelem (char const**) ; 

const char *jsP_aststring(enum js_AstType type)
{
	if (type < nelem(astname)-1)
		return astname[type];
	return "<unknown>";
}