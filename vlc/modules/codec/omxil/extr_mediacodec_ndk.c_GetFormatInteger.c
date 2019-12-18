#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* getInt32 ) (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ AMediaFormat; } ;
typedef  int /*<<< orphan*/  AMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__ syms ; 

__attribute__((used)) static int32_t GetFormatInteger(AMediaFormat *p_format, const char *psz_name)
{
    int32_t i_out = 0;
    syms.AMediaFormat.getInt32(p_format, psz_name, &i_out);
    return i_out;
}