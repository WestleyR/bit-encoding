// Created by: WestleyK
// Email: westleyk@nym.hush.com
// Date: Sep 21, 2019
// Repo: https://github.com/WestleyR/bit-encoding
//
// Version: 1.0.0
//
// License: The Clear BSD License
//
// Copyright (c) 2019 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SCRIPT_VERSION "v1.0.0-beta-2, Sep 21, 2019"

char* script_name = NULL;

void print_version() {
    printf("%s\n", SCRIPT_VERSION);
}

void print_help() {
    printf("Usage:\n");
    printf("  %s [encode/decode]\n", script_name);
    printf("\n");
    printf("Example:\n");
    printf("  echo \"hello, world\" | %s encode\n", script_name);
    printf("\n");
}

int tx_out(const char* msg) {
    for (int i = 0; i < strlen(msg); i++) {
        for (int b = 0; b < 8; b++) {
            int tx = msg[i] & (0x80 >> b);
            printf("%s", tx ? "1" : "0");
        }
    }
    printf("\n");

    return(0);
}

int rx_in(char* message, char *binary) {
    message[0] = '\0';

    unsigned int rx_byte = 0;
    int bp = 0;

    for (int i = 0; i < strlen(binary); i++) {
        if (binary[i] == ' ') {
            bp = 0;
            rx_byte = 0;
            continue;
        }
        //        if (binary[i] == '\n') {
        //            bp = 0;
        //            rx_byte = 0;
        //            continue;
        //        }

        int bin = binary[i] - '0';

        //        if ((bin != 0) && (bin != 1)) {
        //            printf("input not valid: %c\n", binary[i]);
        //            exit(1);
        //        }

        if (bin == 1) {
            rx_byte |= (0x80 >> bp);
        }
        bp++;

        if (bp == 8) {
            strncat(message, (const char *)&rx_byte, 1);
            bp = 0;
            rx_byte = 0;
        }
    }

    return(0);
}

int main(int argc, char** argv) {
    script_name = argv[0];
    int max_len = 1024;

    char input[max_len];
    char foo[max_len];

    input[0] = '\0';
    foo[0] = '\0';


    if (argc > 1) {
        if (strcmp(argv[1], "encode") == 0) {
            while (fgets(foo, max_len, stdin)) {
                strcat(input, foo);
            }
            input[strlen(input)-1] = '\0';
            tx_out(input);
        } else if (strcmp(argv[1], "decode") == 0) {
            while (fgets(foo, max_len, stdin)) {
                strcat(input, foo);
            }
            input[strlen(input)-1] = '\0';

            char *out;
            out = (char*) malloc(max_len/2);

            rx_in(out, input);
            printf("%s\n", out);
            free(out);
        } else if (strcmp(argv[1], "--version") == 0) {
            print_version();
            return(0);
        } else if (strcmp(argv[1], "--help") == 0) {
            print_help();
            return(0);
        } else {
            printf("E: invalid option: %s\n", argv[1]);
            return(22);
        }
    } else {
        printf("E: need option\n");
        exit(1);
    }


    return(0);
}
