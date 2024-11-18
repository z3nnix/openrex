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