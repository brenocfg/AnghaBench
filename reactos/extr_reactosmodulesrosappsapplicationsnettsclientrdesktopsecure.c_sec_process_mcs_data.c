#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint16 ;
struct TYPE_8__ {int* p; int* end; } ;
typedef  TYPE_1__* STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
#define  SEC_TAG_SRV_CHANNELS 130 
#define  SEC_TAG_SRV_CRYPT 129 
#define  SEC_TAG_SRV_INFO 128 
 int /*<<< orphan*/  in_uint16_le (TYPE_1__*,int) ; 
 int /*<<< orphan*/  in_uint8 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  in_uint8s (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sec_process_crypt_info (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sec_process_srv_info (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

void
sec_process_mcs_data(RDPCLIENT * This, STREAM s)
{
	uint16 tag, length;
	uint8 *next_tag;
	uint8 len;

	in_uint8s(s, 21);	/* header (T.124 ConferenceCreateResponse) */
	in_uint8(s, len);
	if (len & 0x80)
		in_uint8(s, len);

	while (s->p < s->end)
	{
		in_uint16_le(s, tag);
		in_uint16_le(s, length);

		if (length <= 4)
			return;

		next_tag = s->p + length - 4;

		switch (tag)
		{
			case SEC_TAG_SRV_INFO:
				sec_process_srv_info(This, s);
				break;

			case SEC_TAG_SRV_CRYPT:
				sec_process_crypt_info(This, s);
				break;

			case SEC_TAG_SRV_CHANNELS:
				/* FIXME: We should parse this information and
				   use it to map RDP5 channels to MCS
				   channels */
				break;

			default:
				unimpl("response tag 0x%x\n", tag);
		}

		s->p = next_tag;
	}
}