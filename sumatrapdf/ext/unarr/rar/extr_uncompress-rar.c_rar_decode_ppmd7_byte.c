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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  v3; } ;
struct TYPE_6__ {TYPE_1__ state; } ;
struct TYPE_7__ {TYPE_2__ uncomp; } ;
typedef  TYPE_3__ ar_archive_rar ;

/* Variables and functions */
 int rar_decode_ppmd7_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rar_decode_ppmd7_byte(ar_archive_rar *rar, uint8_t *byte)
{
    return rar_decode_ppmd7_symbol(&rar->uncomp.state.v3, byte);
}