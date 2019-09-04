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
typedef  int SECURITY_INFORMATION ;

/* Variables and functions */
 int DACL_SECURITY_INFORMATION ; 
 int /*<<< orphan*/  DbgP (char*,char*,char*,char*,char*) ; 
 int GROUP_SECURITY_INFORMATION ; 
 int OWNER_SECURITY_INFORMATION ; 
 int SACL_SECURITY_INFORMATION ; 

void print_acl_args(
    SECURITY_INFORMATION info)
{
    DbgP("Security query: %s %s %s\n",
        (info & OWNER_SECURITY_INFORMATION)?"OWNER":"",
        (info & GROUP_SECURITY_INFORMATION)?"GROUP":"",
        (info & DACL_SECURITY_INFORMATION)?"DACL":"",
        (info & SACL_SECURITY_INFORMATION)?"SACL":"");
}