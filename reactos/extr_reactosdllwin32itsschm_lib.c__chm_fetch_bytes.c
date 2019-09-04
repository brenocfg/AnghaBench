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
struct chmFile {scalar_t__ fd; int /*<<< orphan*/  mutex; } ;
typedef  scalar_t__ UInt64 ;
typedef  int /*<<< orphan*/  UChar ;
struct TYPE_4__ {scalar_t__ QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  scalar_t__ Int64 ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CHM_ACQUIRE_LOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ CHM_NULL_FD ; 
 int /*<<< orphan*/  CHM_RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  FILE_CURRENT ; 
 scalar_t__ ReadFile (scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFilePointerEx (scalar_t__,TYPE_1__,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Int64 _chm_fetch_bytes(struct chmFile *h,
                              UChar *buf,
                              UInt64 os,
                              Int64 len)
{
    Int64 readLen=0;
    if (h->fd  ==  CHM_NULL_FD)
        return readLen;

    CHM_ACQUIRE_LOCK(h->mutex);
    /* NOTE: this might be better done with CreateFileMapping, et cetera... */
    {
        LARGE_INTEGER old_pos, new_pos;
        DWORD actualLen=0;

        /* awkward Win32 Seek/Tell */
        new_pos.QuadPart = 0;
        SetFilePointerEx( h->fd, new_pos, &old_pos, FILE_CURRENT );
        new_pos.QuadPart = os;
        SetFilePointerEx( h->fd, new_pos, NULL, FILE_BEGIN );

        /* read the data */
        if (ReadFile(h->fd,
                     buf,
                     (DWORD)len,
                     &actualLen,
                     NULL))
            readLen = actualLen;
        else
            readLen = 0;

        /* restore original position */
        SetFilePointerEx( h->fd, old_pos, NULL, FILE_BEGIN );
    }
    CHM_RELEASE_LOCK(h->mutex);
    return readLen;
}