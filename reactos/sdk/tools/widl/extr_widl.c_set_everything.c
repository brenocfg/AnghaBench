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
 int do_client ; 
 int do_dlldata ; 
 int do_header ; 
 int do_idfile ; 
 int do_old_typelib ; 
 int do_proxies ; 
 int do_regscript ; 
 int do_server ; 
 int do_typelib ; 

__attribute__((used)) static void set_everything(int x)
{
  do_header = x;
  do_typelib = x;
  do_old_typelib = x;
  do_proxies = x;
  do_client = x;
  do_server = x;
  do_regscript = x;
  do_idfile = x;
  do_dlldata = x;
}