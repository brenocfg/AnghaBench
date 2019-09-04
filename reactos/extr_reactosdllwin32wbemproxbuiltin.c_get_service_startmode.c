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
typedef  char WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  SERVICE_AUTO_START 132 
#define  SERVICE_BOOT_START 131 
#define  SERVICE_DEMAND_START 130 
#define  SERVICE_DISABLED 129 
#define  SERVICE_SYSTEM_START 128 

__attribute__((used)) static const WCHAR *get_service_startmode( DWORD mode )
{
    static const WCHAR bootW[] = {'B','o','o','t',0};
    static const WCHAR systemW[] = {'S','y','s','t','e','m',0};
    static const WCHAR autoW[] = {'A','u','t','o',0};
    static const WCHAR manualW[] = {'M','a','n','u','a','l',0};
    static const WCHAR disabledW[] = {'D','i','s','a','b','l','e','d',0};
    static const WCHAR unknownW[] = {'U','n','k','n','o','w','n',0};

    switch (mode)
    {
    case SERVICE_BOOT_START:   return bootW;
    case SERVICE_SYSTEM_START: return systemW;
    case SERVICE_AUTO_START:   return autoW;
    case SERVICE_DEMAND_START: return manualW;
    case SERVICE_DISABLED:     return disabledW;
    default:
        ERR("unknown mode 0x%x\n", mode);
        return unknownW;
    }
}