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
struct ByteReader {int /*<<< orphan*/  rar; } ;
typedef  int Byte ;

/* Variables and functions */
 scalar_t__ br_bits (int /*<<< orphan*/ ,int) ; 
 scalar_t__ br_check (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Byte ByteIn_Read(void *p)
{
    struct ByteReader *self = p;
    return br_check(self->rar, 8) ? (Byte)br_bits(self->rar, 8) : 0xFF;
}