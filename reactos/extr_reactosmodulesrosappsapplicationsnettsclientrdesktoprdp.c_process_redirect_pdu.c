#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int uint32 ;
struct TYPE_9__ {int /*<<< orphan*/  redirect; } ;
struct TYPE_8__ {scalar_t__ p; } ;
typedef  TYPE_1__* STREAM ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  event_redirect (TYPE_2__*,int,int,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_uint32_le (TYPE_1__*,int) ; 
 int /*<<< orphan*/  in_uint8s (TYPE_1__*,int) ; 

__attribute__((used)) static BOOL
process_redirect_pdu(RDPCLIENT * This, STREAM s /*, uint32 * ext_disc_reason */ )
{
	uint32 flags;

	uint32 server_len;
	wchar_t * server;

	uint32 cookie_len;
	char * cookie;

	uint32 username_len;
	wchar_t * username;

	uint32 domain_len;
	wchar_t * domain;

	uint32 password_len;
	wchar_t * password;

	/* these 2 bytes are unknown, seem to be zeros */
	in_uint8s(s, 2);

	/* read connection flags */
	in_uint32_le(s, flags);

	/* read length of ip string */
	in_uint32_le(s, server_len);

	/* read ip string */
	server = (wchar_t *)s->p;
	in_uint8s(s, server_len);

	/* read length of cookie string */
	in_uint32_le(s, cookie_len);

	/* read cookie string (plain ASCII) */
	cookie = (char *)s->p;
	in_uint8s(s, cookie_len);

	/* read length of username string */
	in_uint32_le(s, username_len);

	/* read username string */
	username = (wchar_t *)s->p;
	in_uint8s(s, username_len);

	/* read length of domain string */
	in_uint32_le(s, domain_len);

	/* read domain string */
	domain = (wchar_t *)s->p;
	in_uint8s(s, domain_len);

	/* read length of password string */
	in_uint32_le(s, password_len);

	/* read password string */
	password = (wchar_t *)s->p;
	in_uint8s(s, password_len);

	This->redirect = True;

	return event_redirect
	(
		This,
		flags,
		server_len,
		server,
		cookie_len,
		cookie,
		username_len,
		username,
		domain_len,
		domain,
		password_len,
		password
	);
}