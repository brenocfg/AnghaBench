#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  hparent; int /*<<< orphan*/  hvideownd; } ;
typedef  TYPE_2__ vout_display_sys_win32_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_22__ {TYPE_1__* lpVtbl; } ;
struct TYPE_21__ {int dwOSVersionInfoSize; int dwMajorVersion; } ;
struct TYPE_20__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {int /*<<< orphan*/  top; scalar_t__ bottom; int /*<<< orphan*/  left; scalar_t__ right; } ;
struct TYPE_17__ {scalar_t__ (* SetThumbnailClip ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_3__*) ;int /*<<< orphan*/  (* Release ) (TYPE_6__*) ;int /*<<< orphan*/  (* HrInit ) (TYPE_6__*) ;} ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__ POINT ;
typedef  TYPE_5__ OSVERSIONINFO ;
typedef  TYPE_6__ ITaskbarList3 ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_TaskbarList ; 
 int /*<<< orphan*/  COINIT_MULTITHREADED ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GA_ROOT ; 
 int /*<<< orphan*/  GetAncestor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetVersionEx (TYPE_5__*) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IID_ITaskbarList3 ; 
 unsigned int RECTHeight (TYPE_3__) ; 
 unsigned int RECTWidth (TYPE_3__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ ScreenToClient (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 scalar_t__ stub2 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static void CommonChangeThumbnailClip(vlc_object_t *obj, vout_display_sys_win32_t *sys, bool show)
{
    /* Windows 7 taskbar thumbnail code */
    OSVERSIONINFO winVer;
    winVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (!GetVersionEx(&winVer) || winVer.dwMajorVersion <= 5)
        return;

    if( FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED)) )
        vlc_assert_unreachable();

    void *ptr;
    if (S_OK == CoCreateInstance(&CLSID_TaskbarList,
                                 NULL, CLSCTX_INPROC_SERVER,
                                 &IID_ITaskbarList3,
                                 &ptr)) {
        ITaskbarList3 *taskbl = ptr;
        taskbl->lpVtbl->HrInit(taskbl);

        HWND hroot = GetAncestor(sys->hvideownd, GA_ROOT);
        RECT video;
        if (show) {
            GetWindowRect(sys->hparent, &video);
            POINT client = {video.left, video.top};
            if (ScreenToClient(hroot, &client))
            {
                unsigned int width = RECTWidth(video);
                unsigned int height = RECTHeight(video);
                video.left = client.x;
                video.top = client.y;
                video.right = video.left + width;
                video.bottom = video.top + height;
            }
        }
        HRESULT hr;
        hr = taskbl->lpVtbl->SetThumbnailClip(taskbl, hroot,
                                                 show ? &video : NULL);
        if ( hr != S_OK )
            msg_Err(obj, "SetThumbNailClip failed: 0x%lX", hr);

        taskbl->lpVtbl->Release(taskbl);
    }
    CoUninitialize();
}