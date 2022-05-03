#include <generateTestFile.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <main.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define INPUT_FILE_NAME  ("input_values.txt")

// Local Prototypes
static bool appendString( char* tsOutput, int* tsIndex, int width, int min, int max );


/*
 * Generate Test File
 *
 * Generates a file containing random time/date stamps for testing.
 *
 * Inputs
 *   numberOfEntries - Total number of entries in test file
 *
 * Outputs
 *   returns 1 if sucessful
 */
int generateTestFile( long numberOfEntries ){
    FILE* fp;

    // Set seed for random function to be based on current time
    srand( time(NULL) );

    char* templateTimeDatePtr = "2020-12-15T03:15:25+03:00";
    int timeDatePtrLen = strlen(templateTimeDatePtr);

    // Open input values file
    fp = fopen( INPUT_FILE_NAME, "w+" );

    for( long index = 0; index < numberOfEntries; index++ ){
        int tsIndex = 0;
        char* tsOutput = (char*) calloc( timeDatePtrLen, sizeof(char) );

        // Year
        {
            #define YEAR_LEN (4)
            #define YEAR_MIN (0)
            #define YEAR_MAX (9999)

            appendString( tsOutput, &tsIndex, YEAR_LEN, YEAR_MIN, YEAR_MAX );

            tsOutput[tsIndex++] = '-';
        }

        // Month
        {
            #define MONTH_LEN (2)
            #define MONTH_MIN (1)
            #define MONTH_MAX (12)

            appendString( tsOutput, &tsIndex, MONTH_LEN, MONTH_MIN, MONTH_MAX );

            tsOutput[tsIndex++] = '-';
        }

        // Day
        {
            #define DAY_LEN (2)
            #define DAY_MIN (1)
            #define DAY_MAX (31)

            appendString( tsOutput, &tsIndex, MONTH_LEN, DAY_MIN, DAY_MAX );

            tsOutput[tsIndex++] = 'T';
        }

        // Hour
        {
            #define HOUR_LEN (2)
            #define HOUR_MIN (0)
            #define HOUR_MAX (23)

            appendString( tsOutput, &tsIndex, HOUR_LEN, HOUR_MIN, HOUR_MAX );

            tsOutput[tsIndex++] = ':';
        }

        // Minute
        {
            #define MIN_LEN (2)
            #define MIN_MIN (0)
            #define MIN_MAX (59)

            appendString( tsOutput, &tsIndex, MIN_LEN, MIN_MIN, MIN_MAX );

            tsOutput[tsIndex++] = ':';
        }

        // Second
        {
            #define SEC_LEN (2)
            #define SEC_MIN (0)
            #define SEC_MAX (59)

            appendString( tsOutput, &tsIndex, SEC_LEN, SEC_MIN, SEC_MAX );

            tsOutput[tsIndex++] = '+';
        }

        // Timezone Hour
        {
            #define TZHOUR_LEN (2)
            #define TZHOUR_MIN (0)
            #define TZHOUR_MAX (23)

            appendString( tsOutput, &tsIndex, TZHOUR_LEN, TZHOUR_MIN, TZHOUR_MAX );

            tsOutput[tsIndex++] = ':';
        }

        // Timezone Minute
        {
            #define TZMIN_LEN (2)
            #define TZMIN_MIN (0)
            #define TZMIN_MAX (59)

            appendString( tsOutput, &tsIndex, TZMIN_LEN, TZMIN_MIN, TZMIN_MAX );
        }

        // Add to file
        fprintf( fp, "%s\n", tsOutput );
    }

    // Close input values file
    fclose(fp);

    return 1;
}

/*
 * Append String
 *
 * Generates a pseudo random integer of either 2 or 4 digits in width and appends it
 * the current timestamp output string.
 *
 * Inputs
 *   tsOutput - Pointer to current output string
 *   tsIndex  - Current index of current output string
 *   width    - Desired number of digits of appended string
 *   min      - Minimum allowed value
 *   max      - Maximum allowed value
 *
 * Outputs
 *   Returns true if successful
 */
static bool appendString( char* tsOutput, int* tsIndex, int width, int min, int max ){
    bool retVal = false;

    if( tsOutput && tsIndex ){
        char* localString = (char*) calloc( width, sizeof(char) );

        // Generate a random number
        int localInt = rand() % ( max + 1 );

        // Ensure value is not less than min
        if( localInt < min ){
             localInt = min;
        }

        // Check width
        ( width == 4 ) ? sprintf( localString, "%04d", localInt ) : sprintf( localString, "%02d", localInt );

        // Add current value to string
        for( int localIndex = 0; localIndex < width; localIndex++ ){
            tsOutput[(*tsIndex)++] = localString[localIndex];
        }

        free( localString );
    }

    return retVal;
}
