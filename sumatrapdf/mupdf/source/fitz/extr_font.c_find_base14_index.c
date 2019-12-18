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

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int
find_base14_index(const char *name)
{
	if (!strcmp(name, "Courier")) return 0;
	if (!strcmp(name, "Courier-Oblique")) return 1;
	if (!strcmp(name, "Courier-Bold")) return 2;
	if (!strcmp(name, "Courier-BoldOblique")) return 3;
	if (!strcmp(name, "Helvetica")) return 4;
	if (!strcmp(name, "Helvetica-Oblique")) return 5;
	if (!strcmp(name, "Helvetica-Bold")) return 6;
	if (!strcmp(name, "Helvetica-BoldOblique")) return 7;
	if (!strcmp(name, "Times-Roman")) return 8;
	if (!strcmp(name, "Times-Italic")) return 9;
	if (!strcmp(name, "Times-Bold")) return 10;
	if (!strcmp(name, "Times-BoldItalic")) return 11;
	if (!strcmp(name, "Symbol")) return 12;
	if (!strcmp(name, "ZapfDingbats")) return 13;
	return -1;
}