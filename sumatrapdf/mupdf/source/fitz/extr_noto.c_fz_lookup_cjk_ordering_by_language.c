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
 int FZ_ADOBE_CNS ; 
 int FZ_ADOBE_GB ; 
 int FZ_ADOBE_JAPAN ; 
 int FZ_ADOBE_KOREA ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int
fz_lookup_cjk_ordering_by_language(const char *name)
{
	if (!strcmp(name, "zh-Hant")) return FZ_ADOBE_CNS;
	if (!strcmp(name, "zh-TW")) return FZ_ADOBE_CNS;
	if (!strcmp(name, "zh-HK")) return FZ_ADOBE_CNS;
	if (!strcmp(name, "zh-Hans")) return FZ_ADOBE_GB;
	if (!strcmp(name, "zh-CN")) return FZ_ADOBE_GB;
	if (!strcmp(name, "ja")) return FZ_ADOBE_JAPAN;
	if (!strcmp(name, "ko")) return FZ_ADOBE_KOREA;
	return -1;
}