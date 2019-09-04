#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_19__ ;

/* Type definitions */
struct inode {int i_ino; int i_mode; int /*<<< orphan*/  i_flags; scalar_t__ i_extra_isize; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/ * i_sb; int /*<<< orphan*/  member_0; } ;
struct ext3_super_block {int /*<<< orphan*/  s_want_extra_isize; } ;
struct dentry {int dummy; } ;
typedef  int ULONG ;
struct TYPE_28__ {int /*<<< orphan*/  s_feature_incompat; } ;
struct TYPE_27__ {TYPE_4__* Inode; TYPE_3__* Mcb; } ;
struct TYPE_26__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  Flags; int /*<<< orphan*/  sb; } ;
struct TYPE_25__ {int /*<<< orphan*/  Buffer; } ;
struct TYPE_24__ {int i_ino; int i_mode; int /*<<< orphan*/  i_generation; } ;
struct TYPE_22__ {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct TYPE_21__ {int /*<<< orphan*/  Buffer; } ;
struct TYPE_23__ {TYPE_2__ Inode; TYPE_1__ ShortName; } ;
struct TYPE_20__ {struct ext3_super_block* s_es; } ;
typedef  TYPE_5__* PUNICODE_STRING ;
typedef  TYPE_6__* PEXT2_VCB ;
typedef  int /*<<< orphan*/  PEXT2_IRP_CONTEXT ;
typedef  TYPE_7__* PEXT2_FCB ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;

/* Variables and functions */
 int BLOCKS_PER_GROUP ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DL_INF ; 
 int /*<<< orphan*/  DbgBreak () ; 
 int /*<<< orphan*/  EXT2_EXTENTS_FL ; 
 int EXT2_FT_DIR ; 
 int EXT2_FT_REG_FILE ; 
 TYPE_19__* EXT3_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXT4_FEATURE_INCOMPAT_EXTENTS ; 
 int /*<<< orphan*/  Ext2AddEntry (int /*<<< orphan*/ ,TYPE_6__*,TYPE_7__*,struct inode*,TYPE_5__*,struct dentry**) ; 
 int /*<<< orphan*/  Ext2ClearInode (int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 int /*<<< orphan*/  Ext2FreeEntry (struct dentry*) ; 
 int /*<<< orphan*/  Ext2FreeInode (int /*<<< orphan*/ ,TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  Ext2LinuxTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ext2NewInode (int /*<<< orphan*/ ,TYPE_6__*,int,int,int*) ; 
 int /*<<< orphan*/  Ext2SaveInode (int /*<<< orphan*/ ,TYPE_6__*,struct inode*) ; 
 scalar_t__ IsFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeQuerySystemTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 TYPE_8__* SUPER_BLOCK ; 
 int S_IFATTR ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int S_IPERMISSION_MASK ; 
 int /*<<< orphan*/  VCB_USER_IDS ; 
 int /*<<< orphan*/  ext4_ext_tree_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

NTSTATUS
Ext2CreateInode(
    PEXT2_IRP_CONTEXT   IrpContext,
    PEXT2_VCB           Vcb,
    PEXT2_FCB           Parent,
    ULONG               Type,
    ULONG               FileAttr,
    PUNICODE_STRING     FileName)
{
    NTSTATUS    Status;
    ULONG       iGrp;
    ULONG       iNo;
    struct inode Inode = { 0 };
    struct dentry *Dentry = NULL;
	struct ext3_super_block *es = EXT3_SB(&Vcb->sb)->s_es;

    LARGE_INTEGER   SysTime;

    iGrp = (Parent->Inode->i_ino - 1) / BLOCKS_PER_GROUP;

    DEBUG(DL_INF, ("Ext2CreateInode: %S in %S(Inode=%xh)\n",
                   FileName->Buffer,
                   Parent->Mcb->ShortName.Buffer,
                   Parent->Inode->i_ino));

    Status = Ext2NewInode(IrpContext, Vcb, iGrp, Type, &iNo);
    if (!NT_SUCCESS(Status)) {
        goto errorout;
    }

    KeQuerySystemTime(&SysTime);
    Ext2ClearInode(IrpContext, Vcb, iNo);
    Inode.i_sb = &Vcb->sb;
    Inode.i_ino = iNo;
    Inode.i_ctime = Inode.i_mtime =
    Inode.i_atime = Ext2LinuxTime(SysTime);
    if (IsFlagOn(Vcb->Flags, VCB_USER_IDS)) {
        Inode.i_uid = Vcb->uid;
        Inode.i_gid = Vcb->gid;
    } else {
        Inode.i_uid = Parent->Mcb->Inode.i_uid;
        Inode.i_gid = Parent->Mcb->Inode.i_gid;
    }
    Inode.i_generation = Parent->Inode->i_generation;
    Inode.i_mode = S_IPERMISSION_MASK &
                   Parent->Inode->i_mode;
    if (Type == EXT2_FT_DIR)  {
        Inode.i_mode |= S_IFDIR;
    } else if (Type == EXT2_FT_REG_FILE) {
        Inode.i_mode &= S_IFATTR;
        Inode.i_mode |= S_IFREG;
    } else {
        DbgBreak();
    }
	if (le16_to_cpu(es->s_want_extra_isize))
		Inode.i_extra_isize = le16_to_cpu(es->s_want_extra_isize);

    /* Force using extent */
    if (IsFlagOn(SUPER_BLOCK->s_feature_incompat, EXT4_FEATURE_INCOMPAT_EXTENTS)) {
        Inode.i_flags |= EXT2_EXTENTS_FL;
        ext4_ext_tree_init(IrpContext, NULL, &Inode);
        /* ext4_ext_tree_init will save inode body */
    } else {
        /* save inode body to cache */
        Ext2SaveInode(IrpContext, Vcb, &Inode);
    }

    /* add new entry to its parent */
    Status = Ext2AddEntry(
                 IrpContext,
                 Vcb,
                 Parent,
                 &Inode,
                 FileName,
                 &Dentry
             );

    if (!NT_SUCCESS(Status)) {
        DbgBreak();
        Ext2FreeInode(IrpContext, Vcb, iNo, Type);
        goto errorout;
    }

    DEBUG(DL_INF, ("Ext2CreateInode: New Inode = %xh (Type=%xh)\n",
                   Inode.i_ino, Type));

errorout:

    if (Dentry)
        Ext2FreeEntry(Dentry);

    return Status;
}