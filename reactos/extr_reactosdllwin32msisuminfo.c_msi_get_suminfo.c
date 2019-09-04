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
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  hdr; int /*<<< orphan*/  storage; } ;
typedef  TYPE_1__ MSISUMMARYINFO ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStorage_OpenStream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int STGM_READ ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* create_suminfo (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ load_summary_info (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szSumInfo ; 

UINT msi_get_suminfo( IStorage *stg, UINT uiUpdateCount, MSISUMMARYINFO **ret )
{
    IStream *stm;
    MSISUMMARYINFO *si;
    HRESULT hr;
    UINT r;

    TRACE("%p, %u\n", stg, uiUpdateCount);

    if (!(si = create_suminfo( stg, uiUpdateCount ))) return ERROR_OUTOFMEMORY;

    hr = IStorage_OpenStream( si->storage, szSumInfo, 0, STGM_READ|STGM_SHARE_EXCLUSIVE, 0, &stm );
    if (FAILED( hr ))
    {
        msiobj_release( &si->hdr );
        return ERROR_FUNCTION_FAILED;
    }

    r = load_summary_info( si, stm );
    IStream_Release( stm );
    if (r != ERROR_SUCCESS)
    {
        msiobj_release( &si->hdr );
        return r;
    }

    *ret = si;
    return ERROR_SUCCESS;
}