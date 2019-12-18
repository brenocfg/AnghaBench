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
typedef  int /*<<< orphan*/  version_str ;

/* Variables and functions */
 char* PACKAGE_VERSION ; 
 unsigned int atoi (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  wpp_add_define (char*,char*) ; 

__attribute__((used)) static void add_widl_version_define(void)
{
    unsigned int version;
    const char *p = PACKAGE_VERSION;

    /* major */
    version = atoi(p) * 0x10000;
    p = strchr(p, '.');

    /* minor */
    if (p)
    {
        version += atoi(p + 1) * 0x100;
        p = strchr(p + 1, '.');
    }

    /* build */
    if (p)
        version += atoi(p + 1);

    if (version != 0)
    {
        char version_str[11];
        snprintf(version_str, sizeof(version_str), "0x%x", version);
        wpp_add_define("__WIDL__", version_str);
    }
    else
        wpp_add_define("__WIDL__", NULL);
}