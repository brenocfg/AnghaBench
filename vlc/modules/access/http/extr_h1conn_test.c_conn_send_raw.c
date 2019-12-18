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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  external_tls ; 
 scalar_t__ vlc_tls_Write (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static void conn_send_raw(const void *buf, size_t len)
{
    ssize_t val = vlc_tls_Write(external_tls, buf, len);
    assert((size_t)val == len);
}