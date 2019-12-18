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
 int /*<<< orphan*/  ECONNABORTED ; 
 int /*<<< orphan*/  ECONNREFUSED ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  EHOSTDOWN ; 
 int /*<<< orphan*/  EHOSTUNREACH ; 
 int /*<<< orphan*/  ENETDOWN ; 
 int /*<<< orphan*/  ENETRESET ; 
 int /*<<< orphan*/  ENETUNREACH ; 
 int /*<<< orphan*/  ENONET ; 
 int /*<<< orphan*/  ENOPROTOOPT ; 
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  EPROTO ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abs (int) ; 

__attribute__((used)) static inline bool ERRNO_IS_DISCONNECT(int r) {
        return IN_SET(abs(r),
                      ECONNABORTED,
                      ECONNREFUSED,
                      ECONNRESET,
                      EHOSTDOWN,
                      EHOSTUNREACH,
                      ENETDOWN,
                      ENETRESET,
                      ENETUNREACH,
                      ENONET,
                      ENOPROTOOPT,
                      ENOTCONN,
                      EPIPE,
                      EPROTO,
                      ESHUTDOWN);
}