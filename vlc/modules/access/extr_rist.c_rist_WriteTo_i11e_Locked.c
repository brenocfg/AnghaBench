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
typedef  int /*<<< orphan*/  vlc_mutex_t ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  rist_WriteTo_i11e (int,void const*,size_t,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rist_WriteTo_i11e_Locked(vlc_mutex_t lock, int fd, const void *buf, size_t len,
    const struct sockaddr *peer, socklen_t slen)
{
    vlc_mutex_lock( &lock );
    rist_WriteTo_i11e(fd, buf, len, peer, slen);
    vlc_mutex_unlock( &lock );
}