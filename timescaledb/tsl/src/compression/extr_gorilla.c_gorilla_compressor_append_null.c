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
struct TYPE_3__ {int has_nulls; int /*<<< orphan*/  nulls; } ;
typedef  TYPE_1__ GorillaCompressor ;

/* Variables and functions */
 int /*<<< orphan*/  simple8brle_compressor_append (int /*<<< orphan*/ *,int) ; 

void
gorilla_compressor_append_null(GorillaCompressor *compressor)
{
	simple8brle_compressor_append(&compressor->nulls, 1);
	compressor->has_nulls = true;
}