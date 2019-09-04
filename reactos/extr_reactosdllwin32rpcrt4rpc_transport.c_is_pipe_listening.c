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
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_S_NOT_LISTENING ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 scalar_t__ WaitNamedPipeA (char const*,int) ; 

__attribute__((used)) static RPC_STATUS is_pipe_listening(const char *pipe_name)
{
  return WaitNamedPipeA(pipe_name, 1) ? RPC_S_OK : RPC_S_NOT_LISTENING;
}