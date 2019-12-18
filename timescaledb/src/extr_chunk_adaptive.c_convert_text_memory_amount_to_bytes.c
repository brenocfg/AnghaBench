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
typedef  int int64 ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GUC_UNIT_BLOCKS ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,char const*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  parse_int (char const*,int*,int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int64
convert_text_memory_amount_to_bytes(const char *memory_amount)
{
	const char *hintmsg;
	int nblocks;
	int64 bytes;

	if (NULL == memory_amount)
		elog(ERROR, "invalid memory amount");

	if (!parse_int(memory_amount, &nblocks, GUC_UNIT_BLOCKS, &hintmsg))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid data amount"),
				 errhint("%s", hintmsg)));

	bytes = nblocks;
	bytes *= BLCKSZ;

	return bytes;
}