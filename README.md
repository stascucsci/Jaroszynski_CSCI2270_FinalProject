# Jaroszynski_CSCI2270_FinalProject

## Project Summary
The library is a contact book. It uses hash tables to speed up searching. It keeps a separate hash table for each search parameter. Because of the high number of contacts that may have the same parameter value, it keeps an array of all the contacts that with the same value for each key. Contacts can be found through combining multiple parameters. It can save its data to a .csv file and load from one as well.

## How to Run
To run the example program use
```
make
./run
```
Test data is provided in data.csv which can be loaded with menu command 6 and inputting the string data.csv when prompted for the path.

## Dependencies
None

## System Requirements
g++ and GNU make to compile

## Group Members
None
