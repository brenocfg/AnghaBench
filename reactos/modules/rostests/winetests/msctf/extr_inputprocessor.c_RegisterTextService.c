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
typedef  int /*<<< orphan*/  REFCLSID ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  ClassFactory_Constructor (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoRegisterClassObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REGCLS_MULTIPLEUSE ; 
 int /*<<< orphan*/  TextService_Constructor ; 
 scalar_t__ cf ; 
 int /*<<< orphan*/  regid ; 

__attribute__((used)) static HRESULT RegisterTextService(REFCLSID rclsid)
{
    ClassFactory_Constructor( TextService_Constructor ,(LPVOID*)&cf);
    return CoRegisterClassObject(rclsid, (IUnknown*) cf, CLSCTX_INPROC_SERVER, REGCLS_MULTIPLEUSE, &regid);
}