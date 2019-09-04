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
typedef  int BOOL ;

/* Variables and functions */
 int FILE_TEST ; 
 int FTP_TEST ; 
 int HTTPS_TEST ; 
 int HTTP_TEST ; 
 int MK_TEST ; 

__attribute__((used)) static BOOL is_urlmon_protocol(int prot)
{
    return prot == FILE_TEST || prot == HTTP_TEST || prot == HTTPS_TEST || prot == FTP_TEST || prot == MK_TEST;
}