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
struct stat {int dummy; } ;
struct _stat {int dummy; } ;
struct TYPE_3__ {int dwFileAttributes; scalar_t__ dwReserved0; } ;
typedef  TYPE_1__ WIN32_FIND_DATA ;
typedef  int /*<<< orphan*/  OPEN_OH_ARGTYPE ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CreateFile (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_REPARSE_POINT ; 
 int /*<<< orphan*/  FILE_FLAG_BACKUP_SEMANTICS ; 
 int /*<<< orphan*/  FILE_READ_ATTRIBUTES ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFile (char const*,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ IO_REPARSE_TAG_SYMLINK ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _O_RDONLY ; 
 int /*<<< orphan*/  _close (int) ; 
 int _fstat (int,struct _stat*) ; 
 int _open_osfhandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static int
stat_symlink_aware(const char *name, struct stat *stp)
{
#if defined(_MSC_VER) && _MSC_VER < 1700
    /* Work around for VC10 or earlier. stat() can't handle symlinks properly.
     * VC9 or earlier: stat() doesn't support a symlink at all. It retrieves
     * status of a symlink itself.
     * VC10: stat() supports a symlink to a normal file, but it doesn't support
     * a symlink to a directory (always returns an error). */
    WIN32_FIND_DATA	findData;
    HANDLE		hFind, h;
    DWORD		attr = 0;
    BOOL		is_symlink = FALSE;

    hFind = FindFirstFile(name, &findData);
    if (hFind != INVALID_HANDLE_VALUE)
    {
	attr = findData.dwFileAttributes;
	if ((attr & FILE_ATTRIBUTE_REPARSE_POINT)
		&& (findData.dwReserved0 == IO_REPARSE_TAG_SYMLINK))
	    is_symlink = TRUE;
	FindClose(hFind);
    }
    if (is_symlink)
    {
	h = CreateFile(name, FILE_READ_ATTRIBUTES,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING,
		(attr & FILE_ATTRIBUTE_DIRECTORY)
					    ? FILE_FLAG_BACKUP_SEMANTICS : 0,
		NULL);
	if (h != INVALID_HANDLE_VALUE)
	{
	    int	    fd, n;

	    fd = _open_osfhandle((OPEN_OH_ARGTYPE)h, _O_RDONLY);
	    n = _fstat(fd, (struct _stat*)stp);
	    _close(fd);
	    return n;
	}
    }
#endif
    return stat(name, stp);
}