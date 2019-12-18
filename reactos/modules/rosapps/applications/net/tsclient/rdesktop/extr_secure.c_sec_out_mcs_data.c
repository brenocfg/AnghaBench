#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_8__ {int num_channels; int width; int height; int keylayout; int keyboard_type; int keyboard_subtype; int keyboard_functionkeys; int server_depth; TYPE_2__* channel_defs; TYPE_1__* channels; scalar_t__ encryption; scalar_t__ console_session; scalar_t__ use_rdp5; } ;
struct TYPE_7__ {int /*<<< orphan*/  options; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 int SEC_TAG_CLI_4 ; 
 int SEC_TAG_CLI_CHANNELS ; 
 int SEC_TAG_CLI_CRYPT ; 
 int SEC_TAG_CLI_INFO ; 
 int /*<<< orphan*/  out_uint16_be (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32_be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8a (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdp_out_unistr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sec_out_mcs_data(RDPCLIENT * This, STREAM s, wchar_t * hostname)
{
	int hostlen = 2 * (int)wcslen(hostname);
	int length = 158 + 76 + 12 + 4;
	unsigned int i;

	if (This->num_channels > 0)
		length += This->num_channels * 12 + 8;

	if (hostlen > 30)
		hostlen = 30;

	/* Generic Conference Control (T.124) ConferenceCreateRequest */
	out_uint16_be(s, 5);
	out_uint16_be(s, 0x14);
	out_uint8(s, 0x7c);
	out_uint16_be(s, 1);

	out_uint16_be(s, (length | 0x8000));	/* remaining length */

	out_uint16_be(s, 8);	/* length? */
	out_uint16_be(s, 16);
	out_uint8(s, 0);
	out_uint16_le(s, 0xc001);
	out_uint8(s, 0);

	out_uint32_le(s, 0x61637544);	/* OEM ID: "Duca", as in Ducati. */
	out_uint16_be(s, ((length - 14) | 0x8000));	/* remaining length */

	/* Client information */
	out_uint16_le(s, SEC_TAG_CLI_INFO);
	out_uint16_le(s, 212);	/* length */
	out_uint16_le(s, This->use_rdp5 ? 4 : 1);	/* RDP version. 1 == RDP4, 4 == RDP5. */
	out_uint16_le(s, 8);
	out_uint16_le(s, This->width);
	out_uint16_le(s, This->height);
	out_uint16_le(s, 0xca01);
	out_uint16_le(s, 0xaa03);
	out_uint32_le(s, This->keylayout);
	out_uint32_le(s, 2600);	/* Client build. We are now 2600 compatible :-) */

	/* Unicode name of client, padded to 32 bytes */
	rdp_out_unistr(This, s, hostname, hostlen);
	out_uint8s(s, 30 - hostlen);

	/* See
	   http://msdn.microsoft.com/library/default.asp?url=/library/en-us/wceddk40/html/cxtsksupportingremotedesktopprotocol.asp */
	out_uint32_le(s, This->keyboard_type);
	out_uint32_le(s, This->keyboard_subtype);
	out_uint32_le(s, This->keyboard_functionkeys);
	out_uint8s(s, 64);	/* reserved? 4 + 12 doublewords */
	out_uint16_le(s, 0xca01);	/* colour depth? */
	out_uint16_le(s, 1);

	out_uint32(s, 0);
	out_uint8(s, This->server_depth);
	out_uint16_le(s, 0x0700);
	out_uint8(s, 0);
	out_uint32_le(s, 1);
	out_uint8s(s, 64);	/* End of client info */

	out_uint16_le(s, SEC_TAG_CLI_4);
	out_uint16_le(s, 12);
	out_uint32_le(s, This->console_session ? 0xb : 9);
	out_uint32(s, 0);

	/* Client encryption settings */
	out_uint16_le(s, SEC_TAG_CLI_CRYPT);
	out_uint16_le(s, 12);	/* length */
	out_uint32_le(s, This->encryption ? 0x3 : 0);	/* encryption supported, 128-bit supported */
	out_uint32(s, 0);	/* Unknown */

	DEBUG_RDP5(("This->num_channels is %d\n", This->num_channels));
	if (This->num_channels > 0)
	{
		out_uint16_le(s, SEC_TAG_CLI_CHANNELS);
		out_uint16_le(s, This->num_channels * 12 + 8);	/* length */
		out_uint32_le(s, This->num_channels);	/* number of virtual channels */
		for (i = 0; i < This->num_channels; i++)
		{
			DEBUG_RDP5(("Requesting channel %s\n", This->channels[i].name));
			out_uint8a(s, This->channel_defs[i].name, 8);
			out_uint32_be(s, This->channel_defs[i].options);
		}
	}

	s_mark_end(s);
}