#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smb2_context {int dummy; } ;
struct TYPE_2__ {void* smb2fh; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_SMB2_GENERIC_CB () ; 
 TYPE_1__* sys ; 

__attribute__((used)) static void
smb2_open_cb(struct smb2_context *smb2, int status, void *data,
             void *private_data)
{
    VLC_SMB2_GENERIC_CB();

    sys->smb2fh = data;
}