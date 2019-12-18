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
typedef  int /*<<< orphan*/  ddsd ;
struct TYPE_5__ {int /*<<< orphan*/  dwCaps; } ;
struct TYPE_6__ {int dwSize; TYPE_1__ ddsCaps; int /*<<< orphan*/  dwFlags; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IDirectDraw ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_2__ DDSURFACEDESC2 ;

/* Variables and functions */
 int /*<<< orphan*/  DDSCAPS_PRIMARYSURFACE ; 
 int /*<<< orphan*/  DDSCL_NORMAL ; 
 int /*<<< orphan*/  DDSD_CAPS ; 
 scalar_t__ DD_OK ; 
 scalar_t__ DirectDrawCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 scalar_t__ IDirectDraw7_CreateSurface (scalar_t__,TYPE_2__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectDraw7_Release (scalar_t__) ; 
 scalar_t__ IDirectDraw7_SetCooperativeLevel (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectDrawSurface7_Release (scalar_t__) ; 
 scalar_t__ IDirectDraw_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectDraw_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirectDraw7 ; 
 int TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pdd7 ; 
 scalar_t__ pdds7 ; 

__attribute__((used)) static int create_directdraw(void)
{
    HRESULT hr;
    IDirectDraw* pdd = NULL;
    DDSURFACEDESC2 ddsd;

    hr = DirectDrawCreate(NULL, &pdd, NULL);
    ok(hr==DD_OK, "DirectDrawCreate returned: %x\n", hr);
    if (hr != DD_OK)
       goto error;

    hr = IDirectDraw_QueryInterface(pdd, &IID_IDirectDraw7, (LPVOID*)&pdd7);
    ok(hr==DD_OK, "QueryInterface returned: %x\n", hr);
    if (hr != DD_OK) goto error;

    hr = IDirectDraw7_SetCooperativeLevel(pdd7, GetDesktopWindow(), DDSCL_NORMAL);
    ok(hr==DD_OK, "SetCooperativeLevel returned: %x\n", hr);

    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    hr = IDirectDraw7_CreateSurface(pdd7, &ddsd, &pdds7, NULL);
    ok(hr==DD_OK, "CreateSurface returned: %x\n", hr);

    return TRUE;

error:
    if (pdds7)
        IDirectDrawSurface7_Release(pdds7);
    if (pdd7)
        IDirectDraw7_Release(pdd7);
    if (pdd)
        IDirectDraw_Release(pdd);

    return FALSE;
}