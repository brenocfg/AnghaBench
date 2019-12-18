#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  arc_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_BUFC_DATA ; 
 int /*<<< orphan*/  ARC_BUFC_METADATA ; 
 int /*<<< orphan*/ * arc_alloc_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arc_buf_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc_loaned_bytes_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_onloan_tag ; 

arc_buf_t *
arc_loan_buf(spa_t *spa, boolean_t is_metadata, int size)
{
	arc_buf_t *buf = arc_alloc_buf(spa, arc_onloan_tag,
	    is_metadata ? ARC_BUFC_METADATA : ARC_BUFC_DATA, size);

	arc_loaned_bytes_update(arc_buf_size(buf));

	return (buf);
}