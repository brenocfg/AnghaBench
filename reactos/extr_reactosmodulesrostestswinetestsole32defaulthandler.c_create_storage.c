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
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  ILockBytes ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateILockBytesOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ILockBytes_Release (int /*<<< orphan*/ *) ; 
 int STGM_CREATE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StgCreateDocfileOnILockBytes (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static HRESULT create_storage(IStorage **stg)
{
    HRESULT hr;
    ILockBytes *lock_bytes;

    hr = CreateILockBytesOnHGlobal(NULL, TRUE, &lock_bytes);
    if(SUCCEEDED(hr))
    {
        hr = StgCreateDocfileOnILockBytes(lock_bytes,
                  STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, stg);
        ILockBytes_Release(lock_bytes);
    }
    return hr;
}