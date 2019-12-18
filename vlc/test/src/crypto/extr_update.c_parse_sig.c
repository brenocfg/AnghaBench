#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ signature_packet_t ;

/* Variables and functions */
 scalar_t__ BINARY_SIGNATURE ; 
 scalar_t__ SIGNATURE_PACKET ; 
 scalar_t__ TEXT_SIGNATURE ; 
 int /*<<< orphan*/  assert (int) ; 
 int* malloc (size_t) ; 
 int packet_header_len (int) ; 
 scalar_t__ packet_type (int) ; 
 int /*<<< orphan*/  parse_signature_packet (TYPE_1__*,int*,int) ; 
 int pgp_unarmor (char*,size_t,int*,size_t) ; 
 int scalar_number (int*,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void parse_sig(signature_packet_t *s, const uint8_t *sig)
{
    size_t sig_size = strlen((char*)sig);
    uint8_t *unarmored_sig = malloc((sig_size * 3) / 4 + 1);
    assert(sig[0] < 0x80); // ASCII
    int bytes = pgp_unarmor((char*)sig, sig_size, unarmored_sig, sig_size);

    assert(packet_type(unarmored_sig[0]) == SIGNATURE_PACKET);

    int header_len = packet_header_len(unarmored_sig[0]);
    assert(header_len == 1 || header_len == 2 || header_len == 4);
    assert(header_len < bytes);

    int len = scalar_number(&unarmored_sig[1], header_len);
    assert(len + header_len + 1 == bytes);

    assert(!parse_signature_packet(s, &unarmored_sig[1+header_len], len));

    assert(s->type == BINARY_SIGNATURE || s->type == TEXT_SIGNATURE);
}