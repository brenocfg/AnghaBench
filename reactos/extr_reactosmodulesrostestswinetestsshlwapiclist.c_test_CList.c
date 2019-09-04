#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct dummystream {int writecalls; int readcalls; int seekcalls; scalar_t__ readbeyondend; int /*<<< orphan*/  IStream_iface; scalar_t__ readreturnlarge; scalar_t__ failreadcall; scalar_t__ failwritesize; scalar_t__ failwritecall; } ;
struct TYPE_14__ {int ulSize; int ulId; } ;
struct TYPE_13__ {int ulSize; int ulId; } ;
typedef  int /*<<< orphan*/  SHLWAPI_CLIST ;
typedef  TYPE_1__* LPSHLWAPI_CLIST ;
typedef  TYPE_2__* LPCSHLWAPI_CLIST ;
typedef  unsigned int* LPBYTE ;
typedef  scalar_t__ HRESULT ;
typedef  unsigned int BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  InitDummyStream (struct dummystream*) ; 
 TYPE_2__* SHLWAPI_CLIST_items ; 
 scalar_t__ STG_E_ACCESSDENIED ; 
 scalar_t__ STG_E_MEDIUMFULL ; 
 scalar_t__ S_OK ; 
 scalar_t__ TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pSHLWAPI_17 (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ pSHLWAPI_18 (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  pSHLWAPI_19 (TYPE_1__*) ; 
 scalar_t__ pSHLWAPI_20 (TYPE_1__**,TYPE_1__*) ; 
 scalar_t__ pSHLWAPI_21 (TYPE_1__**,int) ; 
 TYPE_1__* pSHLWAPI_22 (TYPE_1__*,int) ; 

__attribute__((used)) static void test_CList(void)
{
  struct dummystream streamobj;
  LPSHLWAPI_CLIST list = NULL;
  LPCSHLWAPI_CLIST item = SHLWAPI_CLIST_items;
  BOOL bRet;
  HRESULT hRet;
  LPSHLWAPI_CLIST inserted;
  BYTE buff[64];
  unsigned int i;

  if (!pSHLWAPI_17 || !pSHLWAPI_18 || !pSHLWAPI_19 || !pSHLWAPI_20 ||
      !pSHLWAPI_21 || !pSHLWAPI_22)
    return;

  /* Populate a list and test the items are added correctly */
  while (item->ulSize)
  {
    /* Create item and fill with data */
    inserted = (LPSHLWAPI_CLIST)buff;
    inserted->ulSize = item->ulSize + sizeof(SHLWAPI_CLIST);
    inserted->ulId = item->ulId;
    for (i = 0; i < item->ulSize; i++)
      buff[sizeof(SHLWAPI_CLIST)+i] = i*2;

    /* Add it */
    bRet = pSHLWAPI_20(&list, inserted);
    ok(bRet == TRUE, "failed list add\n");

    if (bRet == TRUE)
    {
      ok(list && list->ulSize, "item not added\n");

      /* Find it */
      inserted = pSHLWAPI_22(list, item->ulId);
      ok(inserted != NULL, "lost after adding\n");

      ok(!inserted || inserted->ulId != ~0U, "find returned a container\n");

      /* Check size */
      if (inserted && inserted->ulSize & 0x3)
      {
        /* Contained */
        ok(inserted[-1].ulId == ~0U, "invalid size is not countained\n");
        ok(inserted[-1].ulSize > inserted->ulSize+sizeof(SHLWAPI_CLIST),
           "container too small\n");
      }
      else if (inserted)
      {
        ok(inserted->ulSize==item->ulSize+sizeof(SHLWAPI_CLIST),
           "id %d wrong size %d\n", inserted->ulId, inserted->ulSize);
      }
      if (inserted)
      {
        BOOL bDataOK = TRUE;
        LPBYTE bufftest = (LPBYTE)inserted;

        for (i = 0; i < inserted->ulSize - sizeof(SHLWAPI_CLIST); i++)
          if (bufftest[sizeof(SHLWAPI_CLIST)+i] != i*2)
            bDataOK = FALSE;

        ok(bDataOK == TRUE, "data corrupted on insert\n");
      }
      ok(!inserted || inserted->ulId==item->ulId, "find got wrong item\n");
    }
    item++;
  }

  /* Write the list */
  InitDummyStream(&streamobj);

  hRet = pSHLWAPI_17(&streamobj.IStream_iface, list);
  ok(hRet == S_OK, "write failed\n");
  if (hRet == S_OK)
  {
    /* 1 call for each element, + 1 for OK (use our null element for this) */
    ok(streamobj.writecalls == ARRAY_SIZE(SHLWAPI_CLIST_items), "wrong call count\n");
    ok(streamobj.readcalls == 0,"called Read() in write\n");
    ok(streamobj.seekcalls == 0,"called Seek() in write\n");
  }

  /* Failure cases for writing */
  InitDummyStream(&streamobj);
  streamobj.failwritecall = TRUE;
  hRet = pSHLWAPI_17(&streamobj.IStream_iface, list);
  ok(hRet == STG_E_ACCESSDENIED, "changed object failure return\n");
  ok(streamobj.writecalls == 1, "called object after failure\n");
  ok(streamobj.readcalls == 0,"called Read() after failure\n");
  ok(streamobj.seekcalls == 0,"called Seek() after failure\n");

  InitDummyStream(&streamobj);
  streamobj.failwritesize = TRUE;
  hRet = pSHLWAPI_17(&streamobj.IStream_iface, list);
  ok(hRet == STG_E_MEDIUMFULL || broken(hRet == E_FAIL) /* Win7 */,
     "changed size failure return\n");
  ok(streamobj.writecalls == 1, "called object after size failure\n");
  ok(streamobj.readcalls == 0,"called Read() after failure\n");
  ok(streamobj.seekcalls == 0,"called Seek() after failure\n");

  /* Invalid inputs for adding */
  inserted = (LPSHLWAPI_CLIST)buff;
  inserted->ulSize = sizeof(SHLWAPI_CLIST) -1;
  inserted->ulId = 33;
  bRet = pSHLWAPI_20(&list, inserted);
  ok(bRet == FALSE, "Expected failure\n");

  inserted = pSHLWAPI_22(list, 33);
  ok(inserted == NULL, "inserted bad element size\n");

  inserted = (LPSHLWAPI_CLIST)buff;
  inserted->ulSize = 44;
  inserted->ulId = ~0U;
  bRet = pSHLWAPI_20(&list, inserted);
  ok(bRet == FALSE, "Expected failure\n");

  item = SHLWAPI_CLIST_items;

  /* Look for nonexistent item in populated list */
  inserted = pSHLWAPI_22(list, 99999999);
  ok(inserted == NULL, "found a nonexistent item\n");

  while (item->ulSize)
  {
    /* Delete items */
    BOOL bRet = pSHLWAPI_21(&list, item->ulId);
    ok(bRet == TRUE, "couldn't find item to delete\n");
    item++;
  }

  /* Look for nonexistent item in empty list */
  inserted = pSHLWAPI_22(list, 99999999);
  ok(inserted == NULL, "found an item in empty list\n");

  /* Create a list by reading in data */
  InitDummyStream(&streamobj);

  hRet = pSHLWAPI_18(&streamobj.IStream_iface, &list);
  ok(hRet == S_OK, "failed create from Read()\n");
  if (hRet == S_OK)
  {
    ok(streamobj.readbeyondend == FALSE, "read beyond end\n");
    /* 2 calls per item, but only 1 for the terminator */
    ok(streamobj.readcalls == ARRAY_SIZE(SHLWAPI_CLIST_items) * 2 - 1, "wrong call count\n");
    ok(streamobj.writecalls == 0, "called Write() from create\n");
    ok(streamobj.seekcalls == 0,"called Seek() from create\n");

    item = SHLWAPI_CLIST_items;

    /* Check the items were added correctly */
    while (item->ulSize)
    {
      inserted = pSHLWAPI_22(list, item->ulId);
      ok(inserted != NULL, "lost after adding\n");

      ok(!inserted || inserted->ulId != ~0U, "find returned a container\n");

      /* Check size */
      if (inserted && inserted->ulSize & 0x3)
      {
        /* Contained */
        ok(inserted[-1].ulId == ~0U, "invalid size is not countained\n");
        ok(inserted[-1].ulSize > inserted->ulSize+sizeof(SHLWAPI_CLIST),
           "container too small\n");
      }
      else if (inserted)
      {
        ok(inserted->ulSize==item->ulSize+sizeof(SHLWAPI_CLIST),
           "id %d wrong size %d\n", inserted->ulId, inserted->ulSize);
      }
      ok(!inserted || inserted->ulId==item->ulId, "find got wrong item\n");
      if (inserted)
      {
        BOOL bDataOK = TRUE;
        LPBYTE bufftest = (LPBYTE)inserted;

        for (i = 0; i < inserted->ulSize - sizeof(SHLWAPI_CLIST); i++)
          if (bufftest[sizeof(SHLWAPI_CLIST)+i] != i*2)
            bDataOK = FALSE;

        ok(bDataOK == TRUE, "data corrupted on insert\n");
      }
      item++;
    }
  }

  /* Failure cases for reading */
  InitDummyStream(&streamobj);
  streamobj.failreadcall = TRUE;
  hRet = pSHLWAPI_18(&streamobj.IStream_iface, &list);
  ok(hRet == STG_E_ACCESSDENIED, "changed object failure return\n");
  ok(streamobj.readbeyondend == FALSE, "read beyond end\n");
  ok(streamobj.readcalls == 1, "called object after read failure\n");
  ok(streamobj.writecalls == 0,"called Write() after read failure\n");
  ok(streamobj.seekcalls == 0,"called Seek() after read failure\n");

  /* Read returns large object */
  InitDummyStream(&streamobj);
  streamobj.readreturnlarge = TRUE;
  hRet = pSHLWAPI_18(&streamobj.IStream_iface, &list);
  ok(hRet == S_OK, "failed create from Read() with large item\n");
  ok(streamobj.readbeyondend == FALSE, "read beyond end\n");
  ok(streamobj.readcalls == 1,"wrong call count\n");
  ok(streamobj.writecalls == 0,"called Write() after read failure\n");
  ok(streamobj.seekcalls == 2,"wrong Seek() call count (%d)\n", streamobj.seekcalls);

  pSHLWAPI_19(list);
}