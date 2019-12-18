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
typedef  int /*<<< orphan*/  server_record_t ;
typedef  int /*<<< orphan*/  QR_t ;
typedef  scalar_t__ OPJ_BOOL ;

/* Variables and functions */
 scalar_t__ FCGI_Accept () ; 
 int /*<<< orphan*/  FCGI_stderr ; 
 int /*<<< orphan*/  FCGI_stdout ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  QUIT_SIGNAL ; 
 scalar_t__ WSACleanup () ; 
 int WSAGetLastError () ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_QRprocess (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/ * init_JPIPserver (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialisation_win32 ; 
 int /*<<< orphan*/  local_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_querystring (char*) ; 
 scalar_t__ process_JPIPrequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_responsedata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  terminate_JPIPserver (int /*<<< orphan*/ **) ; 

int main(void)
{
    server_record_t *server_record;
#ifdef SERVER
    char *query_string;
#endif

#ifdef _WIN32
    int erreur = WSAStartup(MAKEWORD(2, 2), &initialisation_win32);
    if (erreur != 0) {
        fprintf(stderr, "Erreur initialisation Winsock error : %d %d\n", erreur,
                WSAGetLastError());
    } else {
        fprintf(stderr, "Initialisation Winsock\n");
    }
#endif /*_WIN32*/

    server_record = init_JPIPserver(60000, 0);

#ifdef SERVER
    while (FCGI_Accept() >= 0)
#else

    char query_string[128];
    while (fgets(query_string, 128, stdin) && query_string[0] != '\n')
#endif
    {
        QR_t *qr;
        OPJ_BOOL parse_status;

#ifdef SERVER
        query_string = getenv("QUERY_STRING");
#endif /*SERVER*/

        if (strcmp(query_string, QUIT_SIGNAL) == 0) {
            break;
        }

        qr = parse_querystring(query_string);

        parse_status = process_JPIPrequest(server_record, qr);

#ifndef SERVER
        local_log(OPJ_TRUE, OPJ_TRUE, parse_status, OPJ_FALSE, qr, server_record);
#endif

        if (parse_status) {
            send_responsedata(server_record, qr);
        } else {
            fprintf(FCGI_stderr, "Error: JPIP request failed\n");
            fprintf(FCGI_stdout, "\r\n");
        }

        end_QRprocess(server_record, &qr);
    }

    fprintf(FCGI_stderr, "JPIP server terminated by a client request\n");

    terminate_JPIPserver(&server_record);

#ifdef _WIN32
    if (WSACleanup() != 0) {
        fprintf(stderr, "\nError in WSACleanup : %d %d", erreur, WSAGetLastError());
    } else {
        fprintf(stderr, "\nWSACleanup OK\n");
    }
#endif

    return 0;
}