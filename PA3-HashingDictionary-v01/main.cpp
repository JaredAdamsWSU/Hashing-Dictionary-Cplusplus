/*
*  main.cpp - Hashtable based dictionary
*   Aaron Crandall <acrandal@gmail.com> - 2017
*   Educational use only
*
*/


#include <iostream>
#include <cstdlib>
#include <string.h>
#include "word.h"
#include "hashtable.h"
#include "dictionary.h"
#include "testinghash.h"
#include "testingdictionary.h"


using namespace std;

/**
*  Test mode operations
*/
void run_test_mode( bool bigtest = false ) {
 cout << " [t] Running in test mode. " << endl;

 run_hashtable_tests();
 cout << endl << " ----------------------------------------------------------- " << endl << endl;;

 cout << " [t] Testing the dictionary class. " << endl;
 run_dictionary_tests( bigtest );
}

/**
*  Normal mode execution for general user control
*/
void run_normal_mode() {
 cout << " [x] Running in normal mode. " << endl;

 Dictionary dict;

 dict.run_ui();
}



/**
*  Main function for test or use
*/
int main( int argc, char* argv[] )
{
 int retState = 0;
 // Note: If you call this program like this: ./HashingDict --test
 //  it will call the test function
 if( argc > 2 && !strcmp(argv[2], "--withFuzzing" )  )
 {
	 run_test_mode( true );
	 cout << " [x] BIGTEST testing program complete. " << endl;
 }
 else if( argc > 1 && !strcmp(argv[1], "--test" ) )
 {
	 run_test_mode( );
	 cout << " [x] Testing program complete. " << endl;
 }
 else
 {
	 cout << " [x] Running in normal mode. " << endl;
	 cout << "  [!] Nothing to do in normal mode so here's a helicopter: " << endl;

	 cout << "        .----.-.\n       /    ( o \\\n      '|  __ ` ||\n       |||  ||| -'" << endl << endl;
	 cout << "     Since that's not a helicopter, you should probably replace this code with something like \"Welcome to my dictionary program\" and go into normal running mode." << endl << endl;

	 cout << endl << "     Oh, and you should probably run 'make test' to test your program. " << endl;

	 run_normal_mode();
 }
}
