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
struct TYPE_3__ {int dwSize; scalar_t__ UnlockD3DBuffer; scalar_t__ LockD3DBuffer; scalar_t__ DestroyD3DBuffer; scalar_t__ CreateD3DBuffer; scalar_t__ CanCreateD3DBuffer; int /*<<< orphan*/  dwFlags; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DD_D3DBUFCALLBACKS ;

/* Variables and functions */
 int /*<<< orphan*/  DDHAL_D3DBUFCB32_CANCREATED3DBUF ; 
 int /*<<< orphan*/  DDHAL_D3DBUFCB32_CREATED3DBUF ; 
 int /*<<< orphan*/  DDHAL_D3DBUFCB32_DESTROYD3DBUF ; 
 int /*<<< orphan*/  DDHAL_D3DBUFCB32_LOCKD3DBUF ; 
 int /*<<< orphan*/  DDHAL_D3DBUFCB32_UNLOCKD3DBUF ; 
 int /*<<< orphan*/  checkflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  endcheckflag (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
dump_D3dBufferCallbacks(DD_D3DBUFCALLBACKS *puD3dBufferCallbacks, char *text)
{
    int count = 0;
    DWORD flag = 0;

    printf("dumping the DD_D3DBUFCALLBACKS from %s\n",text);

    if (puD3dBufferCallbacks->dwSize == sizeof(DD_D3DBUFCALLBACKS))
    {
        printf(" puD3dBufferCallbacks->dwSize                                   : 0x%08lx\n",(long)puD3dBufferCallbacks->dwSize);
        printf(" puD3dBufferCallbacks->dwFlags                                  : ");

        /* rember this flags are not in msdn only in ms ddk */
        count = 0;
        flag = puD3dBufferCallbacks->dwFlags;
        checkflag(flag,DDHAL_D3DBUFCB32_CANCREATED3DBUF,"DDHAL_D3DBUFCB32_CANCREATED3DBUF");
        checkflag(flag,DDHAL_D3DBUFCB32_CREATED3DBUF,"DDHAL_D3DBUFCB32_CREATED3DBUF");

        checkflag(flag,DDHAL_D3DBUFCB32_DESTROYD3DBUF,"DDHAL_D3DBUFCB32_DESTROYD3DBUF");

        checkflag(flag,DDHAL_D3DBUFCB32_LOCKD3DBUF,"DDHAL_D3DBUFCB32_LOCKD3DBUF");
        checkflag(flag,DDHAL_D3DBUFCB32_UNLOCKD3DBUF,"DDHAL_D3DBUFCB32_UNLOCKD3DBUF");                                
        endcheckflag(flag,"puD3dBufferCallbacks->dwFlags"); 

        printf(" puD3dBufferCallbacks->CanCreateD3DBuffer                       : 0x%08lx\n",(long)puD3dBufferCallbacks->CanCreateD3DBuffer);
        printf(" puD3dBufferCallbacks->CreateD3DBuffer                          : 0x%08lx\n",(long)puD3dBufferCallbacks->CreateD3DBuffer);
        printf(" puD3dBufferCallbacks->DestroyD3DBuffer                         : 0x%08lx\n",(long)puD3dBufferCallbacks->DestroyD3DBuffer);
        printf(" puD3dBufferCallbacks->LockD3DBuffer                            : 0x%08lx\n",(long)puD3dBufferCallbacks->LockD3DBuffer);
        printf(" puD3dBufferCallbacks->UnlockD3DBuffer                          : 0x%08lx\n",(long)puD3dBufferCallbacks->UnlockD3DBuffer);        
    }
    else
    {
        printf("none puD3dBufferCallbacks from the driver 0x%08lx\n",puD3dBufferCallbacks->dwSize);
    }

}