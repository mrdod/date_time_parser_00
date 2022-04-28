#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define YEAR_START_INDEX (0)
#define YEAR_END_INDEX (4)

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
bool DateIsValid();

int main()
{
    bool dateIsValid = false;
    char* inputDate = "2020-12-15T03:15:25+03:00";

    char* inputDelimiters = "--T:::";

    dateIsValid = DateIsValid( inputDate, inputDelimiters );

    printf( "%s\n", dateIsValid ? "true" : "false" );
    printf( "%s\n", inputDate );
}

bool DateIsValid( char* inputString, char* inputDelimiters ){
    bool retVal = true;
    int stringIndex = 0;
    int delimIndex = 0;
    TIME_DATE_E state = YEAR;
    TIME_DATE_E savedState = YEAR;

    int inputStringSize = strlen(inputString);

    while(true){
        switch( state ){
            case( YEAR ):
            {
                char yearString[5] = {'0','0','0','0','\n'};
                int yearInt;

                for( int index = 0; index < 4; index++ ){
                    yearString[index] = inputString[stringIndex++];
                }

                yearInt = atoi( yearString );

                if( yearInt < 0 || yearInt > 9999 ){
                    return false;
                }

                savedState = YEAR;
                state = DELIM;

                break;
            }
            case( DELIM ):
            {
                if(inputDelimiters[delimIndex] != inputString[stringIndex]){
                    return false;
                }

                delimIndex++;
                stringIndex++;
                state = ++savedState;

                break;
            }
            case( MONTH ):
            {
                char monthString[3] = {'0','0','\n'};
                int monthInt = 0;
                char* endptr;

                for( int index = 0; index < 2; index++ ){
                    monthString[index] = inputString[stringIndex++];
                }

                monthInt = strtol( monthString, &endptr, 10 );

                if( monthInt < 1 || monthInt > 12 ){
                    return false;
                }

                savedState = MONTH;
                state = DELIM;

                break;
            }
            case( DAY ):
            {
                char dayString[3] = {'0','0','\n'};
                int dayInt = 0;

                for( int index = 0; index < 2; index++ ){
                    dayString[index] = inputString[stringIndex++];
                }

                dayInt = atoi( dayString );

                if( dayInt < 1 || dayInt > 31 ){
                    return false;
                }

                savedState = DAY;
                state = DELIM;

                break;
            }
            case( HOUR ):
            {
                char hourString[3] = {'0','0','\n'};
                int hourInt = 0;

                for( int index = 0; index < 2; index++ ){
                    hourString[index] = inputString[stringIndex++];
                }

                hourInt = atoi( hourString );

                if( hourInt < 1 || hourInt > 12 ){
                    return false;
                }

                savedState = HOUR;
                state = DELIM;

                break;
            }
            case( MIN ):
            {
                char minString[3] = {'0','0','\n'};
                int minInt;

                for( int index = 0; index < 2; index++ ){
                    minString[index] = inputString[stringIndex++];
                }

                minInt = atoi( minString );

                if( minInt < 0 || minInt > 59 ){
                    return false;
                }

                savedState = MIN;
                state = DELIM;

                break;
            }
            case( SECOND ):
            {
                char secondString[3] = {'0','0','\n'};
                int secondInt;

                for( int index = 0; index < 2; index++ ){
                    secondString[index] = inputString[stringIndex++];
                }

                secondInt = atoi( secondString );

                if( secondInt < 0 || secondInt > 59 ){
                    return false;
                }

                // Drop through
            }
            case( TZ ):
            {
                // Z stands for UTC or +00.00, if end of timestamp, return success
                if( (inputString[stringIndex] == 'Z') && (stringIndex == inputStringSize) ){
                    return true;
                // Ensure sign is included
                } else if((inputString[stringIndex] != '+') && (inputString[stringIndex] != '-')){
                    return false;
                }

                stringIndex++;

                // Drop through
            }
            case( TZHOUR ):
            {
                char hourString[3] = {'0','0','\n'};
                int hourInt = 0;

                for( int index = 0; index < 2; index++ ){
                    hourString[index] = inputString[stringIndex++];
                }

                hourInt = atoi( hourString );

                if( hourInt < 1 || hourInt > 12 ){
                    return false;
                }

                savedState = TZHOUR;
                state = DELIM;

                break;
            }
            case( TZMIN ):
            {
                char minString[3] = {'0','0','\n'};
                int minInt;

                for( int index = 0; index < 2; index++ ){
                    minString[index] = inputString[stringIndex++];
                }

                minInt = atoi( minString );

                if( minInt < 0 || minInt > 59 ){
                    return false;
                }

                // Success
                if( (stringIndex) == inputStringSize ){
                    return true;
                } else {
                    return false;
                }
            }
            default:
            {
               return false;
            }
        }
    }

    // bool retVal = true;
    // int index = 0;

    // // Year Validation
    // for( ; index < YEAR_END_INDEX; index++ ){
    //     if(inputString[index] < '0' || inputString[index] > '9'){
    //         retVal = false;
    //         return false;
    //     }
    // }

    // // Parse Deliminiter
    // if(inputString[index] != '-'){
    //     return false;
    // }

    // // Month Validation
    // {
    //     char desiredMonthString[2] = {inputString[++index], inputString[++index]};
    //     int desiredMonthInt = atoi(desiredMonthString);

    //     if( (desiredMonthInt < 1) || (desiredMonthInt > 12) ){
    //         return false;
    //     }
    // }

    // // Parse Deliminiter
    // if(inputString[++index] != '-'){
    //     return false;
    // }

    // // Parse Deliminiter
    // if(inputString[++index] != 'T'){
    //     return false;
    // }

    // if(inputString[]){

    // }



    return retVal;
}





