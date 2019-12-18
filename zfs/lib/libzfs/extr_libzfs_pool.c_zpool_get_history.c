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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int uint_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  ZPOOL_HIST_RECORD ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_history (int /*<<< orphan*/ *,char*,int*,int*) ; 
 char* malloc (int) ; 
 scalar_t__ nvlist_add_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify (int) ; 
 int zpool_history_unpack (char*,int,int*,int /*<<< orphan*/ ***,int*) ; 

int
zpool_get_history(zpool_handle_t *zhp, nvlist_t **nvhisp, uint64_t *off,
    boolean_t *eof)
{
	char *buf;
	int buflen = 128 * 1024;
	nvlist_t **records = NULL;
	uint_t numrecords = 0;
	int err, i;
	uint64_t start = *off;

	buf = malloc(buflen);
	if (buf == NULL)
		return (ENOMEM);
	/* process about 1MB a time */
	while (*off - start < 1024 * 1024) {
		uint64_t bytes_read = buflen;
		uint64_t leftover;

		if ((err = get_history(zhp, buf, off, &bytes_read)) != 0)
			break;

		/* if nothing else was read in, we're at EOF, just return */
		if (!bytes_read) {
			*eof = B_TRUE;
			break;
		}

		if ((err = zpool_history_unpack(buf, bytes_read,
		    &leftover, &records, &numrecords)) != 0)
			break;
		*off -= leftover;
		if (leftover == bytes_read) {
			/*
			 * no progress made, because buffer is not big enough
			 * to hold this record; resize and retry.
			 */
			buflen *= 2;
			free(buf);
			buf = malloc(buflen);
			if (buf == NULL)
				return (ENOMEM);
		}
	}

	free(buf);

	if (!err) {
		verify(nvlist_alloc(nvhisp, NV_UNIQUE_NAME, 0) == 0);
		verify(nvlist_add_nvlist_array(*nvhisp, ZPOOL_HIST_RECORD,
		    records, numrecords) == 0);
	}
	for (i = 0; i < numrecords; i++)
		nvlist_free(records[i]);
	free(records);

	return (err);
}