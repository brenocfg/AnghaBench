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
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/ * sizes; } ;
typedef  TYPE_1__ ArrayCompressorSerializationInfo ;
typedef  TYPE_2__ ArrayCompressor ;

/* Variables and functions */
 void* array_compressed_from_serialization_info (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* array_compressor_get_serialization_info (TYPE_2__*) ; 

void *
array_compressor_finish(ArrayCompressor *compressor)
{
	ArrayCompressorSerializationInfo *info = array_compressor_get_serialization_info(compressor);
	if (info->sizes == NULL)
		return NULL;

	return array_compressed_from_serialization_info(info, compressor->type);
}