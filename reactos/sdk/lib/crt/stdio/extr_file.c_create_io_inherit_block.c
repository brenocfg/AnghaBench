#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int wxflag; scalar_t__ handle; } ;
typedef  TYPE_1__ ioinfo ;
typedef  int WORD ;
struct TYPE_6__ {scalar_t__ handle; } ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MSVCRT_MAX_FILES ; 
 int TRUE ; 
 int WX_DONTINHERIT ; 
 int WX_OPEN ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 TYPE_1__* get_ioinfo (int) ; 
 TYPE_3__* get_ioinfo_nolock (int) ; 
 int /*<<< orphan*/  release_ioinfo (TYPE_1__*) ; 

unsigned create_io_inherit_block(WORD *size, BYTE **block)
{
  int         fd, last_fd;
  char*       wxflag_ptr;
  HANDLE*     handle_ptr;
  ioinfo*     fdinfo;

  for (last_fd=MSVCRT_MAX_FILES-1; last_fd>=0; last_fd--)
    if (get_ioinfo_nolock(last_fd)->handle != INVALID_HANDLE_VALUE)
      break;
  last_fd++;

  *size = sizeof(unsigned) + (sizeof(char) + sizeof(HANDLE)) * last_fd;
  *block = calloc(1, *size);
  if (!*block)
  {
    *size = 0;
    return FALSE;
  }
  wxflag_ptr = (char*)*block + sizeof(unsigned);
  handle_ptr = (HANDLE*)(wxflag_ptr + last_fd);

  *(unsigned*)*block = last_fd;
  for (fd = 0; fd < last_fd; fd++)
  {
    /* to be inherited, we need it to be open, and that DONTINHERIT isn't set */
    fdinfo = get_ioinfo(fd);
    if ((fdinfo->wxflag & (WX_OPEN | WX_DONTINHERIT)) == WX_OPEN)
    {
      *wxflag_ptr = fdinfo->wxflag;
      *handle_ptr = fdinfo->handle;
    }
    else
    {
      *wxflag_ptr = 0;
      *handle_ptr = INVALID_HANDLE_VALUE;
    }
    release_ioinfo(fdinfo);
    wxflag_ptr++; handle_ptr++;
  }
  return TRUE;
}