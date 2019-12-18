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
typedef  int /*<<< orphan*/  dec_server_record_t ;
typedef  int client_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 scalar_t__ WSACleanup () ; 
 int WSAGetLastError () ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int accept_connection (int /*<<< orphan*/ *) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  handle_clientreq (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * init_dec_server (int) ; 
 int /*<<< orphan*/  initialisation_win32 ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  terminate_dec_server (int /*<<< orphan*/ **) ; 

int main(int argc, char *argv[])
{

    dec_server_record_t *server_record;
    client_t client;
    int port = 50000;
    int erreur;
    (void)erreur;

    if (argc > 1) {
        port = atoi(argv[1]);
    }

#ifdef _WIN32
    erreur = WSAStartup(MAKEWORD(2, 2), &initialisation_win32);
    if (erreur != 0) {
        fprintf(stderr, "Erreur initialisation Winsock error : %d %d\n", erreur,
                WSAGetLastError());
    } else {
        printf("Initialisation Winsock\n");
    }
#endif /*_WIN32*/

    server_record = init_dec_server(port);

    while ((client = accept_connection(server_record)) != -1)
        if (!handle_clientreq(client, server_record)) {
            break;
        }

    terminate_dec_server(&server_record);

#ifdef _WIN32
    if (WSACleanup() != 0) {
        printf("\nError in WSACleanup : %d %d", erreur, WSAGetLastError());
    } else {
        printf("\nWSACleanup OK\n");
    }
#endif

    return 0;
}