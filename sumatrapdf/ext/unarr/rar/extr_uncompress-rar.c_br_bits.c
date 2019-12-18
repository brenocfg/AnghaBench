#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int bits; int available; } ;
struct TYPE_6__ {TYPE_1__ br; } ;
struct TYPE_7__ {TYPE_2__ uncomp; } ;
typedef  TYPE_3__ ar_archive_rar ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t br_bits(ar_archive_rar *rar, int bits)
{
    return (rar->uncomp.br.bits >> (rar->uncomp.br.available -= bits)) & (((uint64_t)1 << bits) - 1);
}