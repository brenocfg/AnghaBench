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
struct MHD_Connection {int dummy; } ;
typedef  enum MHD_RequestTerminationCode { ____Placeholder_MHD_RequestTerminationCode } MHD_RequestTerminationCode ;

/* Variables and functions */
 int /*<<< orphan*/  MHD_RESPMEM_PERSISTENT ; 
 int mhd_respond_internal (struct MHD_Connection*,int,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 char* strjoina (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 

int mhd_respond(struct MHD_Connection *connection,
                enum MHD_RequestTerminationCode code,
                const char *message) {

        const char *fmt;

        fmt = strjoina(message, "\n");

        return mhd_respond_internal(connection, code,
                                    fmt, strlen(message) + 1,
                                    MHD_RESPMEM_PERSISTENT);
}