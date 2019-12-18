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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_data_from_asn1_internal (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,void**,size_t*,int*) ; 
 int /*<<< orphan*/ * oid_from_str (char const*,size_t*) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

void* get_data_from_asn1(const uint8_t* buf, size_t buf_len, const char* oid_str, uint8_t asn1_type, size_t* data_len)
{
	void* data = NULL;
	uint8_t* oid = NULL;
	size_t oid_len = 0;
	BOOL matched = ((oid_str == NULL) || (oid_str[0] == 0));

	if (buf_len >= 65536) {
		uprintf("get_data_from_asn1: Buffers larger than 64KB are not supported");
		return NULL;
	}

	if (!matched) {
		// We have an OID string to convert
		oid = oid_from_str(oid_str, &oid_len);
		if (oid == NULL) {
			uprintf("get_data_from_asn1: Could not convert OID string '%s'", oid_str);
			return NULL;
		}
	}

	// No need to check for the return value as data is always NULL on error
	get_data_from_asn1_internal(buf, buf_len, oid, oid_len, asn1_type, &data, data_len, &matched);
	free(oid);
	return data;
}