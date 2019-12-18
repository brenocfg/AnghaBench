#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drr_object_range {int /*<<< orphan*/  drr_flags; int /*<<< orphan*/  drr_numslots; int /*<<< orphan*/  drr_firstobj; } ;
struct drr_spill {int /*<<< orphan*/  drr_length; int /*<<< orphan*/  drr_object; } ;
struct drr_free {int /*<<< orphan*/  drr_length; int /*<<< orphan*/  drr_offset; int /*<<< orphan*/  drr_object; } ;
struct drr_write_embedded {int /*<<< orphan*/  drr_psize; int /*<<< orphan*/  drr_lsize; int /*<<< orphan*/  drr_etype; int /*<<< orphan*/  drr_compression; int /*<<< orphan*/  drr_length; int /*<<< orphan*/  drr_offset; int /*<<< orphan*/  drr_object; } ;
struct drr_write_byref {int /*<<< orphan*/  drr_flags; int /*<<< orphan*/  drr_checksumtype; int /*<<< orphan*/  drr_refoffset; int /*<<< orphan*/  drr_refobject; int /*<<< orphan*/  drr_refguid; int /*<<< orphan*/  drr_toguid; int /*<<< orphan*/  drr_length; int /*<<< orphan*/  drr_offset; int /*<<< orphan*/  drr_object; } ;
struct drr_write {int /*<<< orphan*/  drr_compressed_size; int /*<<< orphan*/  drr_compressiontype; int /*<<< orphan*/  drr_flags; int /*<<< orphan*/  drr_checksumtype; int /*<<< orphan*/  drr_logical_size; int /*<<< orphan*/  drr_offset; int /*<<< orphan*/  drr_type; int /*<<< orphan*/  drr_object; } ;
struct drr_freeobjects {int /*<<< orphan*/  drr_numobjs; int /*<<< orphan*/  drr_firstobj; } ;
struct drr_object {int /*<<< orphan*/  drr_dn_slots; int /*<<< orphan*/  drr_compress; int /*<<< orphan*/  drr_checksumtype; int /*<<< orphan*/  drr_bonuslen; int /*<<< orphan*/  drr_blksz; int /*<<< orphan*/  drr_bonustype; int /*<<< orphan*/  drr_type; int /*<<< orphan*/  drr_object; } ;
struct TYPE_3__ {struct drr_object_range drr_object_range; struct drr_spill drr_spill; struct drr_free drr_free; struct drr_write_embedded drr_write_embedded; struct drr_write_byref drr_write_byref; struct drr_write drr_write; struct drr_freeobjects drr_freeobjects; struct drr_object drr_object; } ;
struct TYPE_4__ {int drr_type; TYPE_1__ drr_u; } ;
struct receive_record_arg {TYPE_2__ header; } ;

/* Variables and functions */
#define  DRR_FREE 135 
#define  DRR_FREEOBJECTS 134 
#define  DRR_OBJECT 133 
#define  DRR_OBJECT_RANGE 132 
#define  DRR_SPILL 131 
#define  DRR_WRITE 130 
#define  DRR_WRITE_BYREF 129 
#define  DRR_WRITE_EMBEDDED 128 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static void
dprintf_drr(struct receive_record_arg *rrd, int err)
{
#ifdef ZFS_DEBUG
	switch (rrd->header.drr_type) {
	case DRR_OBJECT:
	{
		struct drr_object *drro = &rrd->header.drr_u.drr_object;
		dprintf("drr_type = OBJECT obj = %llu type = %u "
		    "bonustype = %u blksz = %u bonuslen = %u cksumtype = %u "
		    "compress = %u dn_slots = %u err = %d\n",
		    drro->drr_object, drro->drr_type,  drro->drr_bonustype,
		    drro->drr_blksz, drro->drr_bonuslen,
		    drro->drr_checksumtype, drro->drr_compress,
		    drro->drr_dn_slots, err);
		break;
	}
	case DRR_FREEOBJECTS:
	{
		struct drr_freeobjects *drrfo =
		    &rrd->header.drr_u.drr_freeobjects;
		dprintf("drr_type = FREEOBJECTS firstobj = %llu "
		    "numobjs = %llu err = %d\n",
		    drrfo->drr_firstobj, drrfo->drr_numobjs, err);
		break;
	}
	case DRR_WRITE:
	{
		struct drr_write *drrw = &rrd->header.drr_u.drr_write;
		dprintf("drr_type = WRITE obj = %llu type = %u offset = %llu "
		    "lsize = %llu cksumtype = %u flags = %u "
		    "compress = %u psize = %llu err = %d\n",
		    drrw->drr_object, drrw->drr_type, drrw->drr_offset,
		    drrw->drr_logical_size, drrw->drr_checksumtype,
		    drrw->drr_flags, drrw->drr_compressiontype,
		    drrw->drr_compressed_size, err);
		break;
	}
	case DRR_WRITE_BYREF:
	{
		struct drr_write_byref *drrwbr =
		    &rrd->header.drr_u.drr_write_byref;
		dprintf("drr_type = WRITE_BYREF obj = %llu offset = %llu "
		    "length = %llu toguid = %llx refguid = %llx "
		    "refobject = %llu refoffset = %llu cksumtype = %u "
		    "flags = %u err = %d\n",
		    drrwbr->drr_object, drrwbr->drr_offset,
		    drrwbr->drr_length, drrwbr->drr_toguid,
		    drrwbr->drr_refguid, drrwbr->drr_refobject,
		    drrwbr->drr_refoffset, drrwbr->drr_checksumtype,
		    drrwbr->drr_flags, err);
		break;
	}
	case DRR_WRITE_EMBEDDED:
	{
		struct drr_write_embedded *drrwe =
		    &rrd->header.drr_u.drr_write_embedded;
		dprintf("drr_type = WRITE_EMBEDDED obj = %llu offset = %llu "
		    "length = %llu compress = %u etype = %u lsize = %u "
		    "psize = %u err = %d\n",
		    drrwe->drr_object, drrwe->drr_offset, drrwe->drr_length,
		    drrwe->drr_compression, drrwe->drr_etype,
		    drrwe->drr_lsize, drrwe->drr_psize, err);
		break;
	}
	case DRR_FREE:
	{
		struct drr_free *drrf = &rrd->header.drr_u.drr_free;
		dprintf("drr_type = FREE obj = %llu offset = %llu "
		    "length = %lld err = %d\n",
		    drrf->drr_object, drrf->drr_offset, drrf->drr_length,
		    err);
		break;
	}
	case DRR_SPILL:
	{
		struct drr_spill *drrs = &rrd->header.drr_u.drr_spill;
		dprintf("drr_type = SPILL obj = %llu length = %llu "
		    "err = %d\n", drrs->drr_object, drrs->drr_length, err);
		break;
	}
	case DRR_OBJECT_RANGE:
	{
		struct drr_object_range *drror =
		    &rrd->header.drr_u.drr_object_range;
		dprintf("drr_type = OBJECT_RANGE firstobj = %llu "
		    "numslots = %llu flags = %u err = %d\n",
		    drror->drr_firstobj, drror->drr_numslots,
		    drror->drr_flags, err);
		break;
	}
	default:
		return;
	}
#endif
}