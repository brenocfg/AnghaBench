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
typedef  int /*<<< orphan*/ * STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int ISO_PDU_CR ; 
 int /*<<< orphan*/  out_uint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_uint8p (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/ * tcp_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcp_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
iso_send_connection_request(RDPCLIENT * This, char *cookie)
{
	STREAM s;
	int cookielen = (int)strlen(cookie);
	int length = 11 + cookielen;

	s = tcp_init(This, length);

	if(s == NULL)
		return False;

	out_uint8(s, 3);	/* version */
	out_uint8(s, 0);	/* reserved */
	out_uint16_be(s, length);	/* length */

	out_uint8(s, length - 5);	/* hdrlen */
	out_uint8(s, ISO_PDU_CR);
	out_uint16(s, 0);	/* dst_ref */
	out_uint16(s, 0);	/* src_ref */
	out_uint8(s, 0);	/* class */

	out_uint8p(s, cookie, cookielen);

	s_mark_end(s);
	return tcp_send(This, s);
}