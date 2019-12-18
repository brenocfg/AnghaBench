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
#define  NSS_STATUS_NOTFOUND 132 
#define  NSS_STATUS_RETURN 131 
#define  NSS_STATUS_SUCCESS 130 
#define  NSS_STATUS_TRYAGAIN 129 
#define  NSS_STATUS_UNAVAIL 128 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static const char* nss_status_to_string(enum nss_status status, char *buf, size_t buf_len) {
        switch (status) {
        case NSS_STATUS_TRYAGAIN:
                return "NSS_STATUS_TRYAGAIN";
        case NSS_STATUS_UNAVAIL:
                return "NSS_STATUS_UNAVAIL";
        case NSS_STATUS_NOTFOUND:
                return "NSS_STATUS_NOTFOUND";
        case NSS_STATUS_SUCCESS:
                return "NSS_STATUS_SUCCESS";
        case NSS_STATUS_RETURN:
                return "NSS_STATUS_RETURN";
        default:
                snprintf(buf, buf_len, "%i", status);
                return buf;
        }
}