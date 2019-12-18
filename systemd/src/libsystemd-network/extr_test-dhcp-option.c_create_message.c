#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  sname; int /*<<< orphan*/  file; int /*<<< orphan*/  options; } ;
typedef  TYPE_1__ DHCPMessage ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (TYPE_1__*) ; 
 TYPE_1__* malloc0 (size_t) ; 
 int /*<<< orphan*/  memcpy_safe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DHCPMessage *create_message(uint8_t *options, uint16_t optlen,
                uint8_t *file, uint8_t filelen,
                uint8_t *sname, uint8_t snamelen) {
        DHCPMessage *message;
        size_t len = sizeof(DHCPMessage) + optlen;

        message = malloc0(len);
        assert_se(message);

        memcpy_safe(&message->options, options, optlen);
        memcpy_safe(&message->file, file, filelen);
        memcpy_safe(&message->sname, sname, snamelen);

        return message;
}