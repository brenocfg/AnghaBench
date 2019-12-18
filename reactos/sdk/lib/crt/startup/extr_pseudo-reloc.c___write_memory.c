#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  b ;
struct TYPE_3__ {scalar_t__ Protect; int /*<<< orphan*/  RegionSize; int /*<<< orphan*/  BaseAddress; } ;
typedef  TYPE_1__ MEMORY_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ PAGE_EXECUTE_READWRITE ; 
 scalar_t__ PAGE_READWRITE ; 
 int /*<<< orphan*/  VirtualProtect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  VirtualQuery (void*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  __report_error (char*,int,void*) ; 
 int /*<<< orphan*/  mark_section_writable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

__attribute__((used)) static void
__write_memory (void *addr, const void *src, size_t len)
{
  MEMORY_BASIC_INFORMATION b;
  DWORD oldprot;
  int call_unprotect = 0;

  if (!len)
    return;

#ifdef __MINGW64_VERSION_MAJOR
  mark_section_writable ((LPVOID) addr);
#endif

  if (!VirtualQuery (addr, &b, sizeof(b)))
    {
      __report_error ("  VirtualQuery failed for %d bytes at address %p",
		      (int) sizeof(b), addr);
    }

  /* Temporarily allow write access to read-only protected memory.  */
  if (b.Protect != PAGE_EXECUTE_READWRITE && b.Protect != PAGE_READWRITE)
    {
      call_unprotect = 1;
      VirtualProtect (b.BaseAddress, b.RegionSize, PAGE_EXECUTE_READWRITE,
		      &oldprot);
    }

  /* write the data. */
  memcpy (addr, src, len);
  /* Restore original protection. */
  if (call_unprotect && b.Protect != PAGE_EXECUTE_READWRITE && b.Protect != PAGE_READWRITE)
    VirtualProtect (b.BaseAddress, b.RegionSize, oldprot, &oldprot);
}