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
struct redact_record {scalar_t__ eos_marker; int /*<<< orphan*/  datablksz; int /*<<< orphan*/  end_blkid; int /*<<< orphan*/  end_object; int /*<<< orphan*/  start_blkid; int /*<<< orphan*/  start_object; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 scalar_t__ redact_range_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
redact_record_before(const struct redact_record *from,
    const struct redact_record *to)
{
	if (from->eos_marker == B_TRUE)
		return (B_FALSE);
	else if (to->eos_marker == B_TRUE)
		return (B_TRUE);
	return (redact_range_compare(from->start_object, from->start_blkid,
	    from->datablksz, to->end_object, to->end_blkid,
	    to->datablksz) <= 0);
}