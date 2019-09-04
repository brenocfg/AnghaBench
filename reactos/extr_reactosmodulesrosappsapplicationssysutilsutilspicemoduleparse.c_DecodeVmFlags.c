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
typedef  int /*<<< orphan*/  ULONG ;
typedef  char* LPSTR ;

/* Variables and functions */

LPSTR DecodeVmFlags(ULONG flags)
{
    ULONG i;
/*
#define VM_READ		0x0001
#define VM_WRITE	0x0002
#define VM_EXEC		0x0004
#define VM_SHARED	0x0008

#define VM_MAYREAD	0x0010
#define VM_MAYWRITE	0x0020
#define VM_MAYEXEC	0x0040
#define VM_MAYSHARE	0x0080

#define VM_GROWSDOWN	0x0100
#define VM_GROWSUP	0x0200
#define VM_SHM		0x0400
#define VM_DENYWRITE	0x0800

#define VM_EXECUTABLE	0x1000
#define VM_LOCKED	0x2000
#define VM_IO           0x4000

#define VM_STACK_FLAGS	0x0177
*/
    static LPSTR flags_syms_on[]={"R","W","X","S","MR","MW","MX","MS","GD","GU","SHM","exe","LOCK","IO",""};
    static char temp[256];

	// terminate string
    *temp = 0;
//ei fix fix fix
#if 0

    if(flags == VM_STACK_FLAGS)
    {
        PICE_strcpy(temp," (STACK)");
    }
    else
    {
        for(i=0;i<15;i++)
        {
            if(flags&0x1)
            {
                PICE_strcat(temp," ");
                PICE_strcat(temp,flags_syms_on[i]);
            }
            flags >>= 1;
        }
    }
#endif
    return temp;
}