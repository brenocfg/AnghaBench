#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int has_nulls; int /*<<< orphan*/  serializer; int /*<<< orphan*/  type; int /*<<< orphan*/  data; int /*<<< orphan*/  sizes; int /*<<< orphan*/  nulls; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ArrayCompressor ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  char_vec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_datum_serializer (int /*<<< orphan*/ ) ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  simple8brle_compressor_init (int /*<<< orphan*/ *) ; 

ArrayCompressor *
array_compressor_alloc(Oid type_to_compress)
{
	ArrayCompressor *compressor = palloc(sizeof(*compressor));
	compressor->has_nulls = false;

	simple8brle_compressor_init(&compressor->nulls);
	simple8brle_compressor_init(&compressor->sizes);
	char_vec_init(&compressor->data, CurrentMemoryContext, 0);

	compressor->type = type_to_compress;
	compressor->serializer = create_datum_serializer(type_to_compress);
	return compressor;
}