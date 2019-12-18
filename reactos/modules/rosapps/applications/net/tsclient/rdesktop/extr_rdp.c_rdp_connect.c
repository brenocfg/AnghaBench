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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  rdp_send_logon_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*) ; 

BOOL
rdp_connect(RDPCLIENT * This, char *server, uint32 flags, wchar_t *username, wchar_t *domain, wchar_t *password,
	    wchar_t *command, wchar_t *directory, wchar_t *hostname, char *cookie)
{
	if (!sec_connect(This, server, hostname, cookie))
		return False;

	rdp_send_logon_info(This, flags, domain, username, password, command, directory);
	return True;
}