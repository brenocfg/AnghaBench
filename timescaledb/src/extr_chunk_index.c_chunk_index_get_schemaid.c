#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  schema_name; } ;
struct TYPE_8__ {TYPE_1__ fd; } ;
struct TYPE_7__ {int /*<<< orphan*/  chunk_id; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__* Form_chunk_index ;
typedef  TYPE_3__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_oid (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ts_chunk_get_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline Oid
chunk_index_get_schemaid(Form_chunk_index chunk_index, bool missing_ok)
{
	Chunk *chunk = ts_chunk_get_by_id(chunk_index->chunk_id, 0, true);

	return get_namespace_oid(NameStr(chunk->fd.schema_name), missing_ok);
}