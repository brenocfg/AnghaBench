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
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  BrowserService ; 
 int /*<<< orphan*/  DocObjectService ; 
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_IBrowserService ; 
 int /*<<< orphan*/  IID_IDocObjectService ; 
 int /*<<< orphan*/  IID_IShellBrowser ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ShellBrowser ; 

__attribute__((used)) static HRESULT browserservice_qi(REFIID riid, void **ppv)
{
    if(IsEqualGUID(&IID_IShellBrowser, riid)) {
        *ppv = &ShellBrowser;
        return S_OK;
    }

    if(IsEqualGUID(&IID_IDocObjectService, riid)) {
        *ppv = &DocObjectService;
        return S_OK;
    }

    if(IsEqualGUID(&IID_IBrowserService, riid)) {
        *ppv = &BrowserService;
        return S_OK;
    }

    *ppv = NULL;
    return E_NOINTERFACE;
}