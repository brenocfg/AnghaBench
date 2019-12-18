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
 int /*<<< orphan*/  register_fstype (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_fstype ; 
 int /*<<< orphan*/  smb_shareops ; 

void
libshare_smb_init(void)
{
	smb_fstype = register_fstype("smb", &smb_shareops);
}