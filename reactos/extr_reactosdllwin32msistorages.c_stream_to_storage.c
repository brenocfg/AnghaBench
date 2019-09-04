#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULARGE_INTEGER ;
struct TYPE_4__ {int QuadPart; } ;
struct TYPE_5__ {TYPE_1__ cbSize; } ;
typedef  TYPE_2__ STATSTG ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  ILockBytes ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CreateILockBytesOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILockBytes_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ILockBytes_WriteAt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  IStream_Stat (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATFLAG_NONAME ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_DENY_NONE ; 
 int /*<<< orphan*/  StgOpenStorageOnILockBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT stream_to_storage(IStream *stm, IStorage **stg)
{
    ILockBytes *lockbytes = NULL;
    STATSTG stat;
    LPVOID data;
    HRESULT hr;
    DWORD size, read;
    ULARGE_INTEGER offset;

    hr = IStream_Stat(stm, &stat, STATFLAG_NONAME);
    if (FAILED(hr))
        return hr;

    if (stat.cbSize.QuadPart >> 32)
    {
        ERR("Storage is too large\n");
        return E_FAIL;
    }

    size = stat.cbSize.QuadPart;
    data = msi_alloc(size);
    if (!data)
        return E_OUTOFMEMORY;

    hr = IStream_Read(stm, data, size, &read);
    if (FAILED(hr) || read != size)
        goto done;

    hr = CreateILockBytesOnHGlobal(NULL, TRUE, &lockbytes);
    if (FAILED(hr))
        goto done;

    ZeroMemory(&offset, sizeof(ULARGE_INTEGER));
    hr = ILockBytes_WriteAt(lockbytes, offset, data, size, &read);
    if (FAILED(hr) || read != size)
        goto done;

    hr = StgOpenStorageOnILockBytes(lockbytes, NULL,
                                    STGM_READWRITE | STGM_SHARE_DENY_NONE,
                                    NULL, 0, stg);
    if (FAILED(hr))
        goto done;

done:
    msi_free(data);
    if (lockbytes) ILockBytes_Release(lockbytes);
    return hr;
}