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
struct TYPE_2__ {int /*<<< orphan*/ * internal; int /*<<< orphan*/  element_type; } ;
typedef  TYPE_1__ ExtendedCompressor ;
typedef  int /*<<< orphan*/  Compressor ;

/* Variables and functions */
 int /*<<< orphan*/ * dictionary_compressor_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictionary_compressor_append_null (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dictionary_compressor_append_null_value(Compressor *compressor)
{
	ExtendedCompressor *extended = (ExtendedCompressor *) compressor;
	if (extended->internal == NULL)
		extended->internal = dictionary_compressor_alloc(extended->element_type);

	dictionary_compressor_append_null(extended->internal);
}