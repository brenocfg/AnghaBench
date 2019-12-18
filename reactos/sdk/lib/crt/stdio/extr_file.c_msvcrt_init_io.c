#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int wxflag; scalar_t__ handle; } ;
typedef  TYPE_1__ ioinfo ;
struct TYPE_14__ {int /*<<< orphan*/  handle; } ;
struct TYPE_13__ {unsigned int _file; int /*<<< orphan*/  _flag; int /*<<< orphan*/ * _tmpfname; } ;
struct TYPE_12__ {int cbReserved2; int* lpReserved2; } ;
typedef  TYPE_2__ STARTUPINFOA ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int FILE_TYPE_CHAR ; 
 int FILE_TYPE_PIPE ; 
 int GetFileType (scalar_t__) ; 
 int /*<<< orphan*/  GetStartupInfoA (TYPE_2__*) ; 
 scalar_t__ GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MSVCRT_MAX_FILES ; 
 int MSVCRT_stream_idx ; 
 unsigned int STDERR_FILENO ; 
 unsigned int STDIN_FILENO ; 
 unsigned int STDOUT_FILENO ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WX_OPEN ; 
 int WX_PIPE ; 
 int WX_TEXT ; 
 int WX_TTY ; 
 int /*<<< orphan*/  _IOREAD ; 
 int /*<<< orphan*/  _IOWRT ; 
 TYPE_1__ __badioinfo ; 
 TYPE_5__* _iob ; 
 TYPE_1__* get_ioinfo_alloc_fd (unsigned int) ; 
 TYPE_6__* get_ioinfo_nolock (unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 unsigned int min (unsigned int,int) ; 
 int /*<<< orphan*/  msvcrt_set_fd (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  release_ioinfo (TYPE_1__*) ; 

void msvcrt_init_io(void)
{
  STARTUPINFOA  si;
  unsigned int  i;
  ioinfo        *fdinfo;

  GetStartupInfoA(&si);
  if (si.cbReserved2 >= sizeof(unsigned int) && si.lpReserved2 != NULL)
  {
    BYTE*       wxflag_ptr;
    HANDLE*     handle_ptr;
    unsigned int count;

    count = *(unsigned*)si.lpReserved2;
    wxflag_ptr = si.lpReserved2 + sizeof(unsigned);
    handle_ptr = (HANDLE*)(wxflag_ptr + count);

    count = min(count, (si.cbReserved2 - sizeof(unsigned)) / (sizeof(HANDLE) + 1));
    count = min(count, MSVCRT_MAX_FILES);
    for (i = 0; i < count; i++)
    {
      if ((*wxflag_ptr & WX_OPEN) && *handle_ptr != INVALID_HANDLE_VALUE)
      {
        fdinfo = get_ioinfo_alloc_fd(i);
        if(fdinfo != &__badioinfo)
            msvcrt_set_fd(fdinfo, *handle_ptr, *wxflag_ptr);
        release_ioinfo(fdinfo);
      }

      wxflag_ptr++; handle_ptr++;
    }
  }

  fdinfo = get_ioinfo_alloc_fd(STDIN_FILENO);
  if (!(fdinfo->wxflag & WX_OPEN) || fdinfo->handle == INVALID_HANDLE_VALUE) {
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    DWORD type = GetFileType(h);

    msvcrt_set_fd(fdinfo, h, WX_OPEN|WX_TEXT|((type&0xf)==FILE_TYPE_CHAR ? WX_TTY : 0)
            |((type&0xf)==FILE_TYPE_PIPE ? WX_PIPE : 0));
  }
  release_ioinfo(fdinfo);

  fdinfo = get_ioinfo_alloc_fd(STDOUT_FILENO);
  if (!(fdinfo->wxflag & WX_OPEN) || fdinfo->handle == INVALID_HANDLE_VALUE) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD type = GetFileType(h);

    msvcrt_set_fd(fdinfo, h, WX_OPEN|WX_TEXT|((type&0xf)==FILE_TYPE_CHAR ? WX_TTY : 0)
            |((type&0xf)==FILE_TYPE_PIPE ? WX_PIPE : 0));
  }
  release_ioinfo(fdinfo);

  fdinfo = get_ioinfo_alloc_fd(STDERR_FILENO);
  if (!(fdinfo->wxflag & WX_OPEN) || fdinfo->handle == INVALID_HANDLE_VALUE) {
    HANDLE h = GetStdHandle(STD_ERROR_HANDLE);
    DWORD type = GetFileType(h);

    msvcrt_set_fd(fdinfo, h, WX_OPEN|WX_TEXT|((type&0xf)==FILE_TYPE_CHAR ? WX_TTY : 0)
            |((type&0xf)==FILE_TYPE_PIPE ? WX_PIPE : 0));
  }
  release_ioinfo(fdinfo);

  TRACE(":handles (%p)(%p)(%p)\n", get_ioinfo_nolock(STDIN_FILENO)->handle,
        get_ioinfo_nolock(STDOUT_FILENO)->handle,
        get_ioinfo_nolock(STDERR_FILENO)->handle);

  memset(_iob,0,3*sizeof(FILE));
  for (i = 0; i < 3; i++)
  {
    /* FILE structs for stdin/out/err are static and never deleted */
    _iob[i]._file = i;
    _iob[i]._tmpfname = NULL;
    _iob[i]._flag = (i == 0) ? _IOREAD : _IOWRT;
  }
  MSVCRT_stream_idx = 3;
}