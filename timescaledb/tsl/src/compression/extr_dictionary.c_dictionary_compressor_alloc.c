#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  typalign; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typlen; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_8__ {int has_nulls; int /*<<< orphan*/  nulls; int /*<<< orphan*/  dictionary_indexes; int /*<<< orphan*/  dictionary_items; int /*<<< orphan*/  typalign; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  typlen; int /*<<< orphan*/  type; scalar_t__ next_index; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ DictionaryCompressor ;

/* Variables and functions */
 int TYPECACHE_EQ_OPR_FINFO ; 
 int TYPECACHE_HASH_PROC_FINFO ; 
 int /*<<< orphan*/  dictionary_hash_alloc (TYPE_1__*) ; 
 TYPE_1__* lookup_type_cache (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* palloc (int) ; 
 int /*<<< orphan*/  simple8brle_compressor_init (int /*<<< orphan*/ *) ; 

DictionaryCompressor *
dictionary_compressor_alloc(Oid type)
{
	DictionaryCompressor *compressor = palloc(sizeof(*compressor));
	TypeCacheEntry *tentry =
		lookup_type_cache(type, TYPECACHE_EQ_OPR_FINFO | TYPECACHE_HASH_PROC_FINFO);

	compressor->next_index = 0;
	compressor->has_nulls = false;
	compressor->type = type;
	compressor->typlen = tentry->typlen;
	compressor->typbyval = tentry->typbyval;
	compressor->typalign = tentry->typalign;

	compressor->dictionary_items = dictionary_hash_alloc(tentry);

	simple8brle_compressor_init(&compressor->dictionary_indexes);
	simple8brle_compressor_init(&compressor->nulls);
	return compressor;
}