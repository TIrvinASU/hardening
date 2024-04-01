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

#define INIT_STATE_PATH "/sys/module/mali/initstate"
#define MAX_STATE_LENGTH 20

int main(int argc, char **argv) {
    FILE *initstate_file;
    char initstate[MAX_STATE_LENGTH];

    // Open the initstate file for reading
    initstate_file = fopen(INIT_STATE_PATH, "r");
    if (initstate_file == NULL) {
        perror("Error opening initstate file");
        return 1;
    }

    // Read the initialization state from the file
    if (fgets(initstate, MAX_STATE_LENGTH, initstate_file) == NULL) {
        perror("Error reading initstate file");
        fclose(initstate_file);
        return 1;
    }

    // Close the file
    fclose(initstate_file);

    // Print the initialization state
    printf("Mali GPU Initialization State: %s", initstate);

    return 0;
}
