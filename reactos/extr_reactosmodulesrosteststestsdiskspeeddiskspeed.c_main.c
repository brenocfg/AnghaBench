#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_11__ {char* VendorId; } ;
struct TYPE_10__ {int Offset; } ;
typedef  TYPE_1__* PBYTE ;
typedef  TYPE_1__ OVERLAPPED ;
typedef  TYPE_3__ INQUIRYDATA ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetInquiryData (scalar_t__,TYPE_3__*) ; 
 int GetTickCount () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,TYPE_1__*,int,int*,TYPE_1__*) ; 
 TYPE_1__* VirtualAlloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VirtualFree (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

int main(void)
{
    HANDLE hDevice;
    OVERLAPPED ov;

    PBYTE Buffer = NULL ;
    DWORD Start;
    DWORD dwReturned;
    DWORD dwReadTotal;
    DWORD Size;
    BOOL Result;
    ULONG Drive;
    CHAR Name[20];

    INQUIRYDATA InquiryData;


    Drive = 0;
    while (1)
      {
        sprintf(Name, "\\\\.\\PHYSICALDRIVE%ld", Drive);
	hDevice = CreateFile(Name,
	                     GENERIC_READ,
			     FILE_SHARE_READ,
			     NULL,
			     OPEN_EXISTING,
			     0,
			     NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
	  {
	    if (Drive > 0)
	      {
	        VirtualFree(Buffer, 512 * 1024, MEM_RELEASE);
	      }
	    else
	      {
	        printf("Cannot open '%s'\n", Name);
	      }
	    break;
	  }
        if (Drive == 0)
	  {
            printf("Transfer Size (kB)           1     2     4     8    16    32    64   128   256\n");
            printf("Transfer Rate (MB/s)\n");
            printf("-------------------------------------------------------------------------------\n");

	    Buffer = VirtualAlloc(NULL, 512 * 1024, MEM_COMMIT, PAGE_READWRITE);
	  }
        Result = GetInquiryData(hDevice, &InquiryData);
        if (Result)
	  {
            printf("%.24s ", InquiryData.VendorId);
	  }
	else
	  {
	    printf("Disk %ld                   ", Drive + 1);
	  }
        Size = 1024;
        memset(&ov, 0, sizeof(OVERLAPPED));
	while (Size <= 256 * 1024)
	  {
	    memset(Buffer, 0, Size);
	    dwReadTotal = 0;

            Start = GetTickCount() + 2000;
	    while (Start > GetTickCount())
	      {
	        Result = ReadFile(hDevice, Buffer, Size, &dwReturned, &ov);
		if (Result)
		  {
		    dwReadTotal += dwReturned;
		    ov.Offset += dwReturned;
		  }
	      }
	    dwReadTotal /= 2048;
            printf("%3ld.%ld ", dwReadTotal / 1024, (dwReadTotal % 1024) * 10 / 1024);
	    Size *= 2;
	  }
        printf("\n");
	CloseHandle(hDevice);
	Drive++;
      }
    printf("\n");


    return 0;
}