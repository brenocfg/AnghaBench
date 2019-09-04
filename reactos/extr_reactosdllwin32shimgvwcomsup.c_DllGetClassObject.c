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
typedef  int /*<<< orphan*/  STDAPI ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  REFCLSID ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_CLASSNOTAVAILABLE ; 

STDAPI
DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
    HRESULT hr;

    /* There are no classes to export, so always return CLASS_E_CLASSNOTAVAILABLE*/
    *ppv = NULL;
    hr = CLASS_E_CLASSNOTAVAILABLE;

    return hr;
}