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
 int /*<<< orphan*/  abort_import () ; 
 scalar_t__ client_name ; 
 scalar_t__ do_client ; 
 scalar_t__ do_header ; 
 scalar_t__ do_idfile ; 
 scalar_t__ do_proxies ; 
 scalar_t__ do_regscript ; 
 scalar_t__ do_server ; 
 scalar_t__ do_typelib ; 
 scalar_t__ header_name ; 
 scalar_t__ idfile_name ; 
 scalar_t__ local_stubs_name ; 
 scalar_t__ proxy_name ; 
 scalar_t__ regscript_name ; 
 scalar_t__ server_name ; 
 scalar_t__ temp_name ; 
 scalar_t__ typelib_name ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 

__attribute__((used)) static void rm_tempfile(void)
{
  abort_import();
  if(temp_name)
    unlink(temp_name);
  if (do_header)
    unlink(header_name);
  if (local_stubs_name)
    unlink(local_stubs_name);
  if (do_client)
    unlink(client_name);
  if (do_server)
    unlink(server_name);
  if (do_regscript)
    unlink(regscript_name);
  if (do_idfile)
    unlink(idfile_name);
  if (do_proxies)
    unlink(proxy_name);
  if (do_typelib)
    unlink(typelib_name);
}