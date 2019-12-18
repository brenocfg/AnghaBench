#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
typedef  scalar_t__ int64 ;

/* Variables and functions */
 scalar_t__ calculate_initial_chunk_target_size () ; 
 scalar_t__ convert_text_memory_amount_to_bytes (char const*) ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 
 char* text_to_cstring (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int64
chunk_target_size_in_bytes(const text *target_size_text)
{
	const char *target_size = text_to_cstring(target_size_text);
	int64 target_size_bytes = 0;

	if (pg_strcasecmp(target_size, "off") == 0 || pg_strcasecmp(target_size, "disable") == 0)
		return 0;

	if (pg_strcasecmp(target_size, "estimate") == 0)
		target_size_bytes = calculate_initial_chunk_target_size();
	else
		target_size_bytes = convert_text_memory_amount_to_bytes(target_size);

	/* Disable if target size is zero or less */
	if (target_size_bytes <= 0)
		target_size_bytes = 0;

	return target_size_bytes;
}