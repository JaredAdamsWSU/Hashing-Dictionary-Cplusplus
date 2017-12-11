/*
 *  testingdictionary.h - Tests for an English dictionary class
 *   Aaron S. Crandall <acrandal@gmail.com> - 2017
 *   Educational use only
 *
 */

#ifndef __DICT_TESTS_H
#define __DICT_TESTS_H

#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"

using namespace std;

//**********************************************************************
void do_test( string testname, string filename ) {
	cout << "***************************************************************************" << endl;
	cout << " [t] Testing '" << testname << "' command" << endl;
	string instr;
	cout << " [t] Commands being run on the dictionary are: " << endl;
	ifstream in(filename); // Open up commands to test for tester to see
	while(getline(in, instr)) {
		cout << instr << endl;
	}
	cout << endl << " [t] Running those commands to dict: " << endl << endl;

	ifstream in2(filename); // Create file stream for file of commands to test
	cin.rdbuf(in2.rdbuf()); // Redirect std::cin to filename!

   Dictionary dict;        // Create a new dictionary to test
   dict.run_ui();          // Run the dictionary, reading from filename

	cout << endl << " [t] Done testing '" << testname << "' command" << endl << endl;
}


//**********************************************************************
void run_dictionary_tests( bool bigtest = false ) {
	streambuf *cinbuf = cin.rdbuf(); //save default STDIN

	cout << " [t] Dictionary tests begin." << endl;
	cout << "  [x] These tests redirect STDIN to other files. " << endl;
	cout << "  [x] This *should* work on Windows, but no promises! " << endl;
	cout << endl;

	do_test("help",   "UITests/help.txt");
	do_test("add",    "UITests/add.txt");
	do_test("remove", "UITests/remove.txt");
	do_test("define", "UITests/define.txt");
	do_test("load",   "UITests/load.txt");
	do_test("unload", "UITests/unload.txt");
	do_test("size",   "UITests/size.txt");
	do_test("print",  "UITests/print.txt");
	do_test("random", "UITests/random.txt");
	do_test("quit",   "UITests/quit.txt");

	if( bigtest )
		do_test("bigtest","UITests/bigtest.txt");

	cin.rdbuf(cinbuf);   //reset cin to STDIN again
	cout << endl << " [t] Dictionary tests end." << endl;
}


#endif
