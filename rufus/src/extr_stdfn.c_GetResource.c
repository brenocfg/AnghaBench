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
typedef  int /*<<< orphan*/ * HRSRC ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/ * HGLOBAL ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * FindResourceA (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ LockResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SizeofResource (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprintf (char*,char const*,...) ; 

unsigned char* GetResource(HMODULE module, char* name, char* type, const char* desc, DWORD* len, BOOL duplicate)
{
	HGLOBAL res_handle;
	HRSRC res;
	unsigned char* p = NULL;

	res = FindResourceA(module, name, type);
	if (res == NULL) {
		uprintf("Could not locate resource '%s': %s\n", desc, WindowsErrorString());
		goto out;
	}
	res_handle = LoadResource(module, res);
	if (res_handle == NULL) {
		uprintf("Could not load resource '%s': %s\n", desc, WindowsErrorString());
		goto out;
	}
	*len = SizeofResource(module, res);

	if (duplicate) {
		p = (unsigned char*)malloc(*len);
		if (p == NULL) {
			uprintf("Coult not allocate resource '%s'\n", desc);
			goto out;
		}
		memcpy(p, LockResource(res_handle), *len);
	} else {
		p = (unsigned char*)LockResource(res_handle);
	}

out:
	return p;
}