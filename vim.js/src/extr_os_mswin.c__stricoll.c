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

/* Variables and functions */
 int strcoll (char*,char*) ; 
 int /*<<< orphan*/  strxfrm (char*,char*,int) ; 

int _stricoll(char *a, char *b)
{
    // the ANSI-ish correct way is to use strxfrm():
    char a_buff[512], b_buff[512];  // file names, so this is enough on Win32
    strxfrm(a_buff, a, 512);
    strxfrm(b_buff, b, 512);
    return strcoll(a_buff, b_buff);
}