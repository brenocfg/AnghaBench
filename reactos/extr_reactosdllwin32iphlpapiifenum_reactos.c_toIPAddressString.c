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
struct in_addr {unsigned int s_addr; } ;

/* Variables and functions */
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

char *toIPAddressString(unsigned int addr, char string[16])
{
    struct in_addr iAddr;

    iAddr.s_addr = addr;

    if (string)
        strncpy(string, inet_ntoa(iAddr), 16);

    return inet_ntoa(iAddr);
}