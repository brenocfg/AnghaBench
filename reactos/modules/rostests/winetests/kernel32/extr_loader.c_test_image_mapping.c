#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
struct TYPE_10__ {int VirtualAddress; } ;
struct TYPE_7__ {scalar_t__ HighPart; scalar_t__ LowPart; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
struct TYPE_8__ {char* BaseAddress; void* AllocationBase; int AllocationProtect; int State; int Type; int /*<<< orphan*/  Protect; int /*<<< orphan*/  RegionSize; } ;
typedef  int SIZE_T ;
typedef  int NTSTATUS ;
typedef  TYPE_2__ MEMORY_BASIC_INFORMATION ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateFileMappingW (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ERROR_INVALID_ADDRESS ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int FreeLibrary (void*) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 void* LoadLibraryA (char const*) ; 
 int MEM_COMMIT ; 
 void* MapViewOfFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int PAGE_EXECUTE_WRITECOPY ; 
 int PAGE_READONLY ; 
 int SEC_IMAGE ; 
 int STATUS_IMAGE_NOT_AT_BASE ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  UnmapViewOfFile (void*) ; 
 int VirtualQuery (char*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pNtMapViewOfSection (scalar_t__,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int*,int,int /*<<< orphan*/ ,int) ; 
 int pNtUnmapViewOfSection (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  page_size ; 
 TYPE_4__ section ; 

__attribute__((used)) static void test_image_mapping(const char *dll_name, DWORD scn_page_access, BOOL is_dll)
{
    HANDLE hfile, hmap;
    NTSTATUS status;
    LARGE_INTEGER offset;
    SIZE_T size;
    void *addr1, *addr2;
    MEMORY_BASIC_INFORMATION info;

    if (!pNtMapViewOfSection) return;

    SetLastError(0xdeadbeef);
    hfile = CreateFileA(dll_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "CreateFile error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    hmap = CreateFileMappingW(hfile, NULL, PAGE_READONLY | SEC_IMAGE, 0, 0, 0);
    ok(hmap != 0, "CreateFileMapping error %d\n", GetLastError());

    offset.u.LowPart  = 0;
    offset.u.HighPart = 0;

    addr1 = NULL;
    size = 0;
    status = pNtMapViewOfSection(hmap, GetCurrentProcess(), &addr1, 0, 0, &offset,
                                 &size, 1 /* ViewShare */, 0, PAGE_READONLY);
    ok(status == STATUS_SUCCESS, "NtMapViewOfSection error %x\n", status);
    ok(addr1 != 0, "mapped address should be valid\n");

    SetLastError(0xdeadbeef);
    size = VirtualQuery((char *)addr1 + section.VirtualAddress, &info, sizeof(info));
    ok(size == sizeof(info), "VirtualQuery error %d\n", GetLastError());
    ok(info.BaseAddress == (char *)addr1 + section.VirtualAddress, "got %p != expected %p\n", info.BaseAddress, (char *)addr1 + section.VirtualAddress);
    ok(info.RegionSize == page_size, "got %#lx != expected %#x\n", info.RegionSize, page_size);
    ok(info.Protect == scn_page_access, "got %#x != expected %#x\n", info.Protect, scn_page_access);
    ok(info.AllocationBase == addr1, "%p != %p\n", info.AllocationBase, addr1);
    ok(info.AllocationProtect == PAGE_EXECUTE_WRITECOPY, "%#x != PAGE_EXECUTE_WRITECOPY\n", info.AllocationProtect);
    ok(info.State == MEM_COMMIT, "%#x != MEM_COMMIT\n", info.State);
    ok(info.Type == SEC_IMAGE, "%#x != SEC_IMAGE\n", info.Type);

    addr2 = NULL;
    size = 0;
    status = pNtMapViewOfSection(hmap, GetCurrentProcess(), &addr2, 0, 0, &offset,
                                 &size, 1 /* ViewShare */, 0, PAGE_READONLY);
    ok(status == STATUS_IMAGE_NOT_AT_BASE, "expected STATUS_IMAGE_NOT_AT_BASE, got %x\n", status);
    ok(addr2 != 0, "mapped address should be valid\n");
    ok(addr2 != addr1, "mapped addresses should be different\n");

    SetLastError(0xdeadbeef);
    size = VirtualQuery((char *)addr2 + section.VirtualAddress, &info, sizeof(info));
    ok(size == sizeof(info), "VirtualQuery error %d\n", GetLastError());
    ok(info.BaseAddress == (char *)addr2 + section.VirtualAddress, "got %p != expected %p\n", info.BaseAddress, (char *)addr2 + section.VirtualAddress);
    ok(info.RegionSize == page_size, "got %#lx != expected %#x\n", info.RegionSize, page_size);
    ok(info.Protect == scn_page_access, "got %#x != expected %#x\n", info.Protect, scn_page_access);
    ok(info.AllocationBase == addr2, "%p != %p\n", info.AllocationBase, addr2);
    ok(info.AllocationProtect == PAGE_EXECUTE_WRITECOPY, "%#x != PAGE_EXECUTE_WRITECOPY\n", info.AllocationProtect);
    ok(info.State == MEM_COMMIT, "%#x != MEM_COMMIT\n", info.State);
    ok(info.Type == SEC_IMAGE, "%#x != SEC_IMAGE\n", info.Type);

    status = pNtUnmapViewOfSection(GetCurrentProcess(), addr2);
    ok(status == STATUS_SUCCESS, "NtUnmapViewOfSection error %x\n", status);

    addr2 = MapViewOfFile(hmap, 0, 0, 0, 0);
    ok(addr2 != 0, "mapped address should be valid\n");
    ok(addr2 != addr1, "mapped addresses should be different\n");

    SetLastError(0xdeadbeef);
    size = VirtualQuery((char *)addr2 + section.VirtualAddress, &info, sizeof(info));
    ok(size == sizeof(info), "VirtualQuery error %d\n", GetLastError());
    ok(info.BaseAddress == (char *)addr2 + section.VirtualAddress, "got %p != expected %p\n", info.BaseAddress, (char *)addr2 + section.VirtualAddress);
    ok(info.RegionSize == page_size, "got %#lx != expected %#x\n", info.RegionSize, page_size);
    ok(info.Protect == scn_page_access, "got %#x != expected %#x\n", info.Protect, scn_page_access);
    ok(info.AllocationBase == addr2, "%p != %p\n", info.AllocationBase, addr2);
    ok(info.AllocationProtect == PAGE_EXECUTE_WRITECOPY, "%#x != PAGE_EXECUTE_WRITECOPY\n", info.AllocationProtect);
    ok(info.State == MEM_COMMIT, "%#x != MEM_COMMIT\n", info.State);
    ok(info.Type == SEC_IMAGE, "%#x != SEC_IMAGE\n", info.Type);

    UnmapViewOfFile(addr2);

    SetLastError(0xdeadbeef);
    addr2 = LoadLibraryA(dll_name);
    if (is_dll)
    {
        ok(!addr2, "LoadLibrary should fail, is_dll %d\n", is_dll);
        ok(GetLastError() == ERROR_INVALID_ADDRESS, "expected ERROR_INVALID_ADDRESS, got %d\n", GetLastError());
    }
    else
    {
        BOOL ret;
        ok(addr2 != 0, "LoadLibrary error %d, is_dll %d\n", GetLastError(), is_dll);
        ok(addr2 != addr1, "mapped addresses should be different\n");

        SetLastError(0xdeadbeef);
        ret = FreeLibrary(addr2);
        ok(ret, "FreeLibrary error %d\n", GetLastError());
    }

    status = pNtUnmapViewOfSection(GetCurrentProcess(), addr1);
    ok(status == STATUS_SUCCESS, "NtUnmapViewOfSection error %x\n", status);

    CloseHandle(hmap);
    CloseHandle(hfile);
}