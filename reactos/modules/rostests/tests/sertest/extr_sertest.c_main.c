#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int DCBlength; int BaudRate; int ByteSize; int /*<<< orphan*/  StopBits; int /*<<< orphan*/  Parity; } ;
typedef  char TCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  TYPE_1__ DCB ;
typedef  int CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 char* APP_VERSION_STR ; 
 int BUFSIZE ; 
 int /*<<< orphan*/  CLRDTR ; 
 int /*<<< orphan*/  CLRRTS ; 
 scalar_t__ ClearCommError (scalar_t__,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EscapeCommFunction (scalar_t__,int /*<<< orphan*/ ) ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetCommState (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PORTNAME_LEN ; 
 int /*<<< orphan*/  NOPARITY ; 
 int /*<<< orphan*/  ONESTOPBIT ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ ReadFile (scalar_t__,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SETDTR ; 
 int /*<<< orphan*/  SETRTS ; 
 scalar_t__ SetCommState (scalar_t__,TYPE_1__*) ; 
 scalar_t__ WriteFile (scalar_t__,int*,int,int*,int /*<<< orphan*/ *) ; 
 char* _T (char*) ; 
 int /*<<< orphan*/  dwNumRead ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 

int main(int argc, char *argv[])
{
    CHAR txBuffer[BUFSIZE];
    CHAR rxBuffer[BUFSIZE];
    DWORD dwBaud = 9600;
    DWORD dwNumWritten;
    DWORD dwErrors;
    DCB dcb;
    BOOL bResult;
    HANDLE hPort;
    int i;
    int j;
    int k;
	int nPortNum = 1;

	TCHAR szPortName[MAX_PORTNAME_LEN];

    if (argc > 1) {
        //sscanf(argv[1], "%d", &dwBaud);
        sscanf(argv[1], "%d", &nPortNum);
    }
	sprintf(szPortName, _T("COM%d"), nPortNum);

    printf("Serial Port Test Application Version %s\n", APP_VERSION_STR);
    printf("Attempting to open serial port %d - %s\n", nPortNum, szPortName);
    hPort = CreateFile(szPortName,
                       GENERIC_READ|GENERIC_WRITE,
                       0,     // exclusive
                       NULL,  // sec attr
                       OPEN_EXISTING,
                       0,     // no attributes
                       NULL); // no template

    if (hPort == (HANDLE)-1) {
        printf("ERROR: CreateFile() failed with result: %lx\n", (DWORD)hPort);
        return 1;
    }
    printf("CreateFile() returned: %lx\n", (DWORD)hPort);

    printf("Fiddling with DTR and RTS control lines...\n");
	for (i = 0; i < 100; i++) {
	bResult = EscapeCommFunction(hPort, SETDTR);
    if (!bResult) {
        printf("WARNING: EscapeCommFunction(SETDTR) failed: %lx\n", (DWORD)bResult);
    }
	bResult = EscapeCommFunction(hPort, SETRTS);
    if (!bResult) {
        printf("WARNING: EscapeCommFunction(SETRTS) failed: %lx\n", (DWORD)bResult);
    }
	for (j = 0; j < 1000; j++) {
		k *= j;
	}
/*
#define CLRDTR	(6)
#define CLRRTS	(4)
#define SETDTR	(5)
#define SETRTS	(3)
#define SETXOFF	(1)
#define SETXON	(2)
#define SETBREAK	(8)
#define CLRBREAK	(9)
 */
	bResult = EscapeCommFunction(hPort, CLRDTR);
    if (!bResult) {
        printf("WARNING: EscapeCommFunction(CLRDTR) failed: %lx\n", (DWORD)bResult);
    }
	bResult = EscapeCommFunction(hPort, CLRRTS);
    if (!bResult) {
        printf("WARNING: EscapeCommFunction(CLRRTS) failed: %lx\n", (DWORD)bResult);
    }
	}
    printf("Getting the default line characteristics...\n");
	dcb.DCBlength = sizeof(DCB);
	if (!GetCommState(hPort, &dcb)) {
        printf("ERROR: failed to get the dcb: %ld\n", GetLastError());
        return 2;
    }
    printf("Setting the line characteristics to 9600,8,N,1\n");
    dcb.BaudRate = dwBaud;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;

    bResult = SetCommState(hPort, &dcb);
    if (!bResult) {
        printf("ERROR: failed to set the comm state: %lx\n", (DWORD)bResult);
        return 3;
    }
	for (i = 0; i < BUFSIZE; i++) {
        txBuffer[i] = (CHAR)i;
        //printf(" %d ", txBuffer[i]);
        rxBuffer[i] = 0xFF;
    }
    printf("\n");
    printf("Writting transmit buffer to the serial port\n");
    bResult = WriteFile(hPort, txBuffer, BUFSIZE, &dwNumWritten, NULL);
    if (!bResult) {
        printf("ERROR: failed to write to the serial port: %lx\n", (DWORD)bResult);
        return 4;
    }
    printf("WriteFile() returned: %lx, byteswritten: %lx\n", (DWORD)bResult, dwNumWritten);
#if 0
	printf("Attempting to read %d bytes from the serial port\n", BUFSIZE);
    bResult = ReadFile(hPort, rxBuffer, BUFSIZE, &dwNumRead, NULL);
	if (!bResult) {
        printf("ERROR: failed to read from the serial port: %lx\n", (DWORD)bResult);
        return 5;
    }
    printf("ReadFile() returned: %lx, bytesread: %lx\n", (DWORD)bResult, dwNumRead);
    for (i = 0; i < BUFSIZE; i++) {
        printf(" %d ",rxBuffer[i]);
    }
#endif
    printf("Attempting to close the serial port\n");
    bResult = ClearCommError(hPort, &dwErrors, NULL);
    printf("ClearCommError returned: %lx, dwErrors: %lx\n", (DWORD)bResult, dwErrors);
    bResult = CloseHandle(hPort);
    if (!bResult) {
        printf("ERROR: failed to close the serial port: %lx\n", (DWORD)bResult);
        return 6;
    }
    printf("Finished\n");
    return 0;
}