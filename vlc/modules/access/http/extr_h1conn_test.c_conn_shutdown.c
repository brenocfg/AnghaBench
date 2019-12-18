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

/* Variables and functions */
 int /*<<< orphan*/  external_tls ; 
 int /*<<< orphan*/  vlc_tls_Shutdown (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void conn_shutdown(bool duplex)
{
    vlc_tls_Shutdown(external_tls, duplex);
}