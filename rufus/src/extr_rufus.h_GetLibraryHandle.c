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
typedef  int /*<<< orphan*/ * HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/ * GetModuleHandleA (char*) ; 
 int /*<<< orphan*/ * LoadLibraryA (char*) ; 
 scalar_t__ MAX_LIBRARY_HANDLES ; 
 int /*<<< orphan*/ ** OpenedLibrariesHandle ; 
 scalar_t__ OpenedLibrariesHandleSize ; 
 int /*<<< orphan*/  uprintf (char*) ; 

__attribute__((used)) static __inline HMODULE GetLibraryHandle(char* szLibraryName) {
	HMODULE h = NULL;
	if ((h = GetModuleHandleA(szLibraryName)) == NULL) {
		if (OpenedLibrariesHandleSize >= MAX_LIBRARY_HANDLES) {
			uprintf("Error: MAX_LIBRARY_HANDLES is too small\n");
		} else {
			h = LoadLibraryA(szLibraryName);
			if (h != NULL)
				OpenedLibrariesHandle[OpenedLibrariesHandleSize++] = h;
		}
	}
	return h;
}