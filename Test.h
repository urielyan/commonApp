//Copyright (c) 2013-2015 United States Government as represented by the Administrator of the
//National Aeronautics and Space Administration. All Rights Reserved.
#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define feq(x, y) (fabs(x - y) < 1e-4)

//#define IP "172.16.10.55"
//#define IP "127.0.0.1"
#define IP "192.168.0.2"

extern int testFailed;
extern int testPassed;

void runTest(int(*test)(), char* name);

int compareFloat(float expected, float actual);
int compareArray(float expected[], float actual[], int size);
int compareArrays(float* expected[], int esizes[], float* actual[], int asizes[], int count);


#define MALLOC_MEMORY_AND_SEND_DREF \
    int* asizes = (int*)malloc(sizeof(int) * count); \
    float** actual = (float**)malloc(sizeof(float*) * count); \
    for (int i = 0; i < count; ++i) \
    { \
        asizes[i] = sizes[i]; \
        actual[i] = (float*)malloc(sizeof(float) * sizes[i]); \
    }\
    XPCSocket sock = openUDP(IP);  \
    int result = getDREFs(sock, drefs, actual, count, asizes); \
    closeUDP(sock); \
    if (result < 0) \
    { \
        return -1; \
    } \

#define FREE_MEMORY \
    for (int i = 0; i < count; ++i) \
    { \
        free(actual[i]); \
    } \
    free(actual); \
    free(asizes);
#endif
