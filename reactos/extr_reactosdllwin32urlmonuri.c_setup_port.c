#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  port_value; void* has_port; } ;
typedef  TYPE_2__ parse_data ;
struct TYPE_10__ {int modified_props; TYPE_1__* uri; int /*<<< orphan*/  port; scalar_t__ has_port; } ;
typedef  TYPE_3__ UriBuilder ;
struct TYPE_8__ {int /*<<< orphan*/  port; scalar_t__ has_port; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_3__ const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int Uri_HAS_PORT ; 

__attribute__((used)) static void setup_port(const UriBuilder *builder, parse_data *data, DWORD flags) {
    if(builder->modified_props & Uri_HAS_PORT) {
        if(builder->has_port) {
            data->has_port = TRUE;
            data->port_value = builder->port;
        }
    } else if(builder->uri && builder->uri->has_port) {
        data->has_port = TRUE;
        data->port_value = builder->uri->port;
    }

    if(data->has_port)
        TRACE("(%p %p %x): Using %u as port for IUri.\n", builder, data, flags, data->port_value);
}