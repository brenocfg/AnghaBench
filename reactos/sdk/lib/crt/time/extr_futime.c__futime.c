#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct _utimbuf {scalar_t__ actime; scalar_t__ modtime; } ;
struct TYPE_4__ {scalar_t__ handle; } ;
typedef  TYPE_1__ ioinfo ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  scalar_t__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  RtlSecondsSince1970ToTime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFileTime (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  _dosmaperr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _time (scalar_t__*) ; 
 TYPE_1__* get_ioinfo (int) ; 
 int /*<<< orphan*/  release_ioinfo (TYPE_1__*) ; 

int
_futime(int fd, struct _utimbuf *filetime)
{
    ioinfo *info = get_ioinfo(fd);
    FILETIME at, wt;

    if (info->handle == INVALID_HANDLE_VALUE)
    {
        release_ioinfo(info);
        return -1;
    }

    if (!filetime)
    {
        time_t currTime;
        _time(&currTime);
        RtlSecondsSince1970ToTime((ULONG)currTime,
                                  (LARGE_INTEGER *)&at);
        wt = at;
    }
    else
    {
        RtlSecondsSince1970ToTime((ULONG)filetime->actime,
                                  (LARGE_INTEGER *)&at);
        if (filetime->actime == filetime->modtime)
        {
            wt = at;
        }
        else
        {
            RtlSecondsSince1970ToTime((ULONG)filetime->modtime,
                                      (LARGE_INTEGER *)&wt);
        }
    }

    if (!SetFileTime(info->handle, NULL, &at, &wt))
    {
        release_ioinfo(info);
        _dosmaperr(GetLastError());
        return -1 ;
    }
    release_ioinfo(info);
    return 0;
}