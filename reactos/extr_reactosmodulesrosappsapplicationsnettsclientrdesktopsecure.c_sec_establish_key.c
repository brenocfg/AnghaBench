#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_6__ {scalar_t__ server_public_key_len; int /*<<< orphan*/  crypted_random; } ;
struct TYPE_7__ {TYPE_1__ secure; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 scalar_t__ SEC_CLIENT_RANDOM ; 
 scalar_t__ SEC_PADDING_SIZE ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  out_uint8p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  out_uint8s (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_init (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sec_send (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
sec_establish_key(RDPCLIENT * This)
{
	uint32 length = This->secure.server_public_key_len + SEC_PADDING_SIZE;
	uint32 flags = SEC_CLIENT_RANDOM;
	STREAM s;

	s = sec_init(This, flags, length + 4);

	out_uint32_le(s, length);
	out_uint8p(s, This->secure.crypted_random, This->secure.server_public_key_len);
	out_uint8s(s, SEC_PADDING_SIZE);

	s_mark_end(s);
	sec_send(This, s, flags);
}