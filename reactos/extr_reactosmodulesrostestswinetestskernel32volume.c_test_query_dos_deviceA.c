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
typedef  int /*<<< orphan*/  buffer2 ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int QueryDosDeviceA (char*,char*,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 char toupper (char) ; 

__attribute__((used)) static void test_query_dos_deviceA(void)
{
    char drivestr[] = "a:";
    char *p, *buffer, buffer2[2000];
    DWORD ret, ret2, buflen=32768;
    BOOL found = FALSE;

    /* callers must guess the buffer size */
    SetLastError(0xdeadbeef);
    ret = QueryDosDeviceA( NULL, NULL, 0 );
    ok(!ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "QueryDosDeviceA(no buffer): returned %u, le=%u\n", ret, GetLastError());

    buffer = HeapAlloc( GetProcessHeap(), 0, buflen );
    SetLastError(0xdeadbeef);
    ret = QueryDosDeviceA( NULL, buffer, buflen );
    ok((ret && GetLastError() != ERROR_INSUFFICIENT_BUFFER),
        "QueryDosDeviceA failed to return list, last error %u\n", GetLastError());

    if (ret && GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        p = buffer;
        for (;;) {
            if (!strlen(p)) break;
            ret2 = QueryDosDeviceA( p, buffer2, sizeof(buffer2) );
            ok(ret2, "QueryDosDeviceA failed to return current mapping for %s, last error %u\n", p, GetLastError());
            p += strlen(p) + 1;
            if (ret <= (p-buffer)) break;
        }
    }

    for (;drivestr[0] <= 'z'; drivestr[0]++) {
        /* Older W2K fails with ERROR_INSUFFICIENT_BUFFER when buflen is > 32767 */
        ret = QueryDosDeviceA( drivestr, buffer, buflen - 1);
        ok(ret || GetLastError() == ERROR_FILE_NOT_FOUND,
            "QueryDosDeviceA failed to return current mapping for %s, last error %u\n", drivestr, GetLastError());
        if(ret) {
            for (p = buffer; *p; p++) *p = toupper(*p);
            if (strstr(buffer, "HARDDISK") || strstr(buffer, "RAMDISK")) found = TRUE;
        }
    }
    ok(found, "expected at least one devicename to contain HARDDISK or RAMDISK\n");
    HeapFree( GetProcessHeap(), 0, buffer );
}