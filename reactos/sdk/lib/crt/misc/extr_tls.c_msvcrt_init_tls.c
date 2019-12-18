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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TLS_OUT_OF_INDEXES ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TlsAlloc () ; 
 scalar_t__ msvcrt_tls_index ; 

BOOL msvcrt_init_tls(void)
{
  msvcrt_tls_index = TlsAlloc();

  if (msvcrt_tls_index == TLS_OUT_OF_INDEXES)
  {
    ERR("TlsAlloc() failed!\n");
    return FALSE;
  }
  return TRUE;
}