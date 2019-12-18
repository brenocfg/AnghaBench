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
struct TYPE_4__ {int /*<<< orphan*/  (* Read ) (TYPE_2__*,void*,size_t*) ;} ;
struct TYPE_3__ {size_t processed; int /*<<< orphan*/  check; TYPE_2__* realStream; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CSeqCheckInStream ;

/* Variables and functions */
 int /*<<< orphan*/  XzCheck_Update (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,void*,size_t*) ; 

__attribute__((used)) static SRes SeqCheckInStream_Read(void *pp, void *data, size_t *size)
{
  CSeqCheckInStream *p = (CSeqCheckInStream *)pp;
  SRes res = p->realStream->Read(p->realStream, data, size);
  XzCheck_Update(&p->check, data, *size);
  p->processed += *size;
  return res;
}