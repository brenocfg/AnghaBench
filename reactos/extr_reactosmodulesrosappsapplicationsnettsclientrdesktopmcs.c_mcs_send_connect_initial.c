#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
struct TYPE_10__ {scalar_t__ data; scalar_t__ end; } ;
typedef  TYPE_1__* STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BER_TAG_BOOLEAN ; 
 int /*<<< orphan*/  BER_TAG_OCTET_STRING ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  MCS_CONNECT_INITIAL ; 
 int /*<<< orphan*/  ber_out_header (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* iso_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iso_send (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mcs_out_domain_params (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  out_uint8 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  out_uint8p (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  s_mark_end (TYPE_1__*) ; 

__attribute__((used)) static BOOL
mcs_send_connect_initial(RDPCLIENT * This, STREAM mcs_data)
{
	int datalen = (uint16)(mcs_data->end - mcs_data->data);
	int length = 9 + 3 * 34 + 4 + datalen;
	STREAM s;

	s = iso_init(This, length + 5);

	if(s == NULL)
		return False;

	ber_out_header(s, MCS_CONNECT_INITIAL, length);
	ber_out_header(s, BER_TAG_OCTET_STRING, 1);	/* calling domain */
	out_uint8(s, 1);
	ber_out_header(s, BER_TAG_OCTET_STRING, 1);	/* called domain */
	out_uint8(s, 1);

	ber_out_header(s, BER_TAG_BOOLEAN, 1);
	out_uint8(s, 0xff);	/* upward flag */

	mcs_out_domain_params(s, 34, 2, 0, 0xffff);	/* target params */
	mcs_out_domain_params(s, 1, 1, 1, 0x420);	/* min params */
	mcs_out_domain_params(s, 0xffff, 0xfc17, 0xffff, 0xffff);	/* max params */

	ber_out_header(s, BER_TAG_OCTET_STRING, datalen);
	out_uint8p(s, mcs_data->data, datalen);

	s_mark_end(s);
	return iso_send(This, s);
}