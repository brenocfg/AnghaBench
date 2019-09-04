#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ send_dir ;
struct TYPE_10__ {int /*<<< orphan*/  datalen; } ;
typedef  TYPE_2__ send_context ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  BTRFS_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_SEND_CMD_UTIMES ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_ATIME ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_CTIME ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_MTIME ; 
 int /*<<< orphan*/  BTRFS_SEND_TLV_PATH ; 
 int /*<<< orphan*/  send_add_tlv (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  send_add_tlv_path (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_command (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_command_finish (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_utimes_command_dir(send_context* context, send_dir* sd, BTRFS_TIME* atime, BTRFS_TIME* mtime, BTRFS_TIME* ctime) {
    ULONG pos = context->datalen;

    send_command(context, BTRFS_SEND_CMD_UTIMES);

    send_add_tlv_path(context, BTRFS_SEND_TLV_PATH, sd->parent, sd->name, sd->namelen);

    send_add_tlv(context, BTRFS_SEND_TLV_ATIME, atime, sizeof(BTRFS_TIME));
    send_add_tlv(context, BTRFS_SEND_TLV_MTIME, mtime, sizeof(BTRFS_TIME));
    send_add_tlv(context, BTRFS_SEND_TLV_CTIME, ctime, sizeof(BTRFS_TIME));

    send_command_finish(context, pos);
}