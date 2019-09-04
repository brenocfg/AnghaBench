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
typedef  int /*<<< orphan*/  uint8_t ;
struct remote_message_header {int /*<<< orphan*/  session; int /*<<< orphan*/  destination; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  to_bigendian (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
header_to_message(const struct remote_message_header * header, uint8_t * message) {
	to_bigendian(message , header->source);
	to_bigendian(message+4 , header->destination);
	to_bigendian(message+8 , header->session);
}