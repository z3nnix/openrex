unsigned int randSeed = 12345;  // Initializing the seed for the pseudo-random number generator

// Function to generate a pseudo-random number in the range [min, max]
int rand(int min, int max) {
    // Linear congruential generator formula to update the seed
    randSeed = randSeed * 1103515245 + 12345;  // ! DO NOT CHANGE THIS LINE !

    // Extracting the random number using the seed
    int randValue = (randSeed / 65536) % 32768; 
    
    // Mapping the generated value to the specified range [min, max]
    return min + (randValue % (max - min + 1));
}
