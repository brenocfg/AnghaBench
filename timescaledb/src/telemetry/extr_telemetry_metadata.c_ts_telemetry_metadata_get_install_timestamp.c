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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CSTRINGOID ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  METADATA_TIMESTAMP_KEY_NAME ; 
 int /*<<< orphan*/  TIMESTAMPTZOID ; 
 int /*<<< orphan*/  TimestampTzGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_metadata_get_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ts_metadata_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

Datum
ts_telemetry_metadata_get_install_timestamp(void)
{
	bool isnull;
	Datum timestamp;

	timestamp = ts_metadata_get_value(CStringGetDatum(METADATA_TIMESTAMP_KEY_NAME),
									  CSTRINGOID,
									  TIMESTAMPTZOID,
									  &isnull);

	if (isnull)
		timestamp = ts_metadata_insert(CStringGetDatum(METADATA_TIMESTAMP_KEY_NAME),
									   CSTRINGOID,
									   TimestampTzGetDatum(GetCurrentTimestamp()),
									   TIMESTAMPTZOID,
									   true);

	return timestamp;
}