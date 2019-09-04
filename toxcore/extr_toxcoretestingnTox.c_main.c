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
typedef  int /*<<< orphan*/  whoami ;
typedef  char uint8_t ;
typedef  size_t uint16_t ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 int ERR ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  TOX_MAX_NAME_LENGTH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  appender (char*,char) ; 
 size_t atoi (char*) ; 
 int cmdline_parsefor_ipv46 (int,char**,char*) ; 
 char* data_file_name ; 
 int /*<<< orphan*/  do_refresh () ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  file_print_control ; 
 int /*<<< orphan*/  file_request_accept ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  get_id (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* hex_string_to_bin (char*) ; 
 int /*<<< orphan*/  initscr () ; 
 char* input_line ; 
 scalar_t__ isalnum (int) ; 
 scalar_t__ ispunct (int) ; 
 int /*<<< orphan*/  line_eval (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * load_data () ; 
 int /*<<< orphan*/  new_lines (char*) ; 
 int /*<<< orphan*/  nodelay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  print_groupmessage ; 
 int /*<<< orphan*/  print_groupnamelistchange ; 
 int /*<<< orphan*/  print_help (char*) ; 
 int /*<<< orphan*/  print_invite ; 
 int /*<<< orphan*/  print_message ; 
 int /*<<< orphan*/  print_nickchange ; 
 int /*<<< orphan*/  print_online ; 
 int /*<<< orphan*/  print_request ; 
 int /*<<< orphan*/  print_statuschange ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  raw () ; 
 int /*<<< orphan*/  save_data_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int timeout_getch (int /*<<< orphan*/ *) ; 
 int tox_bootstrap (int /*<<< orphan*/ *,char*,size_t,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_callback_file_chunk_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_callback_file_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_callback_file_recv_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_callback_file_recv_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_callback_friend_connection_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_callback_friend_message (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_callback_friend_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_callback_friend_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_callback_friend_status_message (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_callback_group_invite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_callback_group_message (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_callback_group_namelist_change (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_file_chunk_request ; 
 int /*<<< orphan*/  tox_iterate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_kill (int /*<<< orphan*/ *) ; 
 scalar_t__ tox_self_get_connection_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_self_get_name (int /*<<< orphan*/ *,char*) ; 
 size_t tox_self_get_name_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_file ; 
 int /*<<< orphan*/  x ; 
 int /*<<< orphan*/  y ; 

int main(int argc, char *argv[])
{
    /* minimalistic locale support (i.e. when printing dates) */
    setlocale(LC_ALL, "");

    if (argc < 4) {
        if ((argc == 2) && !strcmp(argv[1], "-h")) {
            print_help(argv[0]);
            exit(0);
        }

        printf("Usage: %s [--ipv4|--ipv6] IP PORT KEY [-f keyfile] (or %s -h for help)\n", argv[0], argv[0]);
        exit(0);
    }

    /* let user override default by cmdline */
    uint8_t ipv6enabled = 1; /* x */
    int argvoffset = cmdline_parsefor_ipv46(argc, argv, &ipv6enabled);

    if (argvoffset < 0)
        exit(1);

    int on = 0;
    char *filename = "data";
    char idstring[200] = {0};
    Tox *m;

    /* [-f keyfile] MUST be last two arguments, no point in walking over the list
     * especially not a good idea to accept it anywhere in the middle */
    if (argc > argvoffset + 3)
        if (!strcmp(argv[argc - 2], "-f"))
            filename = argv[argc - 1];

    data_file_name = filename;
    m = load_data();

    if ( !m ) {
        fputs("Failed to allocate Messenger datastructure", stderr);
        exit(0);
    }

    save_data_file(m, filename);

    tox_callback_friend_request(m, print_request, NULL);
    tox_callback_friend_message(m, print_message, NULL);
    tox_callback_friend_name(m, print_nickchange, NULL);
    tox_callback_friend_status_message(m, print_statuschange, NULL);
    tox_callback_group_invite(m, print_invite, NULL);
    tox_callback_group_message(m, print_groupmessage, NULL);
    tox_callback_file_recv_chunk(m, write_file, NULL);
    tox_callback_file_recv_control(m, file_print_control, NULL);
    tox_callback_file_recv(m, file_request_accept, NULL);
    tox_callback_file_chunk_request(m, tox_file_chunk_request, NULL);
    tox_callback_group_namelist_change(m, print_groupnamelistchange, NULL);
    tox_callback_friend_connection_status(m, print_online, NULL);

    initscr();
    noecho();
    raw();
    getmaxyx(stdscr, y, x);

    new_lines("/h for list of commands");
    get_id(m, idstring);
    new_lines(idstring);
    strcpy(input_line, "");

    uint16_t port = atoi(argv[argvoffset + 2]);
    unsigned char *binary_string = hex_string_to_bin(argv[argvoffset + 3]);
    int res = tox_bootstrap(m, argv[argvoffset + 1], port, binary_string, NULL);

    if (!res) {
        printf("Failed to convert \"%s\" into an IP address. Exiting...\n", argv[argvoffset + 1]);
        endwin();
        exit(1);
    }

    nodelay(stdscr, TRUE);

    new_lines("[i] change username with /n");
    uint8_t name[TOX_MAX_NAME_LENGTH + 1];
    tox_self_get_name(m, name);
    uint16_t namelen = tox_self_get_name_size(m);
    name[namelen] = 0;

    if (namelen > 0) {
        char whoami[128 + TOX_MAX_NAME_LENGTH];
        snprintf(whoami, sizeof(whoami), "[i] your current username is: %s", name);
        new_lines(whoami);
    }

    time_t timestamp0 = time(NULL);

    while (1) {
        if (on == 0) {
            if (tox_self_get_connection_status(m)) {
                new_lines("[i] connected to DHT");
                on = 1;
            } else {
                time_t timestamp1 = time(NULL);

                if (timestamp0 + 10 < timestamp1) {
                    timestamp0 = timestamp1;
                    tox_bootstrap(m, argv[argvoffset + 1], port, binary_string, NULL);
                }
            }
        }

        tox_iterate(m);
        do_refresh();

        int c = timeout_getch(m);

        if (c == ERR || c == 27)
            continue;

        getmaxyx(stdscr, y, x);

        if ((c == 0x0d) || (c == 0x0a)) {
            line_eval(m, input_line);
            strcpy(input_line, "");
        } else if (c == 8 || c == 127) {
            input_line[strlen(input_line) - 1] = '\0';
        } else if (isalnum(c) || ispunct(c) || c == ' ') {
            appender(input_line, (char) c);
        }
    }

    free(binary_string);
    save_data_file(m, filename);
    tox_kill(m);
    endwin();
    return 0;
}