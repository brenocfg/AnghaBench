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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  arc_buf_hdr_t ;
typedef  scalar_t__ arc_buf_contents_t ;

/* Variables and functions */
 scalar_t__ ARC_BUFC_DATA ; 
 scalar_t__ ARC_BUFC_METADATA ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ arc_buf_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc_get_data_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 void* zio_buf_alloc (int /*<<< orphan*/ ) ; 
 void* zio_data_buf_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
arc_get_data_buf(arc_buf_hdr_t *hdr, uint64_t size, void *tag)
{
	arc_buf_contents_t type = arc_buf_type(hdr);

	arc_get_data_impl(hdr, size, tag);
	if (type == ARC_BUFC_METADATA) {
		return (zio_buf_alloc(size));
	} else {
		ASSERT(type == ARC_BUFC_DATA);
		return (zio_data_buf_alloc(size));
	}
}