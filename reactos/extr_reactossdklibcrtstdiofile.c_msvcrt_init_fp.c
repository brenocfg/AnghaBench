#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  crit; } ;
typedef  TYPE_1__ file_crit ;
struct TYPE_8__ {int wxflag; } ;
struct TYPE_7__ {int _file; unsigned int _flag; int /*<<< orphan*/ * _tmpfname; scalar_t__ _cnt; int /*<<< orphan*/ * _base; int /*<<< orphan*/  _ptr; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int WX_OPEN ; 
 int _IOB_ENTRIES ; 
 scalar_t__* __doserrno () ; 
 int /*<<< orphan*/ * _errno () ; 
 TYPE_2__* _iob ; 
 TYPE_4__* get_ioinfo_nolock (int) ; 

__attribute__((used)) static int msvcrt_init_fp(FILE* file, int fd, unsigned stream_flags)
{
  TRACE(":fd (%d) allocating FILE*\n",fd);
  if (!(get_ioinfo_nolock(fd)->wxflag & WX_OPEN))
  {
    WARN(":invalid fd %d\n",fd);
    *__doserrno() = 0;
    *_errno() = EBADF;
    return -1;
  }
  file->_ptr = file->_base = NULL;
  file->_cnt = 0;
  file->_file = fd;
  file->_flag = stream_flags;
  file->_tmpfname = NULL;

  if(file<_iob || file>=_iob+_IOB_ENTRIES)
      InitializeCriticalSection(&((file_crit*)file)->crit);

  TRACE(":got FILE* (%p)\n",file);
  return 0;
}