#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fmtW ;
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  Revision; int /*<<< orphan*/  SubSysId; int /*<<< orphan*/  DeviceId; int /*<<< orphan*/  VendorId; } ;
typedef  TYPE_1__ DXGI_ADAPTER_DESC ;

/* Variables and functions */
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *get_pnpdeviceid( DXGI_ADAPTER_DESC *desc )
{
    static const WCHAR fmtW[] =
        {'P','C','I','\\','V','E','N','_','%','0','4','X','&','D','E','V','_','%','0','4','X',
         '&','S','U','B','S','Y','S','_','%','0','8','X','&','R','E','V','_','%','0','2','X','\\',
         '0','&','D','E','A','D','B','E','E','F','&','0','&','D','E','A','D',0};
    WCHAR *ret;

    if (!(ret = heap_alloc( sizeof(fmtW) + 2 * sizeof(WCHAR) ))) return NULL;
    sprintfW( ret, fmtW, desc->VendorId, desc->DeviceId, desc->SubSysId, desc->Revision );
    return ret;
}