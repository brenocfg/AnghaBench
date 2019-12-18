#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct huffman_code {TYPE_1__* tree; } ;
struct TYPE_2__ {scalar_t__* branches; } ;

/* Variables and functions */

__attribute__((used)) static inline bool rar_is_leaf_node(struct huffman_code *code, int node) { return code->tree[node].branches[0] == code->tree[node].branches[1]; }