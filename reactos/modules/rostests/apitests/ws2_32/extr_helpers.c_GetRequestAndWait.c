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
struct fd_set {int dummy; } ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,struct fd_set*) ; 
 int /*<<< orphan*/  FD_ZERO (struct fd_set*) ; 
 int /*<<< orphan*/  SCKTEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_SEND ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  select (int /*<<< orphan*/ ,struct fd_set*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

int GetRequestAndWait(SOCKET sck)
{
    const char szGetRequest[] = "GET / HTTP/1.0\r\n\r\n";
    int iResult;
    struct fd_set readable;

    /* Send the GET request */
    SCKTEST(send(sck, szGetRequest, strlen(szGetRequest), 0));
    ok(iResult == strlen(szGetRequest), "iResult = %d\n", iResult);
#if 0 /* breaks windows too */
    /* Shutdown the SEND connection */
    SCKTEST(shutdown(sck, SD_SEND));
#endif
    /* Wait until we're ready to read */
    FD_ZERO(&readable);
    FD_SET(sck, &readable);

    SCKTEST(select(0, &readable, NULL, NULL, NULL));
    
    return 1;
}