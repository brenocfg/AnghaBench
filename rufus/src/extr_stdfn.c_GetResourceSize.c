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
typedef  int /*<<< orphan*/  HMODULE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetResource (int /*<<< orphan*/ ,char*,char*,char const*,scalar_t__*,int /*<<< orphan*/ ) ; 

DWORD GetResourceSize(HMODULE module, char* name, char* type, const char* desc)
{
	DWORD len = 0;
	return (GetResource(module, name, type, desc, &len, FALSE) == NULL)?0:len;
}