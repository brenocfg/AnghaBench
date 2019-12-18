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
typedef  enum nss_status { ____Placeholder_nss_status } nss_status ;

/* Variables and functions */
 int /*<<< orphan*/  getpwent_data ; 
 int systemd_setent (int /*<<< orphan*/ *) ; 

enum nss_status _nss_systemd_setpwent(int stayopen) {
        return systemd_setent(&getpwent_data);
}