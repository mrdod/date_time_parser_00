# Date Time Time Parser

This system takes a file with a list of date / time stamps and parses them to ensure they match the specified format.

By default, the logic is looking for time / dates matching the following template

2020-12-15T03:15:25+03:00

Valid date / time stamps will be passed through and output to a text file. The algorithm will also ensure there are no duplicates.


generateTestFile( 10000 ) - Can be used to generate an test input file with valid data. The argument adjusts the number of lines. By default this will be put into a file named input_values.txt

The valid output date / time stamps will be saved in output_values.txt


