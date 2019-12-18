#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
struct TYPE_4__ {scalar_t__ server_public_key_len; } ;
struct TYPE_5__ {TYPE_1__ secure; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ SEC_EXPONENT_SIZE ; 
 scalar_t__ SEC_MAX_MODULUS_SIZE ; 
 scalar_t__ SEC_PADDING_SIZE ; 
 scalar_t__ SEC_RSA_MAGIC ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  in_uint32_le (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  in_uint8p (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  s_check (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
sec_parse_public_key(RDPCLIENT * This, STREAM s, uint8 ** modulus, uint8 ** exponent)
{
	uint32 magic, modulus_len;

	in_uint32_le(s, magic);
	if (magic != SEC_RSA_MAGIC)
	{
		error("RSA magic 0x%x\n", magic);
		return False;
	}

	in_uint32_le(s, modulus_len);
	modulus_len -= SEC_PADDING_SIZE;
	if ((modulus_len < 64) || (modulus_len > SEC_MAX_MODULUS_SIZE))
	{
		error("Bad server public key size (%u bits)\n", modulus_len * 8);
		return False;
	}

	in_uint8s(s, 8);	/* modulus_bits, unknown */
	in_uint8p(s, *exponent, SEC_EXPONENT_SIZE);
	in_uint8p(s, *modulus, modulus_len);
	in_uint8s(s, SEC_PADDING_SIZE);
	This->secure.server_public_key_len = modulus_len;

	return s_check(s);
}