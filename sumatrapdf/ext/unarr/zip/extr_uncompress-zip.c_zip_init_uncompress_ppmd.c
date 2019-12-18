#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* In; } ;
struct TYPE_17__ {TYPE_2__ Stream; } ;
struct TYPE_12__ {int /*<<< orphan*/  Read; } ;
struct TYPE_13__ {TYPE_3__ super; TYPE_7__* zip; int /*<<< orphan*/ * input; } ;
struct TYPE_10__ {int /*<<< orphan*/  Free; int /*<<< orphan*/  Alloc; } ;
struct TYPE_14__ {TYPE_9__ ctx; TYPE_4__ bytein; TYPE_1__ alloc; } ;
struct TYPE_15__ {TYPE_5__ ppmd8; } ;
struct ar_archive_zip_uncomp {TYPE_6__ state; int /*<<< orphan*/  input; } ;
struct TYPE_16__ {struct ar_archive_zip_uncomp uncomp; } ;
typedef  TYPE_7__ ar_archive_zip ;

/* Variables and functions */
 int /*<<< orphan*/  Ppmd8_Construct (TYPE_9__*) ; 
 int /*<<< orphan*/  gPpmd_Alloc ; 
 int /*<<< orphan*/  gPpmd_ByteIn_Read ; 
 int /*<<< orphan*/  gPpmd_Free ; 

__attribute__((used)) static bool zip_init_uncompress_ppmd(ar_archive_zip *zip)
{
    struct ar_archive_zip_uncomp *uncomp = &zip->uncomp;
    uncomp->state.ppmd8.alloc.Alloc = gPpmd_Alloc;
    uncomp->state.ppmd8.alloc.Free = gPpmd_Free;
    uncomp->state.ppmd8.bytein.super.Read = gPpmd_ByteIn_Read;
    uncomp->state.ppmd8.bytein.input = &uncomp->input;
    uncomp->state.ppmd8.bytein.zip = zip;
    uncomp->state.ppmd8.ctx.Stream.In = &uncomp->state.ppmd8.bytein.super;
    Ppmd8_Construct(&uncomp->state.ppmd8.ctx);
    return true;
}