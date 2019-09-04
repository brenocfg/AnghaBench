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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/ * STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int LICENCE_HWID_SIZE ; 
 int LICENCE_SIGNATURE_SIZE ; 
 int LICENCE_TAG_AUTHRESP ; 
 int LICENCE_TOKEN_SIZE ; 
 int /*<<< orphan*/  SEC_LICENCE_NEG ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_uint8p (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sec_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
licence_send_authresp(RDPCLIENT * This, uint8 * token, uint8 * crypt_hwid, uint8 * signature)
{
	uint32 sec_flags = SEC_LICENCE_NEG;
	uint16 length = 58;
	STREAM s;

	s = sec_init(This, sec_flags, length + 2);

	if(s == NULL)
		return False;

	out_uint8(s, LICENCE_TAG_AUTHRESP);
	out_uint8(s, 2);	/* version */
	out_uint16_le(s, length);

	out_uint16_le(s, 1);
	out_uint16_le(s, LICENCE_TOKEN_SIZE);
	out_uint8p(s, token, LICENCE_TOKEN_SIZE);

	out_uint16_le(s, 1);
	out_uint16_le(s, LICENCE_HWID_SIZE);
	out_uint8p(s, crypt_hwid, LICENCE_HWID_SIZE);

	out_uint8p(s, signature, LICENCE_SIGNATURE_SIZE);

	s_mark_end(s);
	return sec_send(This, s, sec_flags);
}