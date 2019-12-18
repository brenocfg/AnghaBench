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
typedef  int /*<<< orphan*/  temp_path ;
typedef  int /*<<< orphan*/  psadobe ;
typedef  int /*<<< orphan*/  di ;
typedef  int /*<<< orphan*/  buf ;
typedef  int WORD ;
struct TYPE_3__ {int cbSize; char* lpszDocName; char* lpszOutput; scalar_t__ fwType; int /*<<< orphan*/ * lpszDatatype; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  TYPE_1__ DOCINFOA ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOWNLOADHEADER ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int EndDoc (int /*<<< orphan*/ ) ; 
 int Escape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int ExtEscape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetTempFileNameA (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  POSTSCRIPT_PASSTHROUGH ; 
 int ReadFile (scalar_t__,char*,int,int*,int /*<<< orphan*/ *) ; 
 int StartDocA (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void print_something(HDC hdc)
{
    static const char psadobe[10] = "%!PS-Adobe";
    char buf[1024], *p;
    char temp_path[MAX_PATH], file_name[MAX_PATH];
    DOCINFOA di;
    DWORD ret;
    HANDLE hfile;

    GetTempPathA(sizeof(temp_path), temp_path);
    GetTempFileNameA(temp_path, "ps", 0, file_name);

    di.cbSize = sizeof(di);
    di.lpszDocName = "Let's dance";
    di.lpszOutput = file_name;
    di.lpszDatatype = NULL;
    di.fwType = 0;
    ret = StartDocA(hdc, &di);
    ok(ret > 0, "StartDoc failed: %d\n", ret);

    strcpy(buf + 2, "\n% ===> before DOWNLOADHEADER <===\n");
    *(WORD *)buf = strlen(buf + 2);
    ret = Escape(hdc, POSTSCRIPT_PASSTHROUGH, 0, buf, NULL);
    ok(ret == *(WORD *)buf, "POSTSCRIPT_PASSTHROUGH failed: %d\n", ret);

    strcpy(buf, "deadbeef");
    ret = ExtEscape(hdc, DOWNLOADHEADER, 0, NULL, sizeof(buf), buf );
    ok(ret == 1, "DOWNLOADHEADER failed\n");
    ok(strcmp(buf, "deadbeef") != 0, "DOWNLOADHEADER failed\n");

    strcpy(buf + 2, "\n% ===> after DOWNLOADHEADER <===\n");
    *(WORD *)buf = strlen(buf + 2);
    ret = Escape(hdc, POSTSCRIPT_PASSTHROUGH, 0, buf, NULL);
    ok(ret == *(WORD *)buf, "POSTSCRIPT_PASSTHROUGH failed: %d\n", ret);

    ret = EndDoc(hdc);
    ok(ret == 1, "EndDoc failed\n");

    hfile = CreateFileA(file_name, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "CreateFile failed\n");
    memset(buf, 0, sizeof(buf));
    ret = ReadFile(hfile, buf, sizeof(buf), &ret, NULL);
    ok(ret, "ReadFile failed\n");
    CloseHandle(hfile);

    /* skip the HP PCL language selector */
    buf[sizeof(buf) - 1] = 0;
    p = buf;
    while (*p)
    {
        if (!(p[0] == 0x1b && p[1] == '%') && memcmp(p, "@PJL", 4) != 0)
            break;

        p = strchr(p, '\n');
        if (!p) break;

        while (*p == '\r' || *p == '\n') p++;
    }
    ok(p && !memcmp(p, psadobe, sizeof(psadobe)), "wrong signature: %.14s\n", p ? p : buf);

    DeleteFileA(file_name);
}