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
typedef  int /*<<< orphan*/  WIN32_FIND_DATAA ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DATA2 ;
typedef  int /*<<< orphan*/  DATA ;

/* Variables and functions */
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTempFileNameA (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 size_t fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_filemodeT(void)
{
    char DATA  [] = {26, 't', 'e', 's' ,'t'};
    char DATA2 [100];
    char temppath[MAX_PATH];
    char tempfile[MAX_PATH];
    FILE* f;
    size_t bytesWritten;
    size_t bytesRead;
    WIN32_FIND_DATAA findData;
    HANDLE h;

    GetTempPathA(MAX_PATH, temppath);
    GetTempFileNameA(temppath, "", 0, tempfile);

    f = fopen(tempfile, "w+bDT");
    bytesWritten = fwrite(DATA, 1, sizeof(DATA), f);
    rewind(f);
    bytesRead = fread(DATA2, 1, sizeof(DATA2), f);
    fclose(f);

    ok (bytesRead == bytesWritten && bytesRead == sizeof(DATA),
        "fopen file mode 'T' wrongly interpreted as 't'\n" );

    h = FindFirstFileA(tempfile, &findData);

    ok (h == INVALID_HANDLE_VALUE, "file wasn't deleted when closed.\n" );

    if (h != INVALID_HANDLE_VALUE) FindClose(h);
}