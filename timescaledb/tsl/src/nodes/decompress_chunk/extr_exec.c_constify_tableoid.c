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
struct TYPE_3__ {int /*<<< orphan*/  chunk_relid; int /*<<< orphan*/  chunk_index; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  TYPE_1__ ConstifyTableOidContext ;

/* Variables and functions */
 scalar_t__ constify_tableoid_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static List *
constify_tableoid(List *node, Index chunk_index, Oid chunk_relid)
{
	ConstifyTableOidContext ctx = {
		.chunk_index = chunk_index,
		.chunk_relid = chunk_relid,
	};

	return (List *) constify_tableoid_walker((Node *) node, &ctx);
}