#define NULL ((void*)0) // Define the null pointer. 

unsigned int randSeed = 12345;  // Initializing the seed for the pseudo-random number generator

int rand(int min, int max) { // Function to generate a pseudo-random number in the range [min, max]
    randSeed = randSeed * 1103515245 + 12345; // Linear congruential generator formula to update the seed
    int randValue = (randSeed / 65536) % 32768; // Extracting the random number using the seed
    
    return min + (randValue % (max - min + 1)); // Mapping the generated value to the specified range [min, max]
}

int srand(int min, int max, int seed) { // Function to generate a pseudo-random number in the range [min, max] with given seed [seed].
    unsigned int randSeed = seed;  // Initializing the seed for the pseudo-random number generator
    randSeed = randSeed * 1103515245 + 12345;  // Linear congruential generator formula to update the seed

    int randValue = (randSeed / 65536) % 32768; // Extracting the random number using the seed
    
    return min + (randValue % (max - min + 1)); // Mapping the generated value to the specified range [min, max]
}

void reverse(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* itoa(int num, char* str, int base) {
    int i = 0;
    bool isNegative = false;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';

    reverse(str, i);

    return str;
}