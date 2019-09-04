#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  reobject ;
struct TYPE_22__ {int lindex; int /*<<< orphan*/  tymed; void* dwAspect; int /*<<< orphan*/ * ptd; int /*<<< orphan*/  cfFormat; } ;
struct TYPE_21__ {int /*<<< orphan*/  reOle; } ;
struct TYPE_17__ {void* cy; void* cx; } ;
struct TYPE_20__ {int cbStruct; scalar_t__ dwUser; scalar_t__ dwFlags; void* dvaspect; TYPE_2__ sizel; int /*<<< orphan*/ * polesite; int /*<<< orphan*/ * pstg; int /*<<< orphan*/ * poleobj; int /*<<< orphan*/  clsid; int /*<<< orphan*/  cp; } ;
struct TYPE_19__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
struct TYPE_16__ {scalar_t__ hBitmap; scalar_t__ hEnhMetaFile; } ;
struct TYPE_18__ {int /*<<< orphan*/  tymed; int /*<<< orphan*/ * pUnkForRelease; TYPE_1__ u; } ;
typedef  TYPE_3__ STGMEDIUM ;
typedef  TYPE_4__ SIZEL ;
typedef  TYPE_5__ REOBJECT ;
typedef  TYPE_6__ ME_TextEditor ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/ * LPSTORAGE ;
typedef  int /*<<< orphan*/ * LPOLEOBJECT ;
typedef  int /*<<< orphan*/ * LPOLECLIENTSITE ;
typedef  int /*<<< orphan*/ * LPOLECACHE ;
typedef  int /*<<< orphan*/ * LPDATAOBJECT ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HENHMETAFILE ;
typedef  scalar_t__ HBITMAP ;
typedef  TYPE_7__ FORMATETC ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CF_BITMAP ; 
 int /*<<< orphan*/  CF_ENHMETAFILE ; 
 int /*<<< orphan*/  CLSID_NULL ; 
 int /*<<< orphan*/  CreateIRichEditOle (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *) ; 
 void* DVASPECT_CONTENT ; 
 scalar_t__ E_FAIL ; 
 int /*<<< orphan*/  IDataObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDataObject_SetData (int /*<<< orphan*/ *,TYPE_7__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IDataObject ; 
 int /*<<< orphan*/  IID_IOleCache ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 scalar_t__ IOleCache_Cache (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleCache_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleClientSite_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IOleObject_GetUserClassID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IOleObject_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IOleObject_SetClientSite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IRichEditOle_GetClientSite (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_InsertOLEFromCursor (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 void* MulDiv (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ OleCreateDefaultHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  REO_CP_SELECTION ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TYMED_ENHMF ; 
 int /*<<< orphan*/  TYMED_GDI ; 

__attribute__((used)) static HRESULT insert_static_object(ME_TextEditor *editor, HENHMETAFILE hemf, HBITMAP hbmp,
                                    const SIZEL* sz)
{
  LPOLEOBJECT         lpObject = NULL;
  LPSTORAGE           lpStorage = NULL;
  LPOLECLIENTSITE     lpClientSite = NULL;
  LPDATAOBJECT        lpDataObject = NULL;
  LPOLECACHE          lpOleCache = NULL;
  STGMEDIUM           stgm;
  FORMATETC           fm;
  CLSID               clsid;
  HRESULT             hr = E_FAIL;
  DWORD               conn;

  if (hemf)
  {
      stgm.tymed = TYMED_ENHMF;
      stgm.u.hEnhMetaFile = hemf;
      fm.cfFormat = CF_ENHMETAFILE;
  }
  else if (hbmp)
  {
      stgm.tymed = TYMED_GDI;
      stgm.u.hBitmap = hbmp;
      fm.cfFormat = CF_BITMAP;
  }
  stgm.pUnkForRelease = NULL;

  fm.ptd = NULL;
  fm.dwAspect = DVASPECT_CONTENT;
  fm.lindex = -1;
  fm.tymed = stgm.tymed;

  if (!editor->reOle)
  {
    if (!CreateIRichEditOle(NULL, editor, (LPVOID *)&editor->reOle))
      return hr;
  }

  if (OleCreateDefaultHandler(&CLSID_NULL, NULL, &IID_IOleObject, (void**)&lpObject) == S_OK &&
      IRichEditOle_GetClientSite(editor->reOle, &lpClientSite) == S_OK &&
      IOleObject_SetClientSite(lpObject, lpClientSite) == S_OK &&
      IOleObject_GetUserClassID(lpObject, &clsid) == S_OK &&
      IOleObject_QueryInterface(lpObject, &IID_IOleCache, (void**)&lpOleCache) == S_OK &&
      IOleCache_Cache(lpOleCache, &fm, 0, &conn) == S_OK &&
      IOleObject_QueryInterface(lpObject, &IID_IDataObject, (void**)&lpDataObject) == S_OK &&
      IDataObject_SetData(lpDataObject, &fm, &stgm, TRUE) == S_OK)
  {
    REOBJECT            reobject;

    reobject.cbStruct = sizeof(reobject);
    reobject.cp = REO_CP_SELECTION;
    reobject.clsid = clsid;
    reobject.poleobj = lpObject;
    reobject.pstg = lpStorage;
    reobject.polesite = lpClientSite;
    /* convert from twips to .01 mm */
    reobject.sizel.cx = MulDiv(sz->cx, 254, 144);
    reobject.sizel.cy = MulDiv(sz->cy, 254, 144);
    reobject.dvaspect = DVASPECT_CONTENT;
    reobject.dwFlags = 0; /* FIXME */
    reobject.dwUser = 0;

    ME_InsertOLEFromCursor(editor, &reobject, 0);
    hr = S_OK;
  }

  if (lpObject)       IOleObject_Release(lpObject);
  if (lpClientSite)   IOleClientSite_Release(lpClientSite);
  if (lpStorage)      IStorage_Release(lpStorage);
  if (lpDataObject)   IDataObject_Release(lpDataObject);
  if (lpOleCache)     IOleCache_Release(lpOleCache);

  return hr;
}