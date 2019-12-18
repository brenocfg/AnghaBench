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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IStorage_CreateStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Write (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int STGM_CREATE ; 
 int STGM_DIRECT ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int STGM_WRITE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StgCreateDocfile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL create_storage(LPCSTR name)
{
    WCHAR nameW[MAX_PATH];
    IStorage *stg;
    IStream *stm;
    HRESULT hr;
    DWORD count;
    BOOL res = FALSE;

    MultiByteToWideChar(CP_ACP, 0, name, -1, nameW, MAX_PATH);
    hr = StgCreateDocfile(nameW, STGM_CREATE | STGM_READWRITE |
                          STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 0, &stg);
    if (FAILED(hr))
        return FALSE;

    hr = IStorage_CreateStream(stg, nameW, STGM_WRITE | STGM_SHARE_EXCLUSIVE,
                               0, 0, &stm);
    if (FAILED(hr))
        goto done;

    hr = IStream_Write(stm, "stgdata", 8, &count);
    if (SUCCEEDED(hr))
        res = TRUE;

done:
    IStream_Release(stm);
    IStorage_Release(stg);

    return res;
}