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
struct TYPE_3__ {int /*<<< orphan*/  wVersion; } ;
typedef  TYPE_1__ WSADATA ;

/* Variables and functions */
 int HIBYTE (int /*<<< orphan*/ ) ; 
 int LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  WSACleanup () ; 
 scalar_t__ WSAStartup (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int system_InitWSA(int hi, int lo)
{
    WSADATA data;

    if (WSAStartup(MAKEWORD(hi, lo), &data) == 0)
    {
        if (LOBYTE(data.wVersion) == 2 && HIBYTE(data.wVersion) == 2)
            return 0;
        /* Winsock DLL is not usable */
        WSACleanup( );
    }
    return -1;
}