#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
     YEAR = 0,
     MONTH,
     DAY,
     HOUR,
     MIN,
     SECOND,
     TZ,
     TZHOUR,
     TZMIN,
     DELIM
} TIME_DATE_E;


// Prototypes
bool dateIsValid(  char* dateTimePtr, char* delimPtr );
bool inputIsValid( char* dateTimePtr, int* dateTimeIndexPtr, int length, int minConf, int maxConf );


int main()
{
    bool result = false;

    char* inputDate = "2020-12-15T03:15:25+03:00";
    char* delimPtr= "--T:::";

    /*
    ** Test cases
    */

    printf("Sanity Valid Test Case\n");

    // Valid
    inputDate = "2020-12-15T03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 1    Actual Result: %d\n", inputDate, result );

    /*
    ** Delims Tests
    */
    printf("\nDelim Tests\n");

    // First Delim incorrect
    inputDate = "2020+12-15T03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Second Delim incorrect
    inputDate = "2020-12&15T03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Third Delim incorrect
    inputDate = "2020-12-15A03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Fourth Delim incorrect
    inputDate = "2020-12-15T03#15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Fifth Delim incorrect
    inputDate = "2020-12-15T03:15^25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Sixth Delim incorrect
    inputDate = "2020-12-15T03:15:25%03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Seventh Delim incorrect
    inputDate = "2020-12-15T03:15:25+03=00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // All Delim incorrect
    inputDate = "2020%12@15)03(15~25`03]00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Delim as numbers
    inputDate = "2020112215303415525603700";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    /*
    ** Values Tests
    */
    printf("\nValues Tests\n");

    // Max Values
    inputDate = "9999-12-31T23:59:59+23:59";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 1    Actual Result: %d\n", inputDate, result );

    // Min Values
    inputDate = "0000-01-01T00:00:00+00:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 1    Actual Result: %d\n", inputDate, result );

    // Max Month Exceeded
    inputDate = "2020-13-15T03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Max Day Exceeded
    inputDate = "2020-12-32T03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Max Hour Exceeded
    inputDate = "2020-12-15T24:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Max Minute Exceeded
    inputDate = "2020-12-15T03:60:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Max Second Exceeded
    inputDate = "2020-12-15T03:15:60+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Year with letter
    inputDate = "202A-12-15T03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Month with letter 1
    inputDate = "2020-A2-15T03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Month with letter 2
    inputDate = "2020-1A-15T03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Month with letter 3
    inputDate = "2020-AA-15T03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Day with letter 1
    inputDate = "2020-12-1AT03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Day with letter 2
    inputDate = "2020-12-A5T03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Day with letter 3
    inputDate = "2020-12-AAT03:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Hour with letter 1
    inputDate = "2020-12-15TA3:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Hour with letter 2
    inputDate = "2020-12-15T0A:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Hour with letter 3
    inputDate = "2020-12-15TAA:15:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Minute with letter 1
    inputDate = "2020-12-15T03:A5:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Minute with letter 2
    inputDate = "2020-12-15T03:1A:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Minute with letter 3
    inputDate = "2020-12-15T03:AA:25+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Second with letter 1
    inputDate = "2020-12-15T03:15:A5+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Second with letter 2
    inputDate = "2020-12-15T03:15:2A+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Second with letter 3
    inputDate = "2020-12-15T03:15:AA+03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );


    /*
    ** Timezone Tests
    */
    printf("\nTimezone Tests\n");

    // Negative TZ
    inputDate = "2020-12-15T03:15:25-03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 1    Actual Result: %d\n", inputDate, result );

    // TZ Hour With Letters 1
    inputDate = "2020-12-15T03:15:25+A3:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // TZ Hour With Letters 2
    inputDate = "2020-12-15T03:15:25+0A:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // TZ Hour With Letters 3
    inputDate = "2020-12-15T03:15:25+AA:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // TZ Minute With Letters 1
    inputDate = "2020-12-15T03:15:25+03:A0";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // TZ Minute With Letters 2
    inputDate = "2020-12-15T03:15:25+03:0A";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // TZ Minute With Letters 3
    inputDate = "2020-12-15T03:15:25+03:AA";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // UTC TZ (Z)
    inputDate = "2020-12-15T03:15:25Z";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s        Expected Result: 1    Actual Result: %d\n", inputDate, result );

    // Values after Z
    inputDate = "2020-12-15T03:15:25Z1";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s       Expected Result: 0    Actual Result: %d\n", inputDate, result );

    // Values after Z (second attempt)
    inputDate = "2020-12-15T03:15:25Z03:00";
    result = dateIsValid( inputDate, delimPtr );
    printf( "Input:%s   Expected Result: 0    Actual Result: %d\n", inputDate, result );
}


/*
 * Date is Valid
 *
 * Parses input data time string and returns true if has valid format / contains valid values
 */

bool dateIsValid( char* dateTimePtr, char* delimPtr ){
    int dateTimeIndex = 0;
    int delimIndex    = 0;

    TIME_DATE_E state      = YEAR;
    TIME_DATE_E savedState = YEAR;

    int dateTimePtrSize = strlen( dateTimePtr );

    while( true ){
        switch( state ){
            case( YEAR ):
            {
                #define YEAR_LEN (4)
                #define YEAR_MIN (0)
                #define YEAR_MAX (9999)

                if( !inputIsValid(dateTimePtr, &dateTimeIndex, YEAR_LEN, YEAR_MIN, YEAR_MAX) ){
                    return false;
                }

                savedState = YEAR;
                state = DELIM;

                break;
            }
            case( DELIM ):
            {
                if(delimPtr[delimIndex++] != dateTimePtr[dateTimeIndex++]){
                    return false;
                }

                state = ++savedState;

                break;
            }
            case( MONTH ):
            {
                #define MONTH_LEN (2)
                #define MONTH_MIN (0)
                #define MONTH_MAX (12)

                if( !inputIsValid(dateTimePtr, &dateTimeIndex, MONTH_LEN, MONTH_MIN, MONTH_MAX) ){
                    return false;
                }

                savedState = MONTH;
                state = DELIM;

                break;
            }
            case( DAY ):
            {
                #define DAY_LEN (2)
                #define DAY_MIN (0)
                #define DAY_MAX (31)

                if( !inputIsValid(dateTimePtr, &dateTimeIndex, DAY_LEN, DAY_MIN, DAY_MAX) ){
                    return false;
                }

                savedState = DAY;
                state = DELIM;

                break;
            }
            case( HOUR ):
            {
                #define HOUR_LEN (2)
                #define HOUR_MIN (0)
                #define HOUR_MAX (23)

                if( !inputIsValid(dateTimePtr, &dateTimeIndex, HOUR_LEN, HOUR_MIN, HOUR_MAX) ){
                    return false;
                }

                savedState = HOUR;
                state = DELIM;

                break;
            }
            case( MIN ):
            {
                #define MIN_LEN (2)
                #define MIN_MIN (0)
                #define MIN_MAX (59)

                if( !inputIsValid(dateTimePtr, &dateTimeIndex, MIN_LEN, MIN_MIN, MIN_MAX) ){
                    return false;
                }

                savedState = MIN;
                state = DELIM;

                break;
            }
            case( SECOND ):
            {
                #define SECOND_LEN (2)
                #define SECOND_MIN (0)
                #define SECOND_MAX (59)

                if( !inputIsValid(dateTimePtr, &dateTimeIndex, SECOND_LEN, SECOND_MIN, SECOND_MAX) ){
                    return false;
                }

                // Drop through
            }
            case( TZ ):
            {
                // Z stands for UTC or +00.00, if end of timestamp, return success
                if( (dateTimePtr[dateTimeIndex] == 'Z') && ((dateTimeIndex + 1) == dateTimePtrSize) ){
                    return true;
                // Ensure sign is included
                } else if( (dateTimePtr[dateTimeIndex] != '+') && (dateTimePtr[dateTimeIndex] != '-') ){
                    return false;
                }

                dateTimeIndex++;

                // Drop through
            }
            case( TZHOUR ):
            {
                #define TZHOUR_LEN (2)
                #define TZHOUR_MIN (0)
                #define TZHOUR_MAX (23)

                if( !inputIsValid(dateTimePtr, &dateTimeIndex, TZHOUR_LEN, TZHOUR_MIN, TZHOUR_MAX) ){
                    return false;
                }

                savedState = TZHOUR;
                state = DELIM;

                break;
            }
            case( TZMIN ):
            {
                #define TZMIN_LEN (2)
                #define TZMIN_MIN (0)
                #define TZMIN_MAX (59)

                if( !inputIsValid(dateTimePtr, &dateTimeIndex, TZMIN_LEN, TZMIN_MIN, TZMIN_MAX) ){
                    return false;
                }

                // Success if we are at end of timestamp
                return( (bool)(dateTimeIndex == dateTimePtrSize) );
            }
            default:
            {
               return false;
            }
        }
    }

    // If we got here something is wrong
    return false;
}


/*
 * Input Is Valid
 *
 * Convert Input from string to integer and check to ensure it is within range
 *
 * Inputs:
 *   dateTimePtr      - Pointer to entire dateTimePtr being evaluated
 *   dateTimeIndexPtr - Pointer to current index of dateTimePtr
 *   length           - length of substring being evaluated
 *   minConf          - minimum value to be considered valid
 *   maxConf          - maximum value to be considered valid
 *
 * Return: true if valid, false if not valid
 *
 */
bool inputIsValid( char* dateTimePtr, int* dateTimeIndexPtr, int length, int minConf, int maxConf ){
    bool retVal       = false;
    bool numCheckFail = false;

    if( dateTimePtr && dateTimeIndexPtr ){
        char* localString = (char*) calloc( length, sizeof(char) );
        int localInt = 0;

        // Copy chars up for eval into local buffer
        for( int index = 0; index < length; index++ ){
            localString[index] = dateTimePtr[(*dateTimeIndexPtr)++];

            // Ensure all entries are numbers
            if( localString[index] < '0' || localString[index] > '9'){
                numCheckFail = true;
            }
        }

        // Convert from string to int
        localInt = atoi( localString );

        // Compare to valid range and return result
        retVal = (bool)( !numCheckFail && (localInt >= minConf) && (localInt <= maxConf));

        free(localString);
    }

    return( retVal );
}





