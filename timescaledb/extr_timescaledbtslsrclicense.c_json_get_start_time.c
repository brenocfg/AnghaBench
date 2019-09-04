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
typedef  int /*<<< orphan*/  TimestampTz ;
typedef  int /*<<< orphan*/  Jsonb ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  FIELD_NOT_FOUND_ERRSTRING ; 
 int /*<<< orphan*/  START_TIME_FIELD ; 
 int /*<<< orphan*/  cstring_to_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_jsonb_get_time_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static TimestampTz
json_get_start_time(Jsonb *license)
{
	bool found = false;
	TimestampTz start_time =
		ts_jsonb_get_time_field(license, cstring_to_text(START_TIME_FIELD), &found);

	if (!found)
		elog(ERRCODE_FEATURE_NOT_SUPPORTED, FIELD_NOT_FOUND_ERRSTRING, START_TIME_FIELD);
	return start_time;
}