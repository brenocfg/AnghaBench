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
typedef  int /*<<< orphan*/  td ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_3__ {void* BaseAddress; int const Protect; void* AllocationBase; int const AllocationProtect; int /*<<< orphan*/  Type; int /*<<< orphan*/  State; int /*<<< orphan*/  RegionSize; } ;
typedef  TYPE_1__ MEMORY_BASIC_INFORMATION ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/  MEM_COMMIT ; 
#define  PAGE_EXECUTE 135 
#define  PAGE_EXECUTE_READ 134 
#define  PAGE_EXECUTE_READWRITE 133 
#define  PAGE_EXECUTE_WRITECOPY 132 
#define  PAGE_NOACCESS 131 
#define  PAGE_READONLY 130 
#define  PAGE_READWRITE 129 
#define  PAGE_WRITECOPY 128 
 int /*<<< orphan*/  SEC_IMAGE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int VirtualProtect (void*,int /*<<< orphan*/ ,int const,int*) ; 
 int VirtualQuery (void*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  page_size ; 

__attribute__((used)) static void test_VirtualProtect(void *base, void *section)
{
    static const struct test_data
    {
        DWORD prot_set, prot_get;
    } td[] =
    {
        { 0, 0 }, /* 0x00 */
        { PAGE_NOACCESS, PAGE_NOACCESS }, /* 0x01 */
        { PAGE_READONLY, PAGE_READONLY }, /* 0x02 */
        { PAGE_READONLY | PAGE_NOACCESS, 0 }, /* 0x03 */
        { PAGE_READWRITE, PAGE_WRITECOPY }, /* 0x04 */
        { PAGE_READWRITE | PAGE_NOACCESS, 0 }, /* 0x05 */
        { PAGE_READWRITE | PAGE_READONLY, 0 }, /* 0x06 */
        { PAGE_READWRITE | PAGE_READONLY | PAGE_NOACCESS, 0 }, /* 0x07 */
        { PAGE_WRITECOPY, PAGE_WRITECOPY }, /* 0x08 */
        { PAGE_WRITECOPY | PAGE_NOACCESS, 0 }, /* 0x09 */
        { PAGE_WRITECOPY | PAGE_READONLY, 0 }, /* 0x0a */
        { PAGE_WRITECOPY | PAGE_NOACCESS | PAGE_READONLY, 0 }, /* 0x0b */
        { PAGE_WRITECOPY | PAGE_READWRITE, 0 }, /* 0x0c */
        { PAGE_WRITECOPY | PAGE_READWRITE | PAGE_NOACCESS, 0 }, /* 0x0d */
        { PAGE_WRITECOPY | PAGE_READWRITE | PAGE_READONLY, 0 }, /* 0x0e */
        { PAGE_WRITECOPY | PAGE_READWRITE | PAGE_READONLY | PAGE_NOACCESS, 0 }, /* 0x0f */

        { PAGE_EXECUTE, PAGE_EXECUTE }, /* 0x10 */
        { PAGE_EXECUTE_READ, PAGE_EXECUTE_READ }, /* 0x20 */
        { PAGE_EXECUTE_READ | PAGE_EXECUTE, 0 }, /* 0x30 */
        { PAGE_EXECUTE_READWRITE, PAGE_EXECUTE_WRITECOPY }, /* 0x40 */
        { PAGE_EXECUTE_READWRITE | PAGE_EXECUTE, 0 }, /* 0x50 */
        { PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_READ, 0 }, /* 0x60 */
        { PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_READ | PAGE_EXECUTE, 0 }, /* 0x70 */
        { PAGE_EXECUTE_WRITECOPY, PAGE_EXECUTE_WRITECOPY }, /* 0x80 */
        { PAGE_EXECUTE_WRITECOPY | PAGE_EXECUTE, 0 }, /* 0x90 */
        { PAGE_EXECUTE_WRITECOPY | PAGE_EXECUTE_READ, 0 }, /* 0xa0 */
        { PAGE_EXECUTE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE, 0 }, /* 0xb0 */
        { PAGE_EXECUTE_WRITECOPY | PAGE_EXECUTE_READWRITE, 0 }, /* 0xc0 */
        { PAGE_EXECUTE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE, 0 }, /* 0xd0 */
        { PAGE_EXECUTE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_READ, 0 }, /* 0xe0 */
        { PAGE_EXECUTE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_READ | PAGE_EXECUTE, 0 } /* 0xf0 */
    };
    DWORD ret, orig_prot, old_prot, rw_prot, exec_prot, i, j;
    MEMORY_BASIC_INFORMATION info;

    SetLastError(0xdeadbeef);
    ret = VirtualProtect(section, page_size, PAGE_NOACCESS, &old_prot);
    ok(ret, "VirtualProtect error %d\n", GetLastError());

    orig_prot = old_prot;

    for (i = 0; i < sizeof(td)/sizeof(td[0]); i++)
    {
        SetLastError(0xdeadbeef);
        ret = VirtualQuery(section, &info, sizeof(info));
        ok(ret, "VirtualQuery failed %d\n", GetLastError());
        ok(info.BaseAddress == section, "%d: got %p != expected %p\n", i, info.BaseAddress, section);
        ok(info.RegionSize == page_size, "%d: got %#lx != expected %#x\n", i, info.RegionSize, page_size);
        ok(info.Protect == PAGE_NOACCESS, "%d: got %#x != expected PAGE_NOACCESS\n", i, info.Protect);
        ok(info.AllocationBase == base, "%d: %p != %p\n", i, info.AllocationBase, base);
        ok(info.AllocationProtect == PAGE_EXECUTE_WRITECOPY, "%d: %#x != PAGE_EXECUTE_WRITECOPY\n", i, info.AllocationProtect);
        ok(info.State == MEM_COMMIT, "%d: %#x != MEM_COMMIT\n", i, info.State);
        ok(info.Type == SEC_IMAGE, "%d: %#x != SEC_IMAGE\n", i, info.Type);

        old_prot = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        ret = VirtualProtect(section, page_size, td[i].prot_set, &old_prot);
        if (td[i].prot_get)
        {
            ok(ret, "%d: VirtualProtect error %d, requested prot %#x\n", i, GetLastError(), td[i].prot_set);
            ok(old_prot == PAGE_NOACCESS, "%d: got %#x != expected PAGE_NOACCESS\n", i, old_prot);

            SetLastError(0xdeadbeef);
            ret = VirtualQuery(section, &info, sizeof(info));
            ok(ret, "VirtualQuery failed %d\n", GetLastError());
            ok(info.BaseAddress == section, "%d: got %p != expected %p\n", i, info.BaseAddress, section);
            ok(info.RegionSize == page_size, "%d: got %#lx != expected %#x\n", i, info.RegionSize, page_size);
            ok(info.Protect == td[i].prot_get, "%d: got %#x != expected %#x\n", i, info.Protect, td[i].prot_get);
            ok(info.AllocationBase == base, "%d: %p != %p\n", i, info.AllocationBase, base);
            ok(info.AllocationProtect == PAGE_EXECUTE_WRITECOPY, "%d: %#x != PAGE_EXECUTE_WRITECOPY\n", i, info.AllocationProtect);
            ok(info.State == MEM_COMMIT, "%d: %#x != MEM_COMMIT\n", i, info.State);
            ok(info.Type == SEC_IMAGE, "%d: %#x != SEC_IMAGE\n", i, info.Type);
        }
        else
        {
            ok(!ret, "%d: VirtualProtect should fail\n", i);
            ok(GetLastError() == ERROR_INVALID_PARAMETER, "%d: expected ERROR_INVALID_PARAMETER, got %d\n", i, GetLastError());
        }

        old_prot = 0xdeadbeef;
        SetLastError(0xdeadbeef);
        ret = VirtualProtect(section, page_size, PAGE_NOACCESS, &old_prot);
        ok(ret, "%d: VirtualProtect error %d\n", i, GetLastError());
        if (td[i].prot_get)
            ok(old_prot == td[i].prot_get, "%d: got %#x != expected %#x\n", i, old_prot, td[i].prot_get);
        else
            ok(old_prot == PAGE_NOACCESS, "%d: got %#x != expected PAGE_NOACCESS\n", i, old_prot);
    }

    exec_prot = 0;

    for (i = 0; i <= 4; i++)
    {
        rw_prot = 0;

        for (j = 0; j <= 4; j++)
        {
            DWORD prot = exec_prot | rw_prot;

            SetLastError(0xdeadbeef);
            ret = VirtualProtect(section, page_size, prot, &old_prot);
            if ((rw_prot && exec_prot) || (!rw_prot && !exec_prot))
            {
                ok(!ret, "VirtualProtect(%02x) should fail\n", prot);
                ok(GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
            }
            else
                ok(ret, "VirtualProtect(%02x) error %d\n", prot, GetLastError());

            rw_prot = 1 << j;
        }

        exec_prot = 1 << (i + 4);
    }

    SetLastError(0xdeadbeef);
    ret = VirtualProtect(section, page_size, orig_prot, &old_prot);
    ok(ret, "VirtualProtect error %d\n", GetLastError());
}