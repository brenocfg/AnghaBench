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
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  delete_test_class (char*) ; 
 int /*<<< orphan*/  myRegDeleteTreeA (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static void delete_test_association(const char* extension)
{
    char classname[MAX_PATH];

    sprintf(classname, "shlexec%s", extension);
    delete_test_class(classname);
    myRegDeleteTreeA(HKEY_CLASSES_ROOT, extension);
}