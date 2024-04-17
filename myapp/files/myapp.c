/*
* Copyright (C) 2013 - 2016  Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in this
* Software without prior written authorization from Xilinx.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_BUF_SIZE 1024


int checkdir(const char *path){
	DIR *dir = opendir(path);
	if (dir != NULL) {
		closedir(dir);
		return 1;
	}
	return 0;
}

void nodecheck(){
	printf("Checking nodes by path...\n");
	const char *gpupath = "/sys/devices/platform/axi/fd4b0000.gpu";
	const char *qspipath = "/sys/devices/platform/axi/ff0f0000.spi";
	const char *usbone = "/sys/devices/platform/axi/ff9e0000.usb1";
	const char *usbsub = "/sys/devices/platform/axi/ff9e0000.usb1/of_node/usb@fe300000";
	const char *display = "/sys/devices/platform/axi/fd4a0000.display";
	const char *cci = "/sys/devices/platform/axi/fd6e0000.cci";
	const char *smmu = "/sys/devices/platform/axi/fd800000.smmu";
	const char *perfa = "/sys/devices/platform/axi/ffa00000.perf-monitor";
	const char *perfb = "/sys/devices/platform/axi/fd0b0000.perf-monitor";
	const char *perfc = "/sys/devices/platform/axi/fd490000.perf-monitor";
	const char *perfd = "/sys/devices/platform/axi/ffa10000.perf-monitor";
	if (checkdir(gpupath)) {
		printf("GPU node is up.\n");
	} else {
		printf("GPU node is down!\n");
	}
	if (checkdir(qspipath)) {
		printf("QSPI node is up.\n");
	} else {
		printf("QSPI node is down!\n");
	}
	if (checkdir(usbone)) {
		printf("usb1 is up.\n");
	} else {
		printf("usb1 is down!\n");
	}
	if (checkdir(usbsub)) {
		printf("usb1 child is up.\n");
	} else {
		printf("usb1 child is down!\n");
	}
	if (checkdir(display)) {
		printf("display port is up.\n");
	} else {
		printf("display port is down!\n");
	}
	if (checkdir(cci)) {
		printf("cci is up.\n");
	} else {
		printf("cci is down!\n");
	}
	if (checkdir(smmu)) {
		printf("smmu is up.\n");
	} else {
		printf("smmu is down!\n");
	}
	if (checkdir(perfa)) {
		printf("perf-monitor ocm is up.\n");
	} else {
		printf("perf-monitor ocm is down.\n");
	}
	if (checkdir(perfb)) {
                printf("perf-monitor ddr is up.\n");
        } else {
                printf("perf-monitor ddr is down.\n");
        }
	if (checkdir(perfc)) {
                printf("perf-monitor cci is up.\n");
        } else {
                printf("perf-monitor cci is down.\n");
        }
	if (checkdir(perfd)) {
                printf("perf-monitor lpd is up.\n");
        } else {
                printf("perf-monitor lpd is down.\n");
        }
	printf("\n");
}

void usbstatus(){
	FILE *fp;
	const char *filepath = "/sys/devices/platform/axi/ff9d0000.usb0/power/runtime_status";
	char file_content[1024];
	fp = fopen(filepath, "r");
	printf("Checking usb0 status...\n");
	if (fp == NULL) {
		perror("Error opening file");
	}
	while (fgets(file_content, sizeof(file_content), fp)) {
		printf("%s", file_content);
	}
	fclose(fp);
	printf("\n");
}

int parsedmesg(){
	FILE *pipe;
	char buffer[MAX_BUF_SIZE];
	int qspistate = 0;
	int usbonestate = 0;
	int usbzerosub = 0;
	int displayp = 0;
	int cci = 0;
	int perfa = 0;
	int perfb = 0;
	int perfc = 0;
	int perfd = 0;
	printf("Parsing DMESG...\n");
	pipe = popen("dmesg", "r");
	if (pipe == NULL) {
		perror("popen");
		return 0;
	}
	while (fgets(buffer, MAX_BUF_SIZE, pipe) != NULL) {
		if (strstr(buffer, "ff0f0000.spi: deferred probe timeout") != NULL) {
			printf("QSPI probed!\n");
			qspistate = 1;
		}
		if (strstr(buffer, "probe of ff9e0000.usb1") != NULL) {
			printf("Attempted probe of usb1!\n");
			usbonestate = 1;
		}
		if (strstr(buffer, "dwc3 fe300000.usb: deferred probe timeout") != NULL) {
                        printf("usb0 child probed!\n");
                        usbzerosub = 1;
                }
		if (strstr(buffer, "ZynqMP DisplayPort Subsystem driver probed") != NULL) {
			printf("DisplayPort Probed!\n");
			displayp = 1;
		}
		if (strstr(buffer, "ARM CCI_400_r1 PMU driver probed") != NULL) {
			printf("cci probed!\n");
			cci = 1;
		}
		if (strstr(buffer, "ffa00000.perf-monitor: Probed") != NULL) {
			printf("perf-monitor ocm probed!\n");
			perfa = 1;
		}
		if (strstr(buffer, "fd0b0000.perf-monitor: Probed") != NULL) {
                        printf("perf-monitor ddr probed!\n");
                        perfb = 1;
                }
		if (strstr(buffer, "fd490000.perf-monitor: Probed") != NULL) {
                        printf("perf-monitor cci probed!\n");
                        perfc = 1;
                }
		if (strstr(buffer, "ffa10000.perf-monitor: Probed") != NULL) {
                        printf("perf-monitor lpd probed!\n");
                        perfd = 1;
                }
	}
	pclose(pipe);
	if (qspistate == 0) {
		printf("qspi down!\n");
	}
	if (usbonestate == 0) {
		printf("usb1 down!\n");
	}
	if (usbzerosub == 0) {
		printf("usb1 child node down!\n");
	}
	if (displayp == 0) {
		printf("display port down!\n");
	}
	if (cci == 0) {
		printf("cci is down!\n");
	}
	if (perfa == 0) {
		printf("perf-monitor ocm is down!\n");
	}
	if (perfb == 0) {
                printf("perf-monitor ddr is down!\n");
        }
	if (perfc == 0) {
                printf("perf-monitor cci is down!\n");
        }
	if (perfd == 0) {
                printf("perf-monitor lpd is down!\n");
        }
	printf("\n");
	return 1;
}

int main(int argc, char **argv) {
	nodecheck();
	parsedmesg();
	usbstatus();
	return 0;
}
