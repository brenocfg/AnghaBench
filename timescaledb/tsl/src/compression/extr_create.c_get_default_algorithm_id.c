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
typedef  enum CompressionAlgorithms { ____Placeholder_CompressionAlgorithms } CompressionAlgorithms ;
struct TYPE_6__ {int /*<<< orphan*/ * fn_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * fn_addr; } ;
struct TYPE_7__ {TYPE_2__ eq_opr_finfo; TYPE_1__ hash_proc_finfo; } ;
typedef  TYPE_3__ TypeCacheEntry ;
typedef  int Oid ;

/* Variables and functions */
#define  CHAROID 139 
 int COMPRESSION_ALGORITHM_ARRAY ; 
 int COMPRESSION_ALGORITHM_DELTADELTA ; 
 int COMPRESSION_ALGORITHM_DICTIONARY ; 
 int COMPRESSION_ALGORITHM_GORILLA ; 
#define  DATEOID 138 
#define  FLOAT4OID 137 
#define  FLOAT8OID 136 
#define  INT2OID 135 
#define  INT4OID 134 
#define  INT8OID 133 
#define  INTERVALOID 132 
#define  NUMERICOID 131 
#define  TEXTOID 130 
#define  TIMESTAMPOID 129 
#define  TIMESTAMPTZOID 128 
 int TYPECACHE_EQ_OPR_FINFO ; 
 int TYPECACHE_HASH_PROC_FINFO ; 
 TYPE_3__* lookup_type_cache (int,int) ; 

__attribute__((used)) static enum CompressionAlgorithms
get_default_algorithm_id(Oid typeoid)
{
	switch (typeoid)
	{
		case INT4OID:
		case INT2OID:
		case INT8OID:
		case INTERVALOID:
		case DATEOID:
		case TIMESTAMPOID:
		case TIMESTAMPTZOID:
		{
			return COMPRESSION_ALGORITHM_DELTADELTA;
		}
		case FLOAT4OID:
		case FLOAT8OID:
		{
			return COMPRESSION_ALGORITHM_GORILLA;
		}
		case NUMERICOID:
		{
			return COMPRESSION_ALGORITHM_ARRAY;
		}
		case TEXTOID:
		case CHAROID:
		{
			return COMPRESSION_ALGORITHM_DICTIONARY;
		}
		default:
		{
			/* use dictitionary if possible, otherwise use array */
			TypeCacheEntry *tentry =
				lookup_type_cache(typeoid, TYPECACHE_EQ_OPR_FINFO | TYPECACHE_HASH_PROC_FINFO);
			if (tentry->hash_proc_finfo.fn_addr == NULL || tentry->eq_opr_finfo.fn_addr == NULL)
				return COMPRESSION_ALGORITHM_ARRAY;
			return COMPRESSION_ALGORITHM_DICTIONARY;
		}
	}
}