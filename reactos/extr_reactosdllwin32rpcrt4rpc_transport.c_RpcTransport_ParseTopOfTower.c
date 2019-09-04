#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int count_lhs; size_t count_rhs; scalar_t__ protid; } ;
typedef  TYPE_1__ twr_empty_floor_t ;
struct connection_ops {scalar_t__* epm_protocols; scalar_t__ (* parse_top_of_tower ) (unsigned char const*,size_t,char**,char**) ;int /*<<< orphan*/  name; } ;
typedef  scalar_t__ RPC_STATUS ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct connection_ops*) ; 
 scalar_t__ EPT_S_NOT_REGISTERED ; 
 char* I_RpcAllocate (scalar_t__) ; 
 scalar_t__ RPC_S_OK ; 
 struct connection_ops* conn_protseq_list ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (unsigned char const*,size_t,char**,char**) ; 

RPC_STATUS RpcTransport_ParseTopOfTower(const unsigned char *tower_data,
                                        size_t tower_size,
                                        char **protseq,
                                        char **networkaddr,
                                        char **endpoint)
{
    const twr_empty_floor_t *protocol_floor;
    const twr_empty_floor_t *floor4;
    const struct connection_ops *protseq_ops = NULL;
    RPC_STATUS status;
    unsigned int i;

    if (tower_size < sizeof(*protocol_floor))
        return EPT_S_NOT_REGISTERED;

    protocol_floor = (const twr_empty_floor_t *)tower_data;
    tower_data += sizeof(*protocol_floor);
    tower_size -= sizeof(*protocol_floor);
    if ((protocol_floor->count_lhs != sizeof(protocol_floor->protid)) ||
        (protocol_floor->count_rhs > tower_size))
        return EPT_S_NOT_REGISTERED;
    tower_data += protocol_floor->count_rhs;
    tower_size -= protocol_floor->count_rhs;

    floor4 = (const twr_empty_floor_t *)tower_data;
    if ((tower_size < sizeof(*floor4)) ||
        (floor4->count_lhs != sizeof(floor4->protid)))
        return EPT_S_NOT_REGISTERED;

    for(i = 0; i < ARRAY_SIZE(conn_protseq_list); i++)
        if ((protocol_floor->protid == conn_protseq_list[i].epm_protocols[0]) &&
            (floor4->protid == conn_protseq_list[i].epm_protocols[1]))
        {
            protseq_ops = &conn_protseq_list[i];
            break;
        }

    if (!protseq_ops)
        return EPT_S_NOT_REGISTERED;

    status = protseq_ops->parse_top_of_tower(tower_data, tower_size, networkaddr, endpoint);

    if ((status == RPC_S_OK) && protseq)
    {
        *protseq = I_RpcAllocate(strlen(protseq_ops->name) + 1);
        strcpy(*protseq, protseq_ops->name);
    }

    return status;
}