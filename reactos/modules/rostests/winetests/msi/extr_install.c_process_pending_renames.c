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
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int MOVEFILE_COPY_ALLOWED ; 
 int MOVEFILE_REPLACE_EXISTING ; 
 int /*<<< orphan*/  MoveFileExA (char*,char*,int) ; 
 int /*<<< orphan*/  REG_MULTI_SZ ; 
 int /*<<< orphan*/  RegDeleteValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  RegSetValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  rename_ops ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 

__attribute__((used)) static void process_pending_renames(HKEY hkey)
{
    char *buf, *src, *dst, *buf2, *buf2ptr;
    DWORD size;
    LONG ret;
    BOOL found = FALSE;

    ret = RegQueryValueExA(hkey, rename_ops, NULL, NULL, NULL, &size);
    ok(!ret, "RegQueryValueExA failed %d\n", ret);

    buf = HeapAlloc(GetProcessHeap(), 0, size + 1);
    buf2ptr = buf2 = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size + 1);

    ret = RegQueryValueExA(hkey, rename_ops, NULL, NULL, (LPBYTE)buf, &size);
    buf[size] = 0;
    ok(!ret, "RegQueryValueExA failed %d\n", ret);
    if (ret) return;

    for (src = buf; *src; src = dst + strlen(dst) + 1)
    {
        DWORD flags = MOVEFILE_COPY_ALLOWED;
        BOOL fileret;

        dst = src + strlen(src) + 1;

        if (!strstr(src, "msitest"))
        {
            lstrcpyA(buf2ptr, src);
            buf2ptr += strlen(src) + 1;
            lstrcpyA(buf2ptr, dst);
            buf2ptr += strlen(dst) + 1;
            continue;
        }

        found = TRUE;

        if (*dst == '!')
        {
            flags |= MOVEFILE_REPLACE_EXISTING;
            dst++;
        }
        if (src[0] == '\\' && src[1] == '?' && src[2] == '?' && src[3] == '\\') src += 4;
        if (*dst)
        {
            if (dst[0] == '\\' && dst[1] == '?' && dst[2] == '?' && dst[3] == '\\') dst += 4;
            fileret = MoveFileExA(src, dst, flags);
            ok(fileret, "Failed to move file %s -> %s (%u)\n", src, dst, GetLastError());
        }
        else
        {
            fileret = DeleteFileA(src);
            ok(fileret || broken(!fileret) /* win2k3 */, "Failed to delete file %s (%u)\n", src, GetLastError());
        }
    }

    ok(found, "Expected a 'msitest' entry\n");

    if (*buf2)
        RegSetValueExA(hkey, rename_ops, 0, REG_MULTI_SZ, (LPBYTE)buf2, buf2ptr + 1 - buf2);
    else
        RegDeleteValueA(hkey, rename_ops);

    HeapFree(GetProcessHeap(), 0, buf);
    HeapFree(GetProcessHeap(), 0, buf2);
}