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
struct TYPE_3__ {int server_rdp_version; int server_depth; scalar_t__ use_rdp5; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sec_process_srv_info(RDPCLIENT * This, STREAM s)
{
	in_uint16_le(s, This->server_rdp_version);
	DEBUG_RDP5(("Server RDP version is %d\n", This->server_rdp_version));
	if (1 == This->server_rdp_version)
	{
		This->use_rdp5 = 0;
		This->server_depth = 8;
	}
}