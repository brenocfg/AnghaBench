#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int boolean_t ;
struct TYPE_9__ {TYPE_4__* b_hdr; int /*<<< orphan*/ * b_data; } ;
typedef  TYPE_2__ arc_buf_t ;
struct TYPE_8__ {int /*<<< orphan*/ * b_pabd; } ;
struct TYPE_10__ {TYPE_1__ b_l1hdr; } ;

/* Variables and functions */
 scalar_t__ ARC_BUF_COMPRESSED (TYPE_2__*) ; 
 scalar_t__ ARC_BUF_LAST (TYPE_2__*) ; 
 int ARC_BUF_SHARED (TYPE_2__*) ; 
 int HDR_SHARED_DATA (TYPE_4__*) ; 
 int /*<<< orphan*/  IMPLY (int,int) ; 
 scalar_t__ abd_is_linear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * abd_to_buf (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline boolean_t
arc_buf_is_shared(arc_buf_t *buf)
{
	boolean_t shared = (buf->b_data != NULL &&
	    buf->b_hdr->b_l1hdr.b_pabd != NULL &&
	    abd_is_linear(buf->b_hdr->b_l1hdr.b_pabd) &&
	    buf->b_data == abd_to_buf(buf->b_hdr->b_l1hdr.b_pabd));
	IMPLY(shared, HDR_SHARED_DATA(buf->b_hdr));
	IMPLY(shared, ARC_BUF_SHARED(buf));
	IMPLY(shared, ARC_BUF_COMPRESSED(buf) || ARC_BUF_LAST(buf));

	/*
	 * It would be nice to assert arc_can_share() too, but the "hdr isn't
	 * already being shared" requirement prevents us from doing that.
	 */

	return (shared);
}