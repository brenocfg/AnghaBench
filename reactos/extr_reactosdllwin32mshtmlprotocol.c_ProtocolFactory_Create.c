#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  IInternetProtocolInfo_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  REFCLSID ;
typedef  TYPE_1__ ProtocolFactory ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 TYPE_1__ AboutProtocolFactory ; 
 int /*<<< orphan*/  CLASS_E_CLASSNOTAVAILABLE ; 
 int /*<<< orphan*/  CLSID_AboutProtocol ; 
 int /*<<< orphan*/  CLSID_JSProtocol ; 
 int /*<<< orphan*/  CLSID_ResProtocol ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IInternetProtocolInfo_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ JSProtocolFactory ; 
 TYPE_1__ ResProtocolFactory ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

HRESULT ProtocolFactory_Create(REFCLSID rclsid, REFIID riid, void **ppv)
{
    ProtocolFactory *cf = NULL;

    if(IsEqualGUID(&CLSID_AboutProtocol, rclsid))
        cf = &AboutProtocolFactory;
    else if(IsEqualGUID(&CLSID_ResProtocol, rclsid))
        cf = &ResProtocolFactory;
    else if(IsEqualGUID(&CLSID_JSProtocol, rclsid))
        cf = &JSProtocolFactory;

    if(!cf) {
        FIXME("not implemented protocol %s\n", debugstr_guid(rclsid));
        return CLASS_E_CLASSNOTAVAILABLE;
    }
 
    return IInternetProtocolInfo_QueryInterface(&cf->IInternetProtocolInfo_iface, riid, ppv);
}