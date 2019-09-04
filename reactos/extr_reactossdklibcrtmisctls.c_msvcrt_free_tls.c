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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TlsFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msvcrt_tls_index ; 

BOOL msvcrt_free_tls(void)
{
  if (!TlsFree(msvcrt_tls_index))
  {
    ERR("TlsFree() failed!\n");
    return FALSE;
  }
  return TRUE;
}