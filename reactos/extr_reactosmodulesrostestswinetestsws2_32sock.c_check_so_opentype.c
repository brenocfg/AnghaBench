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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  LPVOID ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_OPENTYPE ; 
 int /*<<< orphan*/  getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void check_so_opentype (void)
{
    int tmp = 1, len;
    len = sizeof (tmp);
    getsockopt ( INVALID_SOCKET, SOL_SOCKET, SO_OPENTYPE, (LPVOID) &tmp, &len );
    ok ( tmp == 0, "check_so_opentype: wrong startup value of SO_OPENTYPE: %d\n", tmp );
}