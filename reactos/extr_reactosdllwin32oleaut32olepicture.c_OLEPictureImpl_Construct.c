#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  yExt; int /*<<< orphan*/  xExt; TYPE_6__* hmeta; } ;
struct TYPE_21__ {TYPE_4__ wmf; } ;
struct TYPE_23__ {int picType; TYPE_5__ u; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_17__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_22__ {int ref; int loadtime_magic; TYPE_7__ desc; TYPE_13__ IPicture_iface; int /*<<< orphan*/  himetricHeight; int /*<<< orphan*/  himetricWidth; int /*<<< orphan*/  bIsDirty; scalar_t__ loadtime_format; int /*<<< orphan*/ * hbmXor; int /*<<< orphan*/ * hbmMask; int /*<<< orphan*/  keepOrigFormat; int /*<<< orphan*/  fOwn; scalar_t__ hDCCur; int /*<<< orphan*/ * pCP; TYPE_3__ IConnectionPointContainer_iface; TYPE_2__ IPersistStream_iface; TYPE_1__ IDispatch_iface; } ;
typedef  TYPE_6__ OLEPictureImpl ;
typedef  TYPE_7__* LPPICTDESC ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CreateConnectionPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ E_UNEXPECTED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_6__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  IID_IPropertyNotifySink ; 
 int /*<<< orphan*/  IPicture_Release (TYPE_13__*) ; 
 int /*<<< orphan*/  OLEPictureImpl_IConnectionPointContainer_VTable ; 
 int /*<<< orphan*/  OLEPictureImpl_IDispatch_VTable ; 
 int /*<<< orphan*/  OLEPictureImpl_IPersistStream_VTable ; 
 int /*<<< orphan*/  OLEPictureImpl_SetBitmap (TYPE_6__*) ; 
 int /*<<< orphan*/  OLEPictureImpl_SetEMF (TYPE_6__*) ; 
 int /*<<< orphan*/  OLEPictureImpl_SetIcon (TYPE_6__*) ; 
 int /*<<< orphan*/  OLEPictureImpl_VTable ; 
#define  PICTYPE_BITMAP 132 
#define  PICTYPE_ENHMETAFILE 131 
#define  PICTYPE_ICON 130 
#define  PICTYPE_METAFILE 129 
#define  PICTYPE_NONE 128 
 int PICTYPE_UNINITIALIZED ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static HRESULT OLEPictureImpl_Construct(LPPICTDESC pictDesc, BOOL fOwn, OLEPictureImpl **pict)
{
  OLEPictureImpl *newObject;
  HRESULT hr;

  if (pictDesc)
      TRACE("(%p) type = %d\n", pictDesc, pictDesc->picType);

  /*
   * Allocate space for the object.
   */
  newObject = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(OLEPictureImpl));
  if (!newObject)
    return E_OUTOFMEMORY;

  /*
   * Initialize the virtual function table.
   */
  newObject->IPicture_iface.lpVtbl = &OLEPictureImpl_VTable;
  newObject->IDispatch_iface.lpVtbl = &OLEPictureImpl_IDispatch_VTable;
  newObject->IPersistStream_iface.lpVtbl = &OLEPictureImpl_IPersistStream_VTable;
  newObject->IConnectionPointContainer_iface.lpVtbl = &OLEPictureImpl_IConnectionPointContainer_VTable;

  newObject->pCP = NULL;
  hr = CreateConnectionPoint((IUnknown*)&newObject->IPicture_iface, &IID_IPropertyNotifySink,
                        &newObject->pCP);
  if (hr != S_OK)
  {
    HeapFree(GetProcessHeap(), 0, newObject);
    return hr;
  }

  /*
   * Start with one reference count. The caller of this function
   * must release the interface pointer when it is done.
   */
  newObject->ref	= 1;
  newObject->hDCCur	= 0;

  newObject->fOwn	= fOwn;

  /* dunno about original value */
  newObject->keepOrigFormat = TRUE;

  newObject->hbmMask = NULL;
  newObject->hbmXor = NULL;
  newObject->loadtime_magic = 0xdeadbeef;
  newObject->loadtime_format = 0;
  newObject->bIsDirty = FALSE;

  if (pictDesc) {
      newObject->desc = *pictDesc;

      switch(pictDesc->picType) {
      case PICTYPE_BITMAP:
	OLEPictureImpl_SetBitmap(newObject);
	break;

      case PICTYPE_METAFILE:
	TRACE("metafile handle %p\n", pictDesc->u.wmf.hmeta);
	newObject->himetricWidth = pictDesc->u.wmf.xExt;
	newObject->himetricHeight = pictDesc->u.wmf.yExt;
	break;

      case PICTYPE_NONE:
	/* not sure what to do here */
	newObject->himetricWidth = newObject->himetricHeight = 0;
	break;

      case PICTYPE_ICON:
        OLEPictureImpl_SetIcon(newObject);
        break;

      case PICTYPE_ENHMETAFILE:
        OLEPictureImpl_SetEMF(newObject);
        break;

      default:
        WARN("Unsupported type %d\n", pictDesc->picType);
        IPicture_Release(&newObject->IPicture_iface);
        return E_UNEXPECTED;
      }
  } else {
      newObject->desc.picType = PICTYPE_UNINITIALIZED;
  }

  TRACE("returning %p\n", newObject);
  *pict = newObject;
  return S_OK;
}