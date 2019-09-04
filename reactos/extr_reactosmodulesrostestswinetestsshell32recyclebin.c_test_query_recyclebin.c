#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  temp_path ;
typedef  int /*<<< orphan*/  info2 ;
typedef  int /*<<< orphan*/  info1 ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {char* pFrom; int fFlags; int /*<<< orphan*/ * lpszProgressTitle; int /*<<< orphan*/ * hNameMappings; int /*<<< orphan*/ * pTo; int /*<<< orphan*/  wFunc; int /*<<< orphan*/ * hwnd; } ;
struct TYPE_5__ {int member_0; int member_1; int member_2; int i64Size; int i64NumItems; } ;
typedef  TYPE_1__ SHQUERYRBINFO ;
typedef  TYPE_2__ SHFILEOPSTRUCTA ;
typedef  char* HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FOF_ALLOWUNDO ; 
 int FOF_FILESONLY ; 
 int FOF_NOCONFIRMATION ; 
 int FOF_SILENT ; 
 int /*<<< orphan*/  FO_DELETE ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetTempFileNameA (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MAX_PATH ; 
 char* S_OK ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pSHFileOperationA (TYPE_2__*) ; 
 char* pSHQueryRecycleBinA (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int strlen (char*) ; 
 char* wine_dbgstr_longlong (int) ; 

__attribute__((used)) static void test_query_recyclebin(void)
{
    SHQUERYRBINFO info1={sizeof(info1),0xdeadbeef,0xdeadbeef};
    SHQUERYRBINFO info2={sizeof(info2),0xdeadbeef,0xdeadbeef};
    UINT written;
    HRESULT hr;
    HANDLE file;
    SHFILEOPSTRUCTA shfo;
    CHAR temp_path[MAX_PATH-14], buf[MAX_PATH+1];
    if(!pSHQueryRecycleBinA)
    {
        skip("SHQueryRecycleBinA does not exist\n");
        return;
    }
    if(!pSHFileOperationA)
    {
        skip("SHFileOperationA does not exist\n");
        return;
    }
    ok(GetTempPathA(sizeof(temp_path), temp_path), "GetTempPath failed\n");
    ok(GetTempFileNameA(temp_path, "trash", 0, buf), "GetTempFileName failed\n");
    buf[strlen(buf) + 1] = '\0';
    hr = pSHQueryRecycleBinA(buf,&info1);
    ok(hr == S_OK, "SHQueryRecycleBinA failed with error 0x%x\n", hr);
    ok(info1.i64Size!=0xdeadbeef,"i64Size not set\n");
    ok(info1.i64NumItems!=0xdeadbeef,"i64NumItems not set\n");
    /*create and send a file to the recycle bin*/
    file = CreateFileA(buf,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
    ok(file != INVALID_HANDLE_VALUE, "Failure to open file %s\n",buf);
    WriteFile(file,buf,strlen(buf),&written,NULL);
    CloseHandle(file);
    shfo.hwnd = NULL;
    shfo.wFunc = FO_DELETE;
    shfo.pFrom = buf;
    shfo.pTo = NULL;
    shfo.fFlags = FOF_FILESONLY | FOF_NOCONFIRMATION | FOF_SILENT | FOF_ALLOWUNDO;
    shfo.hNameMappings = NULL;
    shfo.lpszProgressTitle = NULL;
    ok(!pSHFileOperationA(&shfo), "Deletion was not successful\n");
    hr = pSHQueryRecycleBinA(buf,&info2);
    ok(hr == S_OK, "SHQueryRecycleBinA failed with error 0x%x\n", hr);
    ok(info2.i64Size==info1.i64Size+written,"Expected recycle bin to have 0x%s bytes\n",wine_dbgstr_longlong(info1.i64Size+written));
    ok(info2.i64NumItems==info1.i64NumItems+1,"Expected recycle bin to have 0x%s items\n",wine_dbgstr_longlong(info1.i64NumItems+1));
}