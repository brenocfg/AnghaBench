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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_DSoundRender ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * pDSRender ; 

__attribute__((used)) static BOOL create_dsound_renderer(void)
{
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_DSoundRender, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IUnknown, (LPVOID*)&pDSRender);
    return (hr == S_OK && pDSRender != NULL);
}