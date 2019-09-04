#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ namelen; struct TYPE_3__* parent; } ;
typedef  TYPE_1__ send_dir ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */

__attribute__((used)) static __inline UINT16 find_path_len(send_dir* parent, UINT16 namelen) {
    UINT16 len = namelen;

    while (parent && parent->namelen > 0) {
        len += parent->namelen + 1;
        parent = parent->parent;
    }

    return len;
}