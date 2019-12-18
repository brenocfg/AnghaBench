#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * (* compressor_for_type ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Compressor ;
typedef  size_t CompressionAlgorithms ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 size_t _END_COMPRESSION_ALGORITHMS ; 
 TYPE_1__* definitions ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Compressor *
compressor_for_algorithm_and_type(CompressionAlgorithms algorithm, Oid type)
{
	if (algorithm >= _END_COMPRESSION_ALGORITHMS)
		elog(ERROR, "invalid compression algorithm %d", algorithm);

	return definitions[algorithm].compressor_for_type(type);
}