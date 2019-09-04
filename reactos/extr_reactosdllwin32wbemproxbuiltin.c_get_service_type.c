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
typedef  float WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int SERVICE_FILE_SYSTEM_DRIVER ; 
 int SERVICE_KERNEL_DRIVER ; 
 int SERVICE_WIN32_OWN_PROCESS ; 
 int SERVICE_WIN32_SHARE_PROCESS ; 

__attribute__((used)) static const WCHAR *get_service_type( DWORD type )
{
    static const WCHAR filesystem_driverW[] =
        {'F','i','l','e',' ','S','y','s','t','e','m',' ','D','r','i','v','e','r',0};
    static const WCHAR kernel_driverW[] =
        {'K','e','r','n','e','l',' ','D','r','i','v','e','r',0};
    static const WCHAR own_processW[] =
        {'O','w','n',' ','P','r','o','c','e','s','s',0};
    static const WCHAR share_processW[] =
        {'S','h','a','r','e',' ','P','r','o','c','e','s','s',0};

    if (type & SERVICE_KERNEL_DRIVER)            return kernel_driverW;
    else if (type & SERVICE_FILE_SYSTEM_DRIVER)  return filesystem_driverW;
    else if (type & SERVICE_WIN32_OWN_PROCESS)   return own_processW;
    else if (type & SERVICE_WIN32_SHARE_PROCESS) return share_processW;
    else ERR("unhandled type 0x%08x\n", type);
    return NULL;
}