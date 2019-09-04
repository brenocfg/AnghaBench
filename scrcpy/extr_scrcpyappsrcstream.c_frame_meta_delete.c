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
struct frame_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct frame_meta*) ; 

__attribute__((used)) static void
frame_meta_delete(struct frame_meta *frame_meta) {
    free(frame_meta);
}