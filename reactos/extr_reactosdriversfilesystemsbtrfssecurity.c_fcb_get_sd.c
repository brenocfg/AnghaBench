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
struct _fcb {int /*<<< orphan*/  sd; } ;
struct TYPE_5__ {int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  sd; TYPE_1__ inode_item; int /*<<< orphan*/  inode; int /*<<< orphan*/  subvol; int /*<<< orphan*/  Vcb; } ;
typedef  TYPE_2__ fcb ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  SECURITY_SUBJECT_CONTEXT ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ BTRFS_TYPE_DIRECTORY ; 
 int /*<<< orphan*/  EA_NTACL ; 
 int /*<<< orphan*/  EA_NTACL_HASH ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IoGetFileObjectGenericMapping () ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlSetGroupSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlSetOwnerSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEF_DACL_AUTO_INHERIT ; 
 int /*<<< orphan*/  SeAssignSecurityEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SeCaptureSubjectContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_top_level_sd (TYPE_2__*) ; 
 scalar_t__ get_xattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_to_sid (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uid_to_sid (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

void fcb_get_sd(fcb* fcb, struct _fcb* parent, BOOL look_for_xattr, PIRP Irp) {
    NTSTATUS Status;
    PSID usersid = NULL, groupsid = NULL;
    SECURITY_SUBJECT_CONTEXT subjcont;
    ULONG buflen;

    if (look_for_xattr && get_xattr(fcb->Vcb, fcb->subvol, fcb->inode, EA_NTACL, EA_NTACL_HASH, (UINT8**)&fcb->sd, (UINT16*)&buflen, Irp))
        return;

    if (!parent) {
        get_top_level_sd(fcb);
        return;
    }

    SeCaptureSubjectContext(&subjcont);

    Status = SeAssignSecurityEx(parent->sd, NULL, (void**)&fcb->sd, NULL, fcb->type == BTRFS_TYPE_DIRECTORY, SEF_DACL_AUTO_INHERIT,
                                &subjcont, IoGetFileObjectGenericMapping(), PagedPool);
    if (!NT_SUCCESS(Status)) {
        ERR("SeAssignSecurityEx returned %08x\n", Status);
    }

    Status = uid_to_sid(fcb->inode_item.st_uid, &usersid);
    if (!NT_SUCCESS(Status)) {
        ERR("uid_to_sid returned %08x\n", Status);
        return;
    }

    RtlSetOwnerSecurityDescriptor(&fcb->sd, usersid, FALSE);

    gid_to_sid(fcb->inode_item.st_gid, &groupsid);
    if (!groupsid) {
        ERR("out of memory\n");
        return;
    }

    RtlSetGroupSecurityDescriptor(&fcb->sd, groupsid, FALSE);

    ExFreePool(usersid);
    ExFreePool(groupsid);
}