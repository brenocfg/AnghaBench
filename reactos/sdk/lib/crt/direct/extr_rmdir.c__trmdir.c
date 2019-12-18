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
typedef  int /*<<< orphan*/  _TCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  RemoveDirectory (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _dosmaperr (int /*<<< orphan*/ ) ; 

int _trmdir(const _TCHAR* _path)
{
    if (!RemoveDirectory(_path)) {
    	_dosmaperr(GetLastError());
        return -1;
    }
    return 0;
}