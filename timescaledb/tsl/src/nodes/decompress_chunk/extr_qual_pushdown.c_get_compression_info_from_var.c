#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ varno; scalar_t__ varattno; } ;
typedef  TYPE_3__ Var ;
struct TYPE_10__ {int /*<<< orphan*/  compression_info; TYPE_2__* chunk_rte; TYPE_1__* chunk_rel; } ;
struct TYPE_8__ {int /*<<< orphan*/  relid; } ;
struct TYPE_7__ {scalar_t__ relid; } ;
typedef  TYPE_4__ QualPushdownContext ;
typedef  int /*<<< orphan*/  FormData_hypertable_compression ;

/* Variables and functions */
 char* get_attname_compat (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/ * get_column_compressioninfo (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline FormData_hypertable_compression *
get_compression_info_from_var(QualPushdownContext *context, Var *var)
{
	char *column_name;
	/* Not on the chunk we expect */
	if (var->varno != context->chunk_rel->relid)
		return NULL;

	/* ignore system attibutes or whole row references */
	if (var->varattno <= 0)
		return NULL;

	column_name = get_attname_compat(context->chunk_rte->relid, var->varattno, false);
	return get_column_compressioninfo(context->compression_info, column_name);
}