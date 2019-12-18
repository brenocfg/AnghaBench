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
struct timestamps_filter_s {int sequence; scalar_t__ contiguous_last; scalar_t__ sequence_offset; int /*<<< orphan*/  mva; } ;

/* Variables and functions */
 int /*<<< orphan*/  mva_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void timestamps_filter_init(struct timestamps_filter_s *tf)
{
    mva_init(&tf->mva);
    tf->sequence_offset = 0;
    tf->contiguous_last = 0;
    tf->sequence = -1;
}