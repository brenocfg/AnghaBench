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
struct TYPE_3__ {size_t size; size_t pos; void* buf; TYPE_2__* realStream; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CLookToRead ;

/* Variables and functions */
 size_t LookToRead_BUF_SIZE ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,void*,size_t*) ; 

__attribute__((used)) static SRes LookToRead_Look_Exact(void *pp, const void **buf, size_t *size)
{
  SRes res = SZ_OK;
  CLookToRead *p = (CLookToRead *)pp;
  size_t size2 = p->size - p->pos;
  if (size2 == 0 && *size > 0)
  {
    p->pos = 0;
    if (*size > LookToRead_BUF_SIZE)
      *size = LookToRead_BUF_SIZE;
    res = p->realStream->Read(p->realStream, p->buf, size);
    size2 = p->size = *size;
  }
  if (size2 < *size)
    *size = size2;
  *buf = p->buf + p->pos;
  return res;
}