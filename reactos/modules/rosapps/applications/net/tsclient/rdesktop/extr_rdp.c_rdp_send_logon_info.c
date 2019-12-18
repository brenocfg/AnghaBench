#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int uint32 ;
typedef  int time_t ;
struct TYPE_7__ {int server_rdp_version; int rdp5_performanceflags; int /*<<< orphan*/  use_rdp5; scalar_t__ encryption; } ;
typedef  int /*<<< orphan*/ * STREAM ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 int /*<<< orphan*/  False ; 
 int RDP_LOGON_AUTO ; 
 int RDP_LOGON_BLOB ; 
 int SEC_ENCRYPT ; 
 int SEC_LOGON_INFO ; 
 int /*<<< orphan*/  gmtime (int*) ; 
 int /*<<< orphan*/  localtime (int*) ; 
 int mktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_uint8s (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rdp_out_unistr (TYPE_1__*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sec_init (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  sec_send (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 char* tcp_get_address (TYPE_1__*) ; 
 int time (int /*<<< orphan*/ *) ; 
 int wcslen (char*) ; 

__attribute__((used)) static BOOL
rdp_send_logon_info(RDPCLIENT * This, uint32 flags, wchar_t *domain, wchar_t *user,
		    wchar_t *password, wchar_t *program, wchar_t *directory)
{
	wchar_t *ipaddr = tcp_get_address(This);
	int len_domain = 2 * (int)wcslen(domain);
	int len_user = 2 * (int)wcslen(user);
	int len_password = 2 * (int)wcslen(password);
	int len_program = 2 * (int)wcslen(program);
	int len_directory = 2 * (int)wcslen(directory);
	int len_ip = 2 * (int)wcslen(ipaddr);
	int len_dll = 2 * (int)wcslen(L"C:\\WINNT\\System32\\mstscax.dll");
	int packetlen = 0;
	uint32 sec_flags = This->encryption ? (SEC_LOGON_INFO | SEC_ENCRYPT) : SEC_LOGON_INFO;
	STREAM s;
	time_t t = time(NULL);
	time_t tzone;

	if (!This->use_rdp5 || 1 == This->server_rdp_version)
	{
		DEBUG_RDP5(("Sending RDP4-style Logon packet\n"));

		s = sec_init(This, sec_flags, 18 + len_domain + len_user + len_password
			     + len_program + len_directory + 10);

		if(s == NULL)
			return False;

		out_uint32(s, 0);
		out_uint32_le(s, flags);
		out_uint16_le(s, len_domain);
		out_uint16_le(s, len_user);
		out_uint16_le(s, len_password);
		out_uint16_le(s, len_program);
		out_uint16_le(s, len_directory);
		rdp_out_unistr(This, s, domain, len_domain);
		rdp_out_unistr(This, s, user, len_user);
		rdp_out_unistr(This, s, password, len_password);
		rdp_out_unistr(This, s, program, len_program);
		rdp_out_unistr(This, s, directory, len_directory);
	}
	else
	{

		flags |= RDP_LOGON_BLOB;
		DEBUG_RDP5(("Sending RDP5-style Logon packet\n"));
		packetlen = 4 +	/* Unknown uint32 */
			4 +	/* flags */
			2 +	/* len_domain */
			2 +	/* len_user */
			(flags & RDP_LOGON_AUTO ? 2 : 0) +	/* len_password */
			(flags & RDP_LOGON_BLOB ? 2 : 0) +	/* Length of BLOB */
			2 +	/* len_program */
			2 +	/* len_directory */
			(0 < len_domain ? len_domain : 2) +	/* domain */
			len_user + (flags & RDP_LOGON_AUTO ? len_password : 0) + 0 +	/* We have no 512 byte BLOB. Perhaps we must? */
			(flags & RDP_LOGON_BLOB && !(flags & RDP_LOGON_AUTO) ? 2 : 0) +	/* After the BLOB is a unknown int16. If there is a BLOB, that is. */
			(0 < len_program ? len_program : 2) + (0 < len_directory ? len_directory : 2) + 2 +	/* Unknown (2) */
			2 +	/* Client ip length */
			len_ip +	/* Client ip */
			2 +	/* DLL string length */
			len_dll +	/* DLL string */
			2 +	/* Unknown */
			2 +	/* Unknown */
			64 +	/* Time zone #0 */
			2 +	/* Unknown */
			64 +	/* Time zone #1 */
			32;	/* Unknown */

		s = sec_init(This, sec_flags, packetlen);
		DEBUG_RDP5(("Called sec_init with packetlen %d\n", packetlen));

		if(s == NULL)
			return False;

		out_uint32(s, 0);	/* Unknown */
		out_uint32_le(s, flags);
		out_uint16_le(s, len_domain);
		out_uint16_le(s, len_user);
		if (flags & RDP_LOGON_AUTO)
		{
			out_uint16_le(s, len_password);

		}
		if (flags & RDP_LOGON_BLOB && !(flags & RDP_LOGON_AUTO))
		{
			out_uint16_le(s, 0);
		}
		out_uint16_le(s, len_program);
		out_uint16_le(s, len_directory);
		if (0 < len_domain)
			rdp_out_unistr(This, s, domain, len_domain);
		else
			out_uint16_le(s, 0);
		rdp_out_unistr(This, s, user, len_user);
		if (flags & RDP_LOGON_AUTO)
		{
			rdp_out_unistr(This, s, password, len_password);
		}
		if (flags & RDP_LOGON_BLOB && !(flags & RDP_LOGON_AUTO))
		{
			out_uint16_le(s, 0);
		}
		if (0 < len_program)
		{
			rdp_out_unistr(This, s, program, len_program);

		}
		else
		{
			out_uint16_le(s, 0);
		}
		if (0 < len_directory)
		{
			rdp_out_unistr(This, s, directory, len_directory);
		}
		else
		{
			out_uint16_le(s, 0);
		}
		out_uint16_le(s, 2);
		out_uint16_le(s, len_ip + 2);	/* Length of client ip */
		rdp_out_unistr(This, s, ipaddr, len_ip);
		out_uint16_le(s, len_dll + 2);
		rdp_out_unistr(This, s, L"C:\\WINNT\\System32\\mstscax.dll", len_dll);

		tzone = (mktime(gmtime(&t)) - mktime(localtime(&t))) / 60;
		out_uint32_le(s, (uint32)tzone);

		rdp_out_unistr(This, s, L"GTB, normaltid", 2 * (int)wcslen(L"GTB, normaltid"));
		out_uint8s(s, 62 - 2 * wcslen(L"GTB, normaltid"));

		out_uint32_le(s, 0x0a0000);
		out_uint32_le(s, 0x050000);
		out_uint32_le(s, 3);
		out_uint32_le(s, 0);
		out_uint32_le(s, 0);

		rdp_out_unistr(This, s, L"GTB, sommartid", 2 * (int)wcslen(L"GTB, sommartid"));
		out_uint8s(s, 62 - 2 * wcslen(L"GTB, sommartid"));

		out_uint32_le(s, 0x30000);
		out_uint32_le(s, 0x050000);
		out_uint32_le(s, 2);
		out_uint32(s, 0);
		out_uint32_le(s, 0xffffffc4);
		out_uint32_le(s, 0xfffffffe);
		out_uint32_le(s, This->rdp5_performanceflags);
		out_uint32(s, 0);


	}
	s_mark_end(s);
	return sec_send(This, s, sec_flags);
}