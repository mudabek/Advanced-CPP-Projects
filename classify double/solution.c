#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>


/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

bool getBit (const uint64_t number, const uint8_t index) {
    uint64_t mask = 1;
    mask <<= index;
    uint64_t temp = mask & number;
    temp >>= index;
    return temp;
}

bool isPositive(const uint64_t number) {
    uint8_t negSign = 63;
    return getBit(number, negSign) == 0;
}

bool isAllOnesExp (const uint64_t number) {
    uint8_t index = 62;
    while (index > 51) {
        if (getBit(number, index) == 0)
            return false;
        index--;
    }
    return true;
}

bool isAllZerosExp (const uint64_t number) {
    int index = 62;
    while (index > 51) {
        if (getBit(number, index) == 1)
            return false;
        index--;
    }
    return true;
}

bool isAllZerosFraction (const uint64_t number) {
    int index = 51;
    while (index > 0) {
        if (getBit(number, index) == 1)
            return false;
        index--;
    }
    return true;
}

bool isAllOnesFraction (const uint64_t number) {
    int index = 51;
    while (index > 0) {
        if (getBit(number, index) == 0)
            return false;
        index--;
    }
    return true;
}


/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    return number == 0;
}

bool checkForMinusZero (uint64_t number) {
    return number == 0x8000000000000000;
}

bool checkForPlusInf (uint64_t number) {
    return number == 0x7FF0000000000000;
}

bool checkForMinusInf (uint64_t number) {
    return number == 0xFFF0000000000000;
}

bool checkForPlusNormal (uint64_t number) {
    if (isPositive(number) && !isAllOnesExp(number) && !isAllZerosExp(number))
        return true;
    return false;
}

bool checkForMinusNormal (uint64_t number) {
    if (!isPositive(number) && !isAllOnesExp(number) && !isAllZerosExp(number))
        return true;
    return false;
}

bool checkForPlusDenormal (uint64_t number) {
    if (isPositive(number) && isAllZerosExp(number) && !isAllZerosFraction(number))
        return true;
    return false;
}

bool checkForMinusDenormal (uint64_t number) {
    if (!isPositive(number) && isAllZerosExp(number) && !isAllZerosFraction(number))
        return true;
    return false;
}

bool checkForSignalingNan (uint64_t number) {
    if (isAllOnesExp(number) && !getBit(number, 51))
        return true;
    return false;
}

bool checkForQuietNan (uint64_t number) {
    if (isAllOnesExp(number) && getBit(number, 51))
        return true;
    return false;
}


void classify (double number) {
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n");
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n");
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n");
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus normal\n");
    }

    else if (checkForMinusNormal(convertToUint64(number))) {
        printf("Minus normal\n");
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n");
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n");
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signaling NaN\n");
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n");
    }

    else {
        printf("Error.\n");
    }
}
