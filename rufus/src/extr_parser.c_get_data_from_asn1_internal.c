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
typedef  int uint8_t ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ memcmp (int const*,void const*,size_t) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

__attribute__((used)) static BOOL get_data_from_asn1_internal(const uint8_t* buf, size_t buf_len, const void* oid,
			size_t oid_len, uint8_t asn1_type, void** data, size_t* data_len, BOOL* matched)
{
	size_t pos = 0, len, len_len, i;
	uint8_t tag;
	BOOL is_sequence, is_universal_tag;

	while (pos < buf_len) {
		is_sequence = buf[pos] & 0x20;
		is_universal_tag = ((buf[pos] & 0xC0) == 0x00);
		tag = buf[pos++] & 0x1F;
		if (tag == 0x1F) {
			uprintf("get_data_from_asn1: Long form tags are unsupported");
			return FALSE;
		}

		// Compute the length
		len = 0;
		len_len = 1;
		if ((is_universal_tag) && (tag == 0x05)) {	// ignore "NULL" tag
			pos++;
		} else {
			if (buf[pos] & 0x80) {
				len_len = buf[pos++] & 0x7F;
				// The data we're dealing with is not expected to ever be larger than 64K
				if (len_len > 2) {
					uprintf("get_data_from_asn1: Length fields larger than 2 bytes are unsupported");
					return FALSE;
				}
				for (i = 0; i < len_len; i++) {
					len <<= 8;
					len += buf[pos++];
				}
			} else {
				len = buf[pos++];
			}

			if (len > buf_len - pos) {
				uprintf("get_data_from_asn1: Overflow error (computed length %d is larger than remaining data)", len);
				return FALSE;
			}
		}

		if (len != 0) {
			if (is_sequence) {
				if (!get_data_from_asn1_internal(&buf[pos], len, oid, oid_len, asn1_type, data, data_len, matched))
					return FALSE;	// error
				if (*data != NULL)
					return TRUE;
			} else if (is_universal_tag) {	// Only process tags that belong to the UNIVERSAL class
				// NB: 0x06 = "OID" tag
				if ((!*matched) && (tag == 0x06) && (len == oid_len) && (memcmp(&buf[pos], oid, oid_len) == 0)) {
					*matched = TRUE;
				} else if ((*matched) && (tag == asn1_type)) {
					*data_len = len;
					*data = (void*)&buf[pos];
					return TRUE;
				}
			}
			pos += len;
		}
	};

	return TRUE;
}