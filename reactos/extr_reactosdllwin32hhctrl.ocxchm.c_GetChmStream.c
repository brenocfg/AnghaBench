#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * pStorage; int /*<<< orphan*/  pITStorage; } ;
struct TYPE_5__ {scalar_t__ chm_index; scalar_t__ chm_file; } ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ ChmPath ;
typedef  TYPE_2__ CHMInfo ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IITStorage_StgOpenStorage (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_OpenStream (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int STGM_READ ; 
 int STGM_SHARE_DENY_WRITE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__) ; 

IStream *GetChmStream(CHMInfo *info, LPCWSTR parent_chm, ChmPath *chm_file)
{
    IStorage *storage;
    IStream *stream = NULL;
    HRESULT hres;

    TRACE("%s (%s :: %s)\n", debugstr_w(parent_chm), debugstr_w(chm_file->chm_file),
          debugstr_w(chm_file->chm_index));

    if(parent_chm || chm_file->chm_file) {
        hres = IITStorage_StgOpenStorage(info->pITStorage,
                chm_file->chm_file ? chm_file->chm_file : parent_chm, NULL,
                STGM_READ | STGM_SHARE_DENY_WRITE, NULL, 0, &storage);
        if(FAILED(hres)) {
            WARN("Could not open storage: %08x\n", hres);
            return NULL;
        }
    }else {
        storage = info->pStorage;
        IStorage_AddRef(info->pStorage);
    }

    hres = IStorage_OpenStream(storage, chm_file->chm_index, NULL, STGM_READ, 0, &stream);
    IStorage_Release(storage);
    if(FAILED(hres))
        WARN("Could not open stream: %08x\n", hres);

    return stream;
}