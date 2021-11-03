#include <math.h>
#include <stdio.h>

int isOdd(size_t N) {
    return (N & 1);
}

size_t find_ithBit(size_t N, int i) {
    return N & (1 << (i-1));
}

// set the i th bit to 1 even if the ith bit  is 0 OR 1
size_t set_ithBitTo1(size_t N, int i) {
    return N | (1 << (i-1));
}

size_t posOfRightSetBit(size_t N) {
    return N & (-N);
}

size_t noOfDigitsBase(size_t N, int base) {
    return (size_t)(log(N) / log(base)) + 1;
}

size_t Power(size_t base, size_t power) {

    if (power == 0)
        return 1;
    
    if ((power & 1) == 1) {
        return base * Power(base*base, power>>1);
    }
    return Power(base*base, power>>1);
}

int main(int argc, char const *argv[]) {
    //testing
    printf("%ld\n",isOdd(32542535352));
    printf("%ld\n",find_ithBit(182,5));
    printf("%ld\n",set_ithBitTo1(86,4));
    printf("%ld\n",posOfRightSetBit(364));
    printf("%ld\n",noOfDigitsBase(6,2));//binary
    printf("%ld\n",noOfDigitsBase(6,10));// decimal
    printf("%ld\n",noOfDigitsBase(6,8));// octal

    printf("%ld\n",Power(2,7));// octal
    return 0;
}
