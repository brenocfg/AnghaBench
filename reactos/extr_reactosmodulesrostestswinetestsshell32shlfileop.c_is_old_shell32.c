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
struct TYPE_3__ {int fFlags; int /*<<< orphan*/ * lpszProgressTitle; int /*<<< orphan*/ * hNameMappings; int /*<<< orphan*/ * pTo; int /*<<< orphan*/ * pFrom; int /*<<< orphan*/  wFunc; int /*<<< orphan*/ * hwnd; } ;
typedef  TYPE_1__ SHFILEOPSTRUCTA ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int FOF_MULTIDESTFILES ; 
 int FOF_NOCONFIRMATION ; 
 int FOF_NOCONFIRMMKDIR ; 
 int FOF_NOERRORUI ; 
 int FOF_SILENT ; 
 int /*<<< orphan*/  FO_COPY ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 scalar_t__ SHFileOperationA (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  set_curr_dir_path (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static BOOL is_old_shell32(void)
{
    SHFILEOPSTRUCTA shfo;
    CHAR from[5*MAX_PATH];
    CHAR to[5*MAX_PATH];
    DWORD retval;

    shfo.hwnd = NULL;
    shfo.wFunc = FO_COPY;
    shfo.pFrom = from;
    shfo.pTo = to;
    /* FOF_NOCONFIRMMKDIR is needed for old shell32 */
    shfo.fFlags = FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI | FOF_MULTIDESTFILES | FOF_NOCONFIRMMKDIR;
    shfo.hNameMappings = NULL;
    shfo.lpszProgressTitle = NULL;

    set_curr_dir_path(from, "test1.txt\0test2.txt\0test3.txt\0");
    set_curr_dir_path(to, "test6.txt\0test7.txt\0");
    retval = SHFileOperationA(&shfo);

    /* Delete extra files on old shell32 and Vista+*/
    DeleteFileA("test6.txt\\test1.txt");
    /* Delete extra files on old shell32 */
    DeleteFileA("test6.txt\\test2.txt");
    DeleteFileA("test6.txt\\test3.txt");
    /* Delete extra directory on old shell32 and Vista+ */
    RemoveDirectoryA("test6.txt");
    /* Delete extra files/directories on Vista+*/
    DeleteFileA("test7.txt\\test2.txt");
    RemoveDirectoryA("test7.txt");

    if (retval == ERROR_SUCCESS)
        return TRUE;

    return FALSE;
}