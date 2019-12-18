#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ decrypt_use_count; scalar_t__ encrypt_use_count; } ;
struct TYPE_6__ {TYPE_1__ secure; scalar_t__ server_rdp_version; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  mcs_reset_state (TYPE_2__*) ; 

void
sec_reset_state(RDPCLIENT * This)
{
	This->server_rdp_version = 0;
	This->secure.encrypt_use_count = 0;
	This->secure.decrypt_use_count = 0;
	mcs_reset_state(This);
}