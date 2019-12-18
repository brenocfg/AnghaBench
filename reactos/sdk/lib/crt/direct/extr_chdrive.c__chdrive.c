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
typedef  int WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetCurrentDirectoryW (int*) ; 
 int /*<<< orphan*/  _dosmaperr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _set_errno (int /*<<< orphan*/ ) ; 

int _chdrive(int newdrive)
{
  WCHAR buffer[] = L"A:";

  buffer[0] += newdrive - 1;
  if (!SetCurrentDirectoryW( buffer ))
  {
    _dosmaperr(GetLastError());
    if (newdrive <= 0)
    {
      _set_errno(EACCES);
    }
    return -1;
  }
  return 0;
}