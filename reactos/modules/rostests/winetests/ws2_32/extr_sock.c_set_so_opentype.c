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
typedef  int /*<<< orphan*/  optval ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_OPENTYPE ; 
 scalar_t__ getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_so_opentype ( BOOL overlapped )
{
    int optval = !overlapped, newval, len = sizeof (int);

    ok ( setsockopt ( INVALID_SOCKET, SOL_SOCKET, SO_OPENTYPE,
                      (LPVOID) &optval, sizeof (optval) ) == 0,
         "setting SO_OPENTYPE failed\n" );
    ok ( getsockopt ( INVALID_SOCKET, SOL_SOCKET, SO_OPENTYPE,
                      (LPVOID) &newval, &len ) == 0,
         "getting SO_OPENTYPE failed\n" );
    ok ( optval == newval, "failed to set SO_OPENTYPE\n" );
}