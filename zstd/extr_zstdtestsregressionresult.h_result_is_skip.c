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
typedef  int /*<<< orphan*/  result_t ;

/* Variables and functions */
 scalar_t__ result_error_skip ; 
 scalar_t__ result_get_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int result_is_skip(result_t result) {
    return result_get_error(result) == result_error_skip;
}