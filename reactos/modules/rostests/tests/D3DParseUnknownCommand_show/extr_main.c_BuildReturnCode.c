#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_2__ {int bCommand; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int INT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ D3DHAL_DP2COMMAND ;

/* Variables and functions */
 scalar_t__ D3DParseUnknownCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

VOID BuildReturnCode(DWORD * ReturnCode)
{
    INT t;
    D3DHAL_DP2COMMAND dp2command;
    DWORD lplpvReturnedCommand[2];

    for (t=0;t<256;t++)
    {
       dp2command.bCommand = t;
       ReturnCode[t] = D3DParseUnknownCommand ( (LPVOID) &dp2command, (LPVOID *) lplpvReturnedCommand) ;
       printf("D3DParseUnknownCommand return code = %x command %d \n", (UINT)ReturnCode[t], t);
    }
}