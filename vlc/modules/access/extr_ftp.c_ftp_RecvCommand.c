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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DummyLine ; 
 int ftp_RecvAnswer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ftp_RecvCommand( vlc_object_t *obj, access_sys_t *sys,
                            int *restrict codep, char **restrict strp )
{
    return ftp_RecvAnswer( obj, sys, codep, strp, DummyLine, NULL );
}