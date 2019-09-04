#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum secure_packet_direction { ____Placeholder_secure_packet_direction } secure_packet_direction ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* secure_packet ) (TYPE_2__*,int,int /*<<< orphan*/ *,unsigned int,unsigned char*,unsigned int,int /*<<< orphan*/ *,unsigned char*,unsigned int) ;} ;
typedef  int /*<<< orphan*/  RpcPktHdr ;
typedef  TYPE_2__ RpcConnection ;
typedef  int /*<<< orphan*/  RpcAuthVerifier ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int /*<<< orphan*/ *,unsigned int,unsigned char*,unsigned int,int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 

__attribute__((used)) static inline RPC_STATUS rpcrt4_conn_secure_packet(
    RpcConnection *conn, enum secure_packet_direction dir,
    RpcPktHdr *hdr, unsigned int hdr_size, unsigned char *stub_data,
    unsigned int stub_data_size, RpcAuthVerifier *auth_hdr,
    unsigned char *auth_value, unsigned int auth_value_size)
{
    return conn->ops->secure_packet(conn, dir, hdr, hdr_size, stub_data, stub_data_size, auth_hdr, auth_value, auth_value_size);
}