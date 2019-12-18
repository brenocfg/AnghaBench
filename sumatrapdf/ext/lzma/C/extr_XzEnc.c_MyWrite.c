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
struct TYPE_4__ {size_t (* Write ) (TYPE_2__*,void const*,size_t) ;} ;
struct TYPE_3__ {size_t processed; TYPE_2__* realStream; } ;
typedef  TYPE_1__ CSeqSizeOutStream ;

/* Variables and functions */
 size_t stub1 (TYPE_2__*,void const*,size_t) ; 

__attribute__((used)) static size_t MyWrite(void *pp, const void *data, size_t size)
{
  CSeqSizeOutStream *p = (CSeqSizeOutStream *)pp;
  size = p->realStream->Write(p->realStream, data, size);
  p->processed += size;
  return size;
}