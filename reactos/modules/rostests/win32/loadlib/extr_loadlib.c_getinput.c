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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  InputHandle ; 
 int /*<<< orphan*/  ReadConsoleA (int /*<<< orphan*/ ,char*,int,scalar_t__*,int /*<<< orphan*/ *) ; 

long getinput(char* buf, int buflen)
{
    DWORD result;

    ReadConsoleA(InputHandle, buf, buflen, &result, NULL);
    return (long)result;
}