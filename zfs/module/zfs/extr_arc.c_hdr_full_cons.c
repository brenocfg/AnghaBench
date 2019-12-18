#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  b_arc_node; int /*<<< orphan*/  b_freeze_lock; int /*<<< orphan*/  b_refcnt; int /*<<< orphan*/  b_cv; int /*<<< orphan*/  b_byteswap; } ;
struct TYPE_5__ {int /*<<< orphan*/  b_l2node; } ;
struct TYPE_7__ {TYPE_2__ b_l1hdr; TYPE_1__ b_l2hdr; } ;
typedef  TYPE_3__ arc_buf_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_SPACE_HDRS ; 
 int /*<<< orphan*/  CV_DEFAULT ; 
 int /*<<< orphan*/  DMU_BSWAP_NUMFUNCS ; 
 int /*<<< orphan*/  HDR_FULL_SIZE ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  arc_space_consume (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_link_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multilist_link_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hdr_full_cons(void *vbuf, void *unused, int kmflag)
{
	arc_buf_hdr_t *hdr = vbuf;

	bzero(hdr, HDR_FULL_SIZE);
	hdr->b_l1hdr.b_byteswap = DMU_BSWAP_NUMFUNCS;
	cv_init(&hdr->b_l1hdr.b_cv, NULL, CV_DEFAULT, NULL);
	zfs_refcount_create(&hdr->b_l1hdr.b_refcnt);
	mutex_init(&hdr->b_l1hdr.b_freeze_lock, NULL, MUTEX_DEFAULT, NULL);
	list_link_init(&hdr->b_l1hdr.b_arc_node);
	list_link_init(&hdr->b_l2hdr.b_l2node);
	multilist_link_init(&hdr->b_l1hdr.b_arc_node);
	arc_space_consume(HDR_FULL_SIZE, ARC_SPACE_HDRS);

	return (0);
}