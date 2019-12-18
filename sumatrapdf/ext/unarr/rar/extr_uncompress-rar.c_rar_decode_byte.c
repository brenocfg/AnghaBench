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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  ar_archive_rar ;

/* Variables and functions */
 scalar_t__ br_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  br_check (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool rar_decode_byte(ar_archive_rar *rar, uint8_t *byte)
{
    if (!br_check(rar, 8))
        return false;
    *byte = (uint8_t)br_bits(rar, 8);
    return true;
}