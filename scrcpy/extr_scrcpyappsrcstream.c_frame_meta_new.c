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
struct frame_meta {int /*<<< orphan*/ * next; int /*<<< orphan*/  pts; } ;

/* Variables and functions */
 struct frame_meta* malloc (int) ; 

__attribute__((used)) static struct frame_meta *
frame_meta_new(uint64_t pts) {
    struct frame_meta *meta = malloc(sizeof(*meta));
    if (!meta) {
        return meta;
    }
    meta->pts = pts;
    meta->next = NULL;
    return meta;
}