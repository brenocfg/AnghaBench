#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  size_t cmsUInt32Number ;
struct TYPE_9__ {TYPE_3__* seq; } ;
typedef  TYPE_2__ cmsSEQ ;
struct TYPE_8__ {int /*<<< orphan*/  ID8; } ;
struct TYPE_10__ {int /*<<< orphan*/  Description; TYPE_1__ ProfileID; } ;
typedef  TYPE_3__ cmsPSEQDESC ;
struct TYPE_11__ {int (* Read ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int,int) ;} ;
typedef  TYPE_4__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ReadEmbeddedText (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_4__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  TRUE ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static
cmsBool ReadSeqID(cmsContext ContextID, struct _cms_typehandler_struct* self,
                                             cmsIOHANDLER* io,
                                             void* Cargo,
                                             cmsUInt32Number n,
                                             cmsUInt32Number SizeOfTag)
{
    cmsSEQ* OutSeq = (cmsSEQ*) Cargo;
    cmsPSEQDESC* seq = &OutSeq ->seq[n];

    if (io -> Read(ContextID, io,seq ->ProfileID.ID8, 16, 1) != 1) return FALSE;
    if (!ReadEmbeddedText(ContextID, self, io, &seq ->Description, SizeOfTag)) return FALSE;

    return TRUE;
}