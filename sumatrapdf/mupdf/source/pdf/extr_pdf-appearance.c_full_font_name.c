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

__attribute__((used)) static const char *full_font_name(const char **name)
{
	if (!strcmp(*name, "Cour")) return "Courier";
	if (!strcmp(*name, "Helv")) return "Helvetica";
	if (!strcmp(*name, "TiRo")) return "Times-Roman";
	if (!strcmp(*name, "Symb")) return "Symbol";
	if (!strcmp(*name, "ZaDb")) return "ZapfDingbats";
	return *name = "Helv", "Helvetica";
}