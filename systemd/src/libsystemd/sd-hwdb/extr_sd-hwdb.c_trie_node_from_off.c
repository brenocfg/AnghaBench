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
struct trie_node_f {int dummy; } ;
struct TYPE_3__ {scalar_t__ map; } ;
typedef  TYPE_1__ sd_hwdb ;
typedef  int /*<<< orphan*/  le64_t ;

/* Variables and functions */
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct trie_node_f *trie_node_from_off(sd_hwdb *hwdb, le64_t off) {
        return (const struct trie_node_f *)(hwdb->map + le64toh(off));
}