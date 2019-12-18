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
typedef  int /*<<< orphan*/  pg_uuid_t ;
typedef  int /*<<< orphan*/  TimestampTz ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  UUID_LEN ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 unsigned char* palloc0 (int /*<<< orphan*/ ) ; 
 int pg_backend_random (char*,int /*<<< orphan*/ ) ; 

pg_uuid_t *
ts_uuid_create(void)
{
	/*
	 * PG9.6 doesn't expose the internals of pg_uuid_t, so we just treat it as
	 * a byte array
	 */
	unsigned char *gen_uuid = palloc0(UUID_LEN);
	bool rand_success = false;

#if !PG96
	rand_success = pg_backend_random((char *) gen_uuid, UUID_LEN);
#endif

	/*
	 * If pg_backend_random() cannot find sources of randomness, then we use
	 * the current timestamp as a "random source". Note that
	 * pg_backend_random() was added in PG10, so we always use the current
	 * timestamp on PG9.6. Timestamps are 8 bytes, so we copy this into bytes
	 * 9-16 of the UUID. If we see all 0s in bytes 0-8 (other than version +
	 * variant), we know that there is something wrong with the RNG on this
	 * instance.
	 */
	if (!rand_success)
	{
		TimestampTz ts = GetCurrentTimestamp();

		memcpy(&gen_uuid[8], &ts, sizeof(TimestampTz));
	}

	gen_uuid[6] = (gen_uuid[6] & 0x0f) | 0x40; /* "version" field */
	gen_uuid[8] = (gen_uuid[8] & 0x3f) | 0x80; /* "variant" field */

	return (pg_uuid_t *) gen_uuid;
}