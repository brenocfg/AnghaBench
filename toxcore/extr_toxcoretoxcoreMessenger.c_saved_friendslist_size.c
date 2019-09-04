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
typedef  int uint32_t ;
struct SAVED_FRIEND {int dummy; } ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int count_friendlist (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static uint32_t saved_friendslist_size(const Messenger *m)
{
    return count_friendlist(m) * sizeof(struct SAVED_FRIEND);
}