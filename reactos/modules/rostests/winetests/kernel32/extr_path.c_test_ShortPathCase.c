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
typedef  int /*<<< orphan*/  shortbuf ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetShortPathNameA (char*,char*,int) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*,char const*) ; 
 size_t strlen (char const*) ; 
 char tolower (char) ; 

__attribute__((used)) static void test_ShortPathCase(const char *tmpdir, const char *dirname,
                               const char *filename)
{
    char buf[MAX_PATH], shortbuf[MAX_PATH];
    HANDLE hndl;
    size_t i;

    assert(strlen(tmpdir) + strlen(dirname) + strlen(filename) + 2 < sizeof(buf));
    sprintf(buf,"%s\\%s\\%s",tmpdir,dirname,filename);
    GetShortPathNameA(buf,shortbuf,sizeof(shortbuf));
    hndl = CreateFileA(shortbuf,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    ok(hndl!=INVALID_HANDLE_VALUE,"CreateFileA failed (%d)\n",GetLastError());
    CloseHandle(hndl);
    /* Now for the real test */
    for(i=0;i<strlen(shortbuf);i++)
        if (i % 2)
            shortbuf[i] = tolower(shortbuf[i]);
    hndl = CreateFileA(shortbuf,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    ok(hndl!=INVALID_HANDLE_VALUE,"CreateFileA failed (%d)\n",GetLastError());
    CloseHandle(hndl);
}