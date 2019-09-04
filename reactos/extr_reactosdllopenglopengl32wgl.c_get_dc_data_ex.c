#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ u; } ;
struct wgl_dc_data {struct wgl_dc_data* next; int /*<<< orphan*/  nb_sw_formats; scalar_t__ nb_icd_formats; TYPE_2__* icd_data; int /*<<< orphan*/ * sw_data; scalar_t__ pixelformat; int /*<<< orphan*/  flags; TYPE_1__ owner; } ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/ * DriverName; scalar_t__ (* DrvDescribePixelFormat ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PIXELFORMATDESCRIPTOR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ GetObjectType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct wgl_dc_data* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* IntGetIcdData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ OBJ_DC ; 
 scalar_t__ OBJ_MEMDC ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WGL_DC_OBJ_DC ; 
 int /*<<< orphan*/ * WindowFromDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_data_cs ; 
 struct wgl_dc_data* dc_data_list ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sw_DescribePixelFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
struct wgl_dc_data*
get_dc_data_ex(HDC hdc, INT format, UINT size, PIXELFORMATDESCRIPTOR *descr)
{
    HWND hwnd = NULL;
    struct wgl_dc_data* data;
    DWORD objType = GetObjectType(hdc);
    ULONG flags = 0;
    union
    {
        HWND hwnd;
        HDC hdc;
        HANDLE u;
    } id;
    
    /* Look for the right data identifier */
    if(objType == OBJ_DC)
    {
        hwnd = WindowFromDC(hdc);
        if(!hwnd)
            return NULL;
        id.hwnd = hwnd;
        flags = WGL_DC_OBJ_DC;
    }
    else if(objType == OBJ_MEMDC)
    {
        id.hdc = hdc;
    }
    else
    {
        return NULL;
    }

    EnterCriticalSection(&dc_data_cs);
    data = dc_data_list;
    while(data)
    {
        if(data->owner.u == id.u)
        {
            LeaveCriticalSection(&dc_data_cs);
            return data;
        }
        data = data->next;
    }
    data= HeapAlloc(GetProcessHeap(), 0, sizeof(*data));
    if(!data)
    {
        LeaveCriticalSection(&dc_data_cs);
        return NULL;
    }
    /* initialize the structure */
    data->owner.u = id.u;
    data->flags = flags;
    data->pixelformat = 0;
    data->sw_data = NULL;
    /* Load the driver */
    data->icd_data = IntGetIcdData(hdc);
    /* Get the number of available formats for this DC once and for all */
    if(data->icd_data)
        data->nb_icd_formats = data->icd_data->DrvDescribePixelFormat(hdc, format, size, descr);
    else
        data->nb_icd_formats = 0;
    TRACE("ICD %S has %u formats for HDC %x.\n", data->icd_data ? data->icd_data->DriverName : NULL, data->nb_icd_formats, hdc);
    data->nb_sw_formats = sw_DescribePixelFormat(hdc, 0, 0, NULL);
    data->next = dc_data_list;
    dc_data_list = data;
    LeaveCriticalSection(&dc_data_cs);
    return data;
}