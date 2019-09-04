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
typedef  int /*<<< orphan*/  prot_map ;
typedef  int /*<<< orphan*/  map ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateFileMappingA (scalar_t__,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ CreateFileMappingW (scalar_t__,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int DuplicateHandle (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
#define  GENERIC_ALL 149 
#define  GENERIC_EXECUTE 148 
#define  GENERIC_READ 147 
#define  GENERIC_WRITE 146 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetTempFileNameA (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 scalar_t__ OpenFileMappingA (int,int /*<<< orphan*/ ,char*) ; 
#define  PAGE_EXECUTE 145 
#define  PAGE_EXECUTE_READ 144 
#define  PAGE_EXECUTE_READWRITE 143 
#define  PAGE_EXECUTE_WRITECOPY 142 
#define  PAGE_NOACCESS 141 
#define  PAGE_READONLY 140 
#define  PAGE_READWRITE 139 
#define  PAGE_WRITECOPY 138 
#define  SECTION_ALL_ACCESS 137 
#define  SECTION_MAP_EXECUTE 136 
#define  SECTION_MAP_READ 135 
#define  SECTION_MAP_WRITE 134 
#define  SECTION_QUERY 133 
#define  STANDARD_RIGHTS_EXECUTE 132 
#define  STANDARD_RIGHTS_READ 131 
#define  STANDARD_RIGHTS_REQUIRED 130 
#define  STANDARD_RIGHTS_WRITE 129 
 int /*<<< orphan*/  SetEndOfFile (scalar_t__) ; 
 int /*<<< orphan*/  SetFilePointer (scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
#define  TRUE 128 
 int get_obj_access (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,int const,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_filemap_security(void)
{
    char temp_path[MAX_PATH];
    char file_name[MAX_PATH];
    DWORD ret, i, access;
    HANDLE file, mapping, dup, created_mapping;
    static const struct
    {
        int generic, mapped;
        BOOL open_only;
    } map[] =
    {
        { 0, 0 },
        { GENERIC_READ, STANDARD_RIGHTS_READ | SECTION_QUERY | SECTION_MAP_READ },
        { GENERIC_WRITE, STANDARD_RIGHTS_WRITE | SECTION_MAP_WRITE },
        { GENERIC_EXECUTE, STANDARD_RIGHTS_EXECUTE | SECTION_MAP_EXECUTE },
        { GENERIC_ALL, STANDARD_RIGHTS_REQUIRED | SECTION_ALL_ACCESS },
        { SECTION_MAP_READ | SECTION_MAP_WRITE, SECTION_MAP_READ | SECTION_MAP_WRITE },
        { SECTION_MAP_WRITE, SECTION_MAP_WRITE },
        { SECTION_MAP_READ | SECTION_QUERY, SECTION_MAP_READ | SECTION_QUERY },
        { SECTION_QUERY, SECTION_MAP_READ, TRUE },
        { SECTION_QUERY | SECTION_MAP_READ, SECTION_QUERY | SECTION_MAP_READ }
    };
    static const struct
    {
        int prot, mapped;
    } prot_map[] =
    {
        { 0, 0 },
        { PAGE_NOACCESS, 0 },
        { PAGE_READONLY, STANDARD_RIGHTS_REQUIRED | SECTION_QUERY | SECTION_MAP_READ },
        { PAGE_READWRITE, STANDARD_RIGHTS_REQUIRED | SECTION_QUERY | SECTION_MAP_READ | SECTION_MAP_WRITE },
        { PAGE_WRITECOPY, STANDARD_RIGHTS_REQUIRED | SECTION_QUERY | SECTION_MAP_READ },
        { PAGE_EXECUTE, 0 },
        { PAGE_EXECUTE_READ, STANDARD_RIGHTS_REQUIRED | SECTION_QUERY | SECTION_MAP_READ | SECTION_MAP_EXECUTE },
        { PAGE_EXECUTE_READWRITE, STANDARD_RIGHTS_REQUIRED | SECTION_QUERY | SECTION_MAP_READ | SECTION_MAP_WRITE | SECTION_MAP_EXECUTE },
        { PAGE_EXECUTE_WRITECOPY, STANDARD_RIGHTS_REQUIRED | SECTION_QUERY | SECTION_MAP_READ | SECTION_MAP_EXECUTE }
    };

    GetTempPathA(MAX_PATH, temp_path);
    GetTempFileNameA(temp_path, "tmp", 0, file_name);

    SetLastError(0xdeadbeef);
    file = CreateFileA(file_name, GENERIC_READ|GENERIC_WRITE|GENERIC_EXECUTE, 0, NULL, CREATE_ALWAYS, 0, 0);
    ok(file != INVALID_HANDLE_VALUE, "CreateFile error %d\n", GetLastError());
    SetFilePointer(file, 4096, NULL, FILE_BEGIN);
    SetEndOfFile(file);

    for (i = 0; i < sizeof(prot_map)/sizeof(prot_map[0]); i++)
    {
        if (map[i].open_only) continue;

        SetLastError(0xdeadbeef);
        mapping = CreateFileMappingW(file, NULL, prot_map[i].prot, 0, 4096, NULL);
        if (prot_map[i].mapped)
        {
            if (!mapping)
            {
                /* NT4 and win2k don't support EXEC on file mappings */
                if (prot_map[i].prot == PAGE_EXECUTE_READ || prot_map[i].prot == PAGE_EXECUTE_READWRITE || prot_map[i].prot == PAGE_EXECUTE_WRITECOPY)
                {
                    win_skip("CreateFileMapping doesn't support PAGE_EXECUTE protection\n");
                    continue;
                }
            }
            ok(mapping != 0, "CreateFileMapping(%04x) error %d\n", prot_map[i].prot, GetLastError());
        }
        else
        {
            ok(!mapping, "CreateFileMapping(%04x) should fail\n", prot_map[i].prot);
            ok(GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
            continue;
        }

        access = get_obj_access(mapping);
        ok(access == prot_map[i].mapped, "%d: expected %#x, got %#x\n", i, prot_map[i].mapped, access);

        CloseHandle(mapping);
    }

    SetLastError(0xdeadbeef);
    mapping = CreateFileMappingW(file, NULL, PAGE_EXECUTE_READWRITE, 0, 4096, NULL);
    if (!mapping)
    {
        /* NT4 and win2k don't support EXEC on file mappings */
        win_skip("CreateFileMapping doesn't support PAGE_EXECUTE protection\n");
        CloseHandle(file);
        DeleteFileA(file_name);
        return;
    }
    ok(mapping != 0, "CreateFileMapping error %d\n", GetLastError());

    access = get_obj_access(mapping);
    ok(access == (STANDARD_RIGHTS_REQUIRED | SECTION_QUERY | SECTION_MAP_READ | SECTION_MAP_WRITE | SECTION_MAP_EXECUTE),
       "expected STANDARD_RIGHTS_REQUIRED | SECTION_QUERY | SECTION_MAP_READ | SECTION_MAP_WRITE | SECTION_MAP_EXECUTE, got %#x\n", access);

    for (i = 0; i < sizeof(map)/sizeof(map[0]); i++)
    {
        if (map[i].open_only) continue;

        SetLastError( 0xdeadbeef );
        ret = DuplicateHandle(GetCurrentProcess(), mapping, GetCurrentProcess(), &dup,
                              map[i].generic, FALSE, 0);
        ok(ret, "DuplicateHandle error %d\n", GetLastError());

        access = get_obj_access(dup);
        ok(access == map[i].mapped, "%d: expected %#x, got %#x\n", i, map[i].mapped, access);

        CloseHandle(dup);
    }

    CloseHandle(mapping);
    CloseHandle(file);
    DeleteFileA(file_name);

    created_mapping = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 0x1000,
                                         "Wine Test Open Mapping");
    ok(created_mapping != NULL, "CreateFileMapping failed with error %u\n", GetLastError());

    for (i = 0; i < sizeof(map)/sizeof(map[0]); i++)
    {
        if (!map[i].generic) continue;

        mapping = OpenFileMappingA(map[i].generic, FALSE, "Wine Test Open Mapping");
        ok(mapping != NULL, "OpenFileMapping failed with error %d\n", GetLastError());
        access = get_obj_access(mapping);
        ok(access == map[i].mapped, "%d: unexpected access flags %#x, expected %#x\n",
           i, access, map[i].mapped);
        CloseHandle(mapping);
    }

    CloseHandle(created_mapping);
}