#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_cksum_t ;
struct TYPE_4__ {int /*<<< orphan*/ * labels; int /*<<< orphan*/  cksum; } ;
typedef  TYPE_1__ cksum_record_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 TYPE_1__* umem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static cksum_record_t *
cksum_record_alloc(zio_cksum_t *cksum, int l)
{
	cksum_record_t *rec;

	rec = umem_zalloc(sizeof (*rec), UMEM_NOFAIL);
	rec->cksum = *cksum;
	rec->labels[l] = B_TRUE;

	return (rec);
}