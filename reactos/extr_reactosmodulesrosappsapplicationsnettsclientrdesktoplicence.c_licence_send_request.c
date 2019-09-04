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
typedef  char uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/ * STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int LICENCE_TAG_HOST ; 
 int LICENCE_TAG_REQUEST ; 
 int LICENCE_TAG_USER ; 
 int /*<<< orphan*/  SEC_LICENCE_NEG ; 
 int SEC_MODULUS_SIZE ; 
 int SEC_PADDING_SIZE ; 
 int SEC_RANDOM_SIZE ; 
 int /*<<< orphan*/  out_uint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_uint8p (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  out_uint8s (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sec_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static BOOL
licence_send_request(RDPCLIENT * This, uint8 * client_random, uint8 * rsa_data, char *user, char *host)
{
	uint32 sec_flags = SEC_LICENCE_NEG;
	uint16 userlen = (uint16)strlen(user) + 1;
	uint16 hostlen = (uint16)strlen(host) + 1;
	uint16 length = 128 + userlen + hostlen;
	STREAM s;

	s = sec_init(This, sec_flags, length + 2);

	if(s == NULL)
		return False;

	out_uint8(s, LICENCE_TAG_REQUEST);
	out_uint8(s, 2);	/* version */
	out_uint16_le(s, length);

	out_uint32_le(s, 1);
	out_uint16(s, 0);
	out_uint16_le(s, 0xff01);

	out_uint8p(s, client_random, SEC_RANDOM_SIZE);
	out_uint16(s, 0);
	out_uint16_le(s, (SEC_MODULUS_SIZE + SEC_PADDING_SIZE));
	out_uint8p(s, rsa_data, SEC_MODULUS_SIZE);
	out_uint8s(s, SEC_PADDING_SIZE);

	out_uint16_le(s, LICENCE_TAG_USER);
	out_uint16_le(s, userlen);
	out_uint8p(s, user, userlen);

	out_uint16_le(s, LICENCE_TAG_HOST);
	out_uint16_le(s, hostlen);
	out_uint8p(s, host, hostlen);

	s_mark_end(s);
	return sec_send(This, s, sec_flags);
}