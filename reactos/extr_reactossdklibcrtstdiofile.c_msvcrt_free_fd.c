#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ wxflag; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ ioinfo ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetStdHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 TYPE_1__ __badioinfo ; 
 TYPE_1__* get_ioinfo (int) ; 
 int /*<<< orphan*/  release_ioinfo (TYPE_1__*) ; 

__attribute__((used)) static void msvcrt_free_fd(int fd)
{
  ioinfo *fdinfo = get_ioinfo(fd);

  if(fdinfo != &__badioinfo)
  {
    fdinfo->handle = INVALID_HANDLE_VALUE;
    fdinfo->wxflag = 0;
  }
  TRACE(":fd (%d) freed\n",fd);

  if (fd < 3)
  {
    switch (fd)
    {
    case 0:
        SetStdHandle(STD_INPUT_HANDLE, 0);
        break;
    case 1:
        SetStdHandle(STD_OUTPUT_HANDLE, 0);
        break;
    case 2:
        SetStdHandle(STD_ERROR_HANDLE, 0);
        break;
    }
  }
  release_ioinfo(fdinfo);
}