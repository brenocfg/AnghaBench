#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int next_index; int /*<<< orphan*/  nulls; int /*<<< orphan*/  dictionary_indexes; int /*<<< orphan*/  typlen; int /*<<< orphan*/  typbyval; int /*<<< orphan*/  dictionary_items; } ;
struct TYPE_5__ {int index; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ DictionaryHashItem ;
typedef  TYPE_2__ DictionaryCompressor ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dictionary_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  simple8brle_compressor_append (int /*<<< orphan*/ *,int) ; 

void
dictionary_compressor_append(DictionaryCompressor *compressor, Datum val)
{
	bool found;
	DictionaryHashItem *dict_item;

	Assert(compressor != NULL);

	dict_item = dictionary_insert(compressor->dictionary_items, val, &found);

	if (!found)
	{
		// per_val->bitmap = roaring_dictionary_create();
		dict_item->index = compressor->next_index;
		dict_item->key = datumCopy(val, compressor->typbyval, compressor->typlen);
		compressor->next_index += 1;
	}

	simple8brle_compressor_append(&compressor->dictionary_indexes, dict_item->index);
	simple8brle_compressor_append(&compressor->nulls, 0);
}