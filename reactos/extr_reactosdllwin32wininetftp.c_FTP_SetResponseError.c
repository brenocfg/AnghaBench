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
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_INTERNET_CANNOT_CONNECT ; 
 int ERROR_INTERNET_CONNECTION_ABORTED ; 
 int ERROR_INTERNET_EXTENDED_ERROR ; 
 int ERROR_INTERNET_LOGIN_FAILURE ; 
 int /*<<< orphan*/  INTERNET_SetLastError (int) ; 

__attribute__((used)) static DWORD FTP_SetResponseError(DWORD dwResponse)
{
    DWORD dwCode = 0;

    switch(dwResponse)
    {
    case 425: /* Cannot open data connection. */
        dwCode = ERROR_INTERNET_CANNOT_CONNECT;
        break;

    case 426: /* Connection closed, transer aborted. */
        dwCode = ERROR_INTERNET_CONNECTION_ABORTED;
        break;

    case 530: /* Not logged in. Login incorrect. */
        dwCode = ERROR_INTERNET_LOGIN_FAILURE;
        break;

    case 421: /* Service not available - Server may be shutting down. */
    case 450: /* File action not taken. File may be busy. */
    case 451: /* Action aborted. Server error. */
    case 452: /* Action not taken. Insufficient storage space on server. */
    case 500: /* Syntax error. Command unrecognized. */
    case 501: /* Syntax error. Error in parameters or arguments. */
    case 502: /* Command not implemented. */
    case 503: /* Bad sequence of commands. */
    case 504: /* Command not implemented for that parameter. */
    case 532: /* Need account for storing files */
    case 550: /* File action not taken. File not found or no access. */
    case 551: /* Requested action aborted. Page type unknown */
    case 552: /* Action aborted. Exceeded storage allocation */
    case 553: /* Action not taken. File name not allowed. */

    default:
        dwCode = ERROR_INTERNET_EXTENDED_ERROR;
        break;
    }

    INTERNET_SetLastError(dwCode);
    return dwCode;
}