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
struct TYPE_5__ {int /*<<< orphan*/  Protseq; } ;
typedef  TYPE_1__ RpcBinding ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  RPCRT4_AllocBinding (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPCRT4_strdupWtoA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

__attribute__((used)) static RPC_STATUS RPCRT4_CreateBindingW(RpcBinding** Binding, BOOL server, LPCWSTR Protseq)
{
  RpcBinding* NewBinding;

  RPCRT4_AllocBinding(&NewBinding, server);
  NewBinding->Protseq = RPCRT4_strdupWtoA(Protseq);

  TRACE("binding: %p\n", NewBinding);
  *Binding = NewBinding;

  return RPC_S_OK;
}