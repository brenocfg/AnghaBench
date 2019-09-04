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
typedef  char WCHAR ;
typedef  int MSIHANDLE ;
typedef  int INT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int ERROR_INVALID_DATATYPE ; 
 int ERROR_INVALID_HANDLE ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_SUCCESS ; 
 int FALSE ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 int MSI_NULL_INTEGER ; 
 int MsiCloseHandle (int) ; 
 int MsiCreateRecord (int) ; 
 int MsiRecordClearData (int) ; 
 int MsiRecordDataSize (int,int) ; 
 int MsiRecordGetFieldCount (int) ; 
 int MsiRecordGetInteger (int,int /*<<< orphan*/ ) ; 
 int MsiRecordGetStringA (int,int /*<<< orphan*/ ,char*,int*) ; 
 int MsiRecordGetStringW (int,int /*<<< orphan*/ ,char*,int*) ; 
 int MsiRecordIsNull (int,int) ; 
 int MsiRecordReadStream (int,int,char*,int*) ; 
 int MsiRecordSetInteger (int,int,int) ; 
 int MsiRecordSetStreamA (int,int,char*) ; 
 int MsiRecordSetStringA (int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int create_temp_file (char*) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static void test_msirecord(void)
{
    DWORD r, sz;
    INT i;
    MSIHANDLE h;
    char buf[10];
    WCHAR bufW[10];
    const char str[] = "hello";
    const WCHAR strW[] = { 'h','e','l','l','o',0};
    char filename[MAX_PATH];

    /* check behaviour with an invalid record */
    r = MsiRecordGetFieldCount(0);
    ok(r==-1, "field count for invalid record not -1\n");
    SetLastError(0);
    r = MsiRecordIsNull(0, 0);
    ok(r==0, "invalid handle not considered to be non-null...\n");
    ok(GetLastError()==0, "MsiRecordIsNull set LastError\n");
    r = MsiRecordGetInteger(0,0);
    ok(r == MSI_NULL_INTEGER, "got integer from invalid record\n");
    r = MsiRecordSetInteger(0,0,0);
    ok(r == ERROR_INVALID_HANDLE, "MsiRecordSetInteger returned wrong error\n");
    r = MsiRecordSetInteger(0,-1,0);
    ok(r == ERROR_INVALID_HANDLE, "MsiRecordSetInteger returned wrong error\n");
    SetLastError(0);
    h = MsiCreateRecord(-1);
    ok(h==0, "created record with -1 elements\n");
    h = MsiCreateRecord(0x10000);
    ok(h==0, "created record with 0x10000 elements\n");
    /* doesn't set LastError */
    ok(GetLastError()==0, "MsiCreateRecord set last error\n");
    r = MsiRecordClearData(0);
    ok(r == ERROR_INVALID_HANDLE, "MsiRecordClearData returned wrong error\n");
    r = MsiRecordDataSize(0,0);
    ok(r == 0, "MsiRecordDataSize returned wrong error\n");


    /* check behaviour of a record with 0 elements */
    h = MsiCreateRecord(0);
    ok(h!=0, "couldn't create record with zero elements\n");
    r = MsiRecordGetFieldCount(h);
    ok(r==0, "field count should be zero\n");
    r = MsiRecordIsNull(h,0);
    ok(r, "new record wasn't null\n");
    r = MsiRecordIsNull(h,1);
    ok(r, "out of range record wasn't null\n");
    r = MsiRecordIsNull(h,-1);
    ok(r, "out of range record wasn't null\n");
    r = MsiRecordDataSize(h,0);
    ok(r==0, "size of null record is 0\n");
    sz = sizeof buf;
    strcpy(buf,"x");
    r = MsiRecordGetStringA(h, 0, buf, &sz);
    ok(r==ERROR_SUCCESS, "failed to get null string\n");
    ok(sz==0, "null string too long\n");
    ok(buf[0]==0, "null string not set\n");

    /* same record, but add an integer to it */
    r = MsiRecordSetInteger(h, 0, 0);
    ok(r == ERROR_SUCCESS, "Failed to set integer at 0 to 0\n");
    r = MsiRecordIsNull(h,0);
    ok(r==0, "new record is null after setting an integer\n");
    r = MsiRecordDataSize(h,0);
    ok(r==sizeof(DWORD), "size of integer record is 4\n");
    r = MsiRecordSetInteger(h, 0, 1);
    ok(r == ERROR_SUCCESS, "Failed to set integer at 0 to 1\n");
    r = MsiRecordSetInteger(h, 1, 1);
    ok(r == ERROR_INVALID_PARAMETER, "set integer at 1\n");
    r = MsiRecordSetInteger(h, -1, 0);
    ok(r == ERROR_INVALID_PARAMETER, "set integer at -1\n");
    r = MsiRecordIsNull(h,0);
    ok(r==0, "new record is null after setting an integer\n");
    r = MsiRecordGetInteger(h, 0);
    ok(r == 1, "failed to get integer\n");

    /* same record, but add a null or empty string to it */
    r = MsiRecordSetStringA(h, 0, NULL);
    ok(r == ERROR_SUCCESS, "Failed to set null string at 0\n");
    r = MsiRecordIsNull(h, 0);
    ok(r == TRUE, "null string not null field\n");
    r = MsiRecordDataSize(h, 0);
    ok(r == 0, "size of string record is strlen\n");
    buf[0] = 0;
    sz = sizeof buf;
    r = MsiRecordGetStringA(h, 0, buf, &sz);
    ok(r == ERROR_SUCCESS, "Failed to get string at 0\n");
    ok(buf[0] == 0, "MsiRecordGetStringA returned the wrong string\n");
    ok(sz == 0, "MsiRecordGetStringA returned the wrong length\n");
    bufW[0] = 0;
    sz = sizeof bufW / sizeof bufW[0];
    r = MsiRecordGetStringW(h, 0, bufW, &sz);
    ok(r == ERROR_SUCCESS, "Failed to get string at 0\n");
    ok(bufW[0] == 0, "MsiRecordGetStringW returned the wrong string\n");
    ok(sz == 0, "MsiRecordGetStringW returned the wrong length\n");
    r = MsiRecordSetStringA(h, 0, "");
    ok(r == ERROR_SUCCESS, "Failed to set empty string at 0\n");
    r = MsiRecordIsNull(h, 0);
    ok(r == TRUE, "null string not null field\n");
    r = MsiRecordDataSize(h, 0);
    ok(r == 0, "size of string record is strlen\n");
    buf[0] = 0;
    sz = sizeof buf;
    r = MsiRecordGetStringA(h, 0, buf, &sz);
    ok(r == ERROR_SUCCESS, "Failed to get string at 0\n");
    ok(buf[0] == 0, "MsiRecordGetStringA returned the wrong string\n");
    ok(sz == 0, "MsiRecordGetStringA returned the wrong length\n");
    bufW[0] = 0;
    sz = sizeof bufW / sizeof bufW[0];
    r = MsiRecordGetStringW(h, 0, bufW, &sz);
    ok(r == ERROR_SUCCESS, "Failed to get string at 0\n");
    ok(bufW[0] == 0, "MsiRecordGetStringW returned the wrong string\n");
    ok(sz == 0, "MsiRecordGetStringW returned the wrong length\n");

    /* same record, but add a null integer to it */
    r = MsiRecordSetInteger(h, 0, 1);
    ok(r == ERROR_SUCCESS, "Failed to set integer at 0\n");
    r = MsiRecordIsNull(h, 0);
    ok(r == FALSE, "expected field to be non-null\n");
    r = MsiRecordSetInteger(h, 0, MSI_NULL_INTEGER);
    ok(r == ERROR_SUCCESS, "Failed to set integer at 0\n");
    r = MsiRecordIsNull(h, 0);
    ok(r == TRUE, "expected field to be null\n");
    sz = sizeof buf;
    r = MsiRecordGetStringA(h, 0, buf, &sz);
    ok(r == ERROR_SUCCESS, "Failed to get string at 0\n");
    ok(buf[0] == 0, "MsiRecordGetStringA returned the wrong string\n");
    ok(sz == 0, "MsiRecordGetStringA returned the wrong length\n");

    /* same record, but add a string to it */
    r = MsiRecordSetStringA(h,0,str);
    ok(r == ERROR_SUCCESS, "Failed to set string at 0\n");
    r = MsiRecordGetInteger(h, 0);
    ok(r == MSI_NULL_INTEGER, "should get invalid integer\n");
    r = MsiRecordDataSize(h,0);
    ok(r==sizeof str-1, "size of string record is strlen\n");
    buf[0]=0;
    sz = sizeof buf;
    r = MsiRecordGetStringA(h,0,buf,&sz);
    ok(r == ERROR_SUCCESS, "Failed to get string at 0\n");
    ok(0==strcmp(buf,str), "MsiRecordGetStringA returned the wrong string\n");
    ok(sz == sizeof str-1, "MsiRecordGetStringA returned the wrong length\n");
    buf[0]=0;
    sz = sizeof str - 2;
    r = MsiRecordGetStringA(h,0,buf,&sz);
    ok(r == ERROR_MORE_DATA, "small buffer should yield ERROR_MORE_DATA\n");
    ok(sz == sizeof str-1, "MsiRecordGetStringA returned the wrong length\n");
    ok(0==strncmp(buf,str,sizeof str-3), "MsiRecordGetStringA returned the wrong string\n");
    ok(buf[sizeof str - 3]==0, "string wasn't nul terminated\n");

    buf[0]=0;
    sz = sizeof str;
    r = MsiRecordGetStringA(h,0,buf,&sz);
    ok(r == ERROR_SUCCESS, "wrong error\n");
    ok(sz == sizeof str-1, "MsiRecordGetStringA returned the wrong length\n");
    ok(0==strcmp(buf,str), "MsiRecordGetStringA returned the wrong string\n");


    memset(bufW, 0, sizeof bufW);
    sz = 5;
    r = MsiRecordGetStringW(h,0,bufW,&sz);
    ok(r == ERROR_MORE_DATA, "wrong error\n");
    ok(sz == 5, "MsiRecordGetStringA returned the wrong length\n");
    ok(0==memcmp(bufW,strW,8), "MsiRecordGetStringA returned the wrong string\n");

    sz = 0;
    bufW[0] = 'x';
    r = MsiRecordGetStringW(h,0,bufW,&sz);
    ok(r == ERROR_MORE_DATA, "wrong error\n");
    ok(sz == 5, "MsiRecordGetStringA returned the wrong length\n");
    ok('x'==bufW[0], "MsiRecordGetStringA returned the wrong string\n");

    memset(buf, 0, sizeof buf);
    sz = 5;
    r = MsiRecordGetStringA(h,0,buf,&sz);
    ok(r == ERROR_MORE_DATA, "wrong error\n");
    ok(sz == 5, "MsiRecordGetStringA returned the wrong length\n");
    ok(0==memcmp(buf,str,4), "MsiRecordGetStringA returned the wrong string\n");

    sz = 0;
    buf[0] = 'x';
    r = MsiRecordGetStringA(h,0,buf,&sz);
    ok(r == ERROR_MORE_DATA, "wrong error\n");
    ok(sz == 5, "MsiRecordGetStringA returned the wrong length\n");
    ok('x'==buf[0], "MsiRecordGetStringA returned the wrong string\n");

    /* same record, check we can wipe all the data */
    r = MsiRecordClearData(h);
    ok(r == ERROR_SUCCESS, "Failed to clear record\n");
    r = MsiRecordClearData(h);
    ok(r == ERROR_SUCCESS, "Failed to clear record again\n");
    r = MsiRecordIsNull(h,0);
    ok(r, "cleared record wasn't null\n");

    /* same record, try converting strings to integers */
    i = MsiRecordSetStringA(h,0,"42");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == 42, "should get invalid integer\n");
    i = MsiRecordSetStringA(h,0,"-42");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == -42, "should get invalid integer\n");
    i = MsiRecordSetStringA(h,0," 42");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == MSI_NULL_INTEGER, "should get invalid integer\n");
    i = MsiRecordSetStringA(h,0,"42 ");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == MSI_NULL_INTEGER, "should get invalid integer\n");
    i = MsiRecordSetStringA(h,0,"42.0");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == MSI_NULL_INTEGER, "should get invalid integer\n");
    i = MsiRecordSetStringA(h,0,"0x42");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == MSI_NULL_INTEGER, "should get invalid integer\n");
    i = MsiRecordSetStringA(h,0,"1000000000000000");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == -1530494976, "should get truncated integer\n");
    i = MsiRecordSetStringA(h,0,"2147483647");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == 2147483647, "should get maxint\n");
    i = MsiRecordSetStringA(h,0,"-2147483647");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == -2147483647, "should get -maxint-1\n");
    i = MsiRecordSetStringA(h,0,"4294967297");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == 1, "should get one\n");
    i = MsiRecordSetStringA(h,0,"foo");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == MSI_NULL_INTEGER, "should get zero\n");
    i = MsiRecordSetStringA(h,0,"");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == MSI_NULL_INTEGER, "should get zero\n");
    i = MsiRecordSetStringA(h,0,"+1");
    ok(i == ERROR_SUCCESS, "Failed to set string at 0\n");
    i = MsiRecordGetInteger(h, 0);
    ok(i == MSI_NULL_INTEGER, "should get zero\n");

    /* same record, try converting integers to strings */
    r = MsiRecordSetInteger(h, 0, 32);
    ok(r == ERROR_SUCCESS, "Failed to set integer at 0 to 32\n");
    sz = 1;
    r = MsiRecordGetStringA(h, 0, NULL, &sz);
    ok(r == ERROR_SUCCESS, "failed to get string from integer\n");
    ok(sz == 2, "length wrong\n");
    buf[0]=0;
    sz = sizeof buf;
    r = MsiRecordGetStringA(h, 0, buf, &sz);
    ok(r == ERROR_SUCCESS, "failed to get string from integer\n");
    ok(0==strcmp(buf,"32"), "failed to get string from integer\n");
    r = MsiRecordSetInteger(h, 0, -32);
    ok(r == ERROR_SUCCESS, "Failed to set integer at 0 to 32\n");
    buf[0]=0;
    sz = 1;
    r = MsiRecordGetStringA(h, 0, NULL, &sz);
    ok(r == ERROR_SUCCESS, "failed to get string from integer\n");
    ok(sz == 3, "length wrong\n");
    sz = sizeof buf;
    r = MsiRecordGetStringA(h, 0, buf, &sz);
    ok(r == ERROR_SUCCESS, "failed to get string from integer\n");
    ok(0==strcmp(buf,"-32"), "failed to get string from integer\n");
    buf[0]=0;

    /* same record, now try streams */
    r = MsiRecordSetStreamA(h, 0, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "set NULL stream\n");
    sz = sizeof buf;
    r = MsiRecordReadStream(h, 0, buf, &sz);
    ok(r == ERROR_INVALID_DATATYPE, "read non-stream type\n");
    ok(sz == sizeof buf, "set sz\n");
    r = MsiRecordDataSize( h, -1);
    ok(r == 0,"MsiRecordDataSize returned wrong size\n");
    r = MsiRecordDataSize( h, 0);
    ok(r == 4,"MsiRecordDataSize returned wrong size\n");

    /* same record, now close it */
    r = MsiCloseHandle(h);
    ok(r == ERROR_SUCCESS, "Failed to close handle\n");

    /* now try streams in a new record - need to create a file to play with */
    r = create_temp_file(filename); 
    if(!r)
        return;

    /* streams can't be inserted in field 0 for some reason */
    h = MsiCreateRecord(2);
    ok(h, "couldn't create a two field record\n");
    r = MsiRecordSetStreamA(h, 0, filename);
    ok(r == ERROR_INVALID_PARAMETER, "added stream to field 0\n");
    r = MsiRecordSetStreamA(h, 1, filename);
    ok(r == ERROR_SUCCESS, "failed to add stream to record\n");
    r = MsiRecordReadStream(h, 1, buf, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "should return error\n");
    DeleteFileA(filename); /* Windows 98 doesn't like this at all, so don't check return. */
    r = MsiRecordReadStream(h, 1, NULL, NULL);
    ok(r == ERROR_INVALID_PARAMETER, "should return error\n");
    sz = sizeof buf;
    r = MsiRecordReadStream(h, 1, NULL, &sz);
    ok(r == ERROR_SUCCESS, "failed to read stream\n");
    ok(sz==26,"couldn't get size of stream\n");
    sz = 0;
    r = MsiRecordReadStream(h, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "failed to read stream\n");
    ok(sz==0,"short read\n");
    sz = sizeof buf;
    r = MsiRecordReadStream(h, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "failed to read stream\n");
    ok(sz==sizeof buf,"short read\n");
    ok(!strncmp(buf,"abcdefghij",10), "read the wrong thing\n");
    sz = sizeof buf;
    r = MsiRecordReadStream(h, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "failed to read stream\n");
    ok(sz==sizeof buf,"short read\n");
    ok(!strncmp(buf,"klmnopqrst",10), "read the wrong thing\n");
    memset(buf,0,sizeof buf);
    sz = sizeof buf;
    r = MsiRecordReadStream(h, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "failed to read stream\n");
    ok(sz==6,"short read\n");
    ok(!strcmp(buf,"uvwxyz"), "read the wrong thing\n");
    memset(buf,0,sizeof buf);
    sz = sizeof buf;
    r = MsiRecordReadStream(h, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "failed to read stream\n");
    ok(sz==0,"size non-zero at end of stream\n");
    ok(buf[0]==0, "read something at end of the stream\n");
    r = MsiRecordSetStreamA(h, 1, NULL);
    ok(r == ERROR_SUCCESS, "failed to reset stream\n");
    sz = 0;
    r = MsiRecordReadStream(h, 1, NULL, &sz);
    ok(r == ERROR_SUCCESS, "bytes left wrong after reset\n");
    ok(sz==26,"couldn't get size of stream\n");
    r = MsiRecordDataSize(h,1);
    ok(r == 26,"MsiRecordDataSize returned wrong size\n");

    /* now close the stream record */
    r = MsiCloseHandle(h);
    ok(r == ERROR_SUCCESS, "Failed to close handle\n");
    DeleteFileA(filename); /* Delete it for sure, when everything else is closed. */
}