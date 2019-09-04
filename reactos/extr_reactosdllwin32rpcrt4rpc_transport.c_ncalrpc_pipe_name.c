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
typedef  int /*<<< orphan*/  prefix ;

/* Variables and functions */
 char* I_RpcAllocate (scalar_t__) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *ncalrpc_pipe_name(const char *endpoint)
{
  static const char prefix[] = "\\\\.\\pipe\\lrpc\\";
  char *pipe_name;

  /* protseq=ncalrpc: supposed to use NT LPC ports,
   * but we'll implement it with named pipes for now */
  pipe_name = I_RpcAllocate(sizeof(prefix) + strlen(endpoint));
  strcat(strcpy(pipe_name, prefix), endpoint);
  return pipe_name;
}