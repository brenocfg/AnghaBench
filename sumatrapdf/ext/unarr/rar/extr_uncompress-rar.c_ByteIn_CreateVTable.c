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
struct TYPE_2__ {int /*<<< orphan*/  Read; } ;
struct ByteReader {int /*<<< orphan*/ * rar; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  ar_archive_rar ;

/* Variables and functions */
 int /*<<< orphan*/  ByteIn_Read ; 

__attribute__((used)) static void ByteIn_CreateVTable(struct ByteReader *br, ar_archive_rar *rar)
{
    br->super.Read = ByteIn_Read;
    br->rar = rar;
}