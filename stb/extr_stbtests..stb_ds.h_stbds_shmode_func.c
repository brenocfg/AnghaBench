#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode; } ;
struct TYPE_5__ {TYPE_1__ string; } ;
typedef  TYPE_2__ stbds_hash_index ;
struct TYPE_6__ {int length; TYPE_2__* hash_table; } ;

/* Variables and functions */
 void* STBDS_ARR_TO_HASH (void*,size_t) ; 
 int /*<<< orphan*/  STBDS_BUCKET_LENGTH ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* stbds_arrgrowf (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* stbds_header (void*) ; 
 scalar_t__ stbds_make_hash_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void * stbds_shmode_func(size_t elemsize, int mode)
{
  void *a = stbds_arrgrowf(0, elemsize, 0, 1);
  stbds_hash_index *h;
  memset(a, 0, elemsize);
  stbds_header(a)->length = 1;
  stbds_header(a)->hash_table = h = (stbds_hash_index *) stbds_make_hash_index(STBDS_BUCKET_LENGTH, NULL);
  h->string.mode = mode;
  return STBDS_ARR_TO_HASH(a,elemsize);
}