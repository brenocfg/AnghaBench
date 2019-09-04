#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_2__ {int mono_abi_version; char const* mono_libdir; char* mono_path; char* mscorlib_path; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetFileAttributesW (char*) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int NUM_ABI_VERSIONS ; 
 int NUM_RUNTIMES ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_mono_path (char*,int) ; 
 int /*<<< orphan*/  runtime_list_cs ; 
 TYPE_1__* runtimes ; 
 int runtimes_initialized ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 
 int /*<<< orphan*/  strcpyW (char*,char*) ; 

__attribute__((used)) static void find_runtimes(void)
{
    int abi_version, i;
    static const WCHAR libmono[] = {'\\','l','i','b','\\','m','o','n','o','\\',0};
    static const WCHAR mscorlib[] = {'\\','m','s','c','o','r','l','i','b','.','d','l','l',0};
    WCHAR mono_path[MAX_PATH], lib_path[MAX_PATH];
    BOOL any_runtimes_found = FALSE;

    if (runtimes_initialized) return;

    EnterCriticalSection(&runtime_list_cs);

    if (runtimes_initialized) goto end;

    for (abi_version=NUM_ABI_VERSIONS; abi_version>0; abi_version--)
    {
        if (!get_mono_path(mono_path, abi_version))
            continue;

        for (i=0; i<NUM_RUNTIMES; i++)
        {
            if (runtimes[i].mono_abi_version == 0)
            {
                strcpyW(lib_path, mono_path);
                strcatW(lib_path, libmono);
                strcatW(lib_path, runtimes[i].mono_libdir);
                strcatW(lib_path, mscorlib);

                if (GetFileAttributesW(lib_path) != INVALID_FILE_ATTRIBUTES)
                {
                    runtimes[i].mono_abi_version = abi_version;

                    strcpyW(runtimes[i].mono_path, mono_path);
                    strcpyW(runtimes[i].mscorlib_path, lib_path);

                    any_runtimes_found = TRUE;
                }
            }
        }
    }

    if (!any_runtimes_found)
    {
        /* Report all runtimes are available if Mono isn't installed.
         * FIXME: Remove this when Mono is properly packaged. */
        for (i=0; i<NUM_RUNTIMES; i++)
            runtimes[i].mono_abi_version = -1;
    }

    runtimes_initialized = 1;

end:
    LeaveCriticalSection(&runtime_list_cs);
}