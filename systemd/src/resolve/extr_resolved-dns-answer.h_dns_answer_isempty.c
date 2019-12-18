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
typedef  int /*<<< orphan*/  DnsAnswer ;

/* Variables and functions */
 scalar_t__ dns_answer_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool dns_answer_isempty(DnsAnswer *a) {
        return dns_answer_size(a) <= 0;
}