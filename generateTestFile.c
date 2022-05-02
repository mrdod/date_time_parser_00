#include <generateTestFile.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <main.h>
#include <string.h>
#include <time.h>

// Prototypes
static int appendString( char* tsOutput, int* tsIndex, int width, int min, int max );


/*
 * Generate Test File
 *
 * Generates a file containing random time/date stamps for testing.
 */
int generateTestFile( long numberOfEntries ){
    FILE* fp;

    // Set seed for random function to be based on current time
    srand(time(NULL));

    char* templateTimeDatePtr = "2020-12-15T03:15:25+03:00";
    int timeDatePtrLen = strlen(templateTimeDatePtr);

    // Open input values file
    fp = fopen("input_values.txt","w+");

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


int appendString( char* tsOutput, int* tsIndex, int width, int min, int max ){
    char* localString = (char*) calloc( width, sizeof(char) );
    int localInt = rand() % ( max + 1 );

    if( localInt < min ){
         localInt = min;
    }

    ( width == 4 ) ? sprintf( localString, "%04d", localInt ) : sprintf( localString, "%02d", localInt );

    for( int localIndex = 0; localIndex < width; localIndex++ ){
        tsOutput[(*tsIndex)++] = localString[localIndex];
    }

    free( localString );

    return 1;
}