#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  marshal_data; } ;
typedef  TYPE_1__ ole_clipbrd ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  CLIPBRD_E_CANT_SET ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int GMEM_DDESHARE ; 
 int GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GetHGlobalFromStream (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalAlloc (int,int) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SetClipboardData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup_global_mem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_marshal_clipboard_format ; 

__attribute__((used)) static HRESULT expose_marshalled_dataobject(ole_clipbrd *clipbrd, IDataObject *data)
{
    HGLOBAL h;

    if(data)
    {
        HGLOBAL h_stm;
        GetHGlobalFromStream(clipbrd->marshal_data, &h_stm);
        dup_global_mem(h_stm, GMEM_DDESHARE|GMEM_MOVEABLE, &h);
    }
    else /* flushed */
        h = GlobalAlloc(GMEM_DDESHARE|GMEM_MOVEABLE, 1);

    if(!h) return E_OUTOFMEMORY;

    if(!SetClipboardData(wine_marshal_clipboard_format, h))
    {
        GlobalFree(h);
        return CLIPBRD_E_CANT_SET;
    }
    return S_OK;
}