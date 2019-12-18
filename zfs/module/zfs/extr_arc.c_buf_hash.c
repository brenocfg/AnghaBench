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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/ * dva_word; } ;
typedef  TYPE_1__ dva_t ;

/* Variables and functions */
 int /*<<< orphan*/  cityhash4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
buf_hash(uint64_t spa, const dva_t *dva, uint64_t birth)
{
	return (cityhash4(spa, dva->dva_word[0], dva->dva_word[1], birth));
}