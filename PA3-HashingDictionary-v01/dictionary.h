

#ifndef __DICT_H
#define __DICT_H

#include "hashtable.h"
#include "word.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class Dictionary
{

	private:
		Hashtable<string, Word> _dict;  // Primary dictionary store

	//Converts any string of one word to all uppercase, no spaces
	string make_upper(char* s) {
		for(int i = 0; s[i] != '\0'; i++)
			s[i] = toupper(s[i]);
		return s;
	}

	int string_value(char* s) {
		int val = 0;
		for(int i = 0; s[i] != '\0'; i++)
			val+=s[i];
		return val;
	}

	void parseline( string line ) {
		string delim_space = " ";
		string delim_quote = "\"";
		char delim_bracket = '}';
		char delim_comma = ',';

		string add = "ADD", rmv = "REMOVE", help = "HELP", define = "DEFINE",
		load = "LOAD", unload = "UNLOAD", size = "SIZE", print = "PRINT",
		random = "RANDOM", quit = "QUIT", clear = "CLEAR";

////////////////////////////////////////////////////////////////////////////////////
		//contains only command, need to make upper then ready to process.
		string command = line.substr(0, line.find(delim_space));
		this->make_upper(&command[0]);
		cout << "command string contains: \"" << command << "\"" << endl;

		if(command == add)
		{
			//parse rest of string to get strings to add to hash
			//contains entire rest of string starting from either a quote on the word or the first letter of the word
			string line2 = line.substr((line.find(delim_space)+1), line.find('\0'));


			if(line2[0] == '\"') //word is surrounded by quotes, eliminate them
			{
				line2.erase(line2.begin());
				line2.erase(line2.begin()+(line2.find(delim_quote)));
			}

			//now store word in its own variable for use later
			string the_word = line2.substr(0, line2.find(delim_space));
			string the_definition = line2.substr(line2.find(delim_space)+1, line2.find('\0'));

			//make word uppercase
			this->make_upper(&the_word[0]);

			//remove quotes surrounding definition if they exist
			if(the_definition[0] == '\"')
			{
				the_definition.erase(the_definition.begin());
				the_definition.erase(the_definition.begin()+(the_definition.find(delim_quote)));
			}

			//create the word object and add it to our hash table
			_dict_hash.insert( the_word, Word( the_word, the_definition ) );

			//cout
			cout << "Word: "<< the_word << endl << "Definition: "<< the_definition << endl << "Succesfully inserted into dictionary!" << endl;

		}
		else if(command == help)
		{
			cout << "COMMANDS:" << endl << "help	\t\t-> print out command help" << endl <<
			"add \"word\" \"definition\"	-> Add (or update!) a word and it’s definition. Must handle quotes" << endl <<
			"remove \"word\"	\t-> Remove a given word. Must handle quotes" << endl <<
			"define \"word\"	\t-> Define a word by printing out it’s definition or \"unknown word\"" << endl <<
			"load \"filename\"	\t-> Load in a JSON file of dictionary words" << endl <<
			"unload \"filename\"	-> Remove words from a given JSON file of dictionary words" << endl <<
			"size	\t\t-> Print out current number of words in the dictionary" << endl <<
			"clear	\t\t-> Remove ALL words from the dictionary" << endl <<
			"print [#words]	\t-> Print out all words, unless user gives a maximum number" << endl <<
			"random	\t\t-> Print out a single word chosen randomly from the dictionary" << endl <<
			"quit	\t\t-> Quit the user interface and shut down" << endl << endl;
		}
		else if(command == rmv)
		{
			//parse rest of string to get strings to add to hash
			//contains entire rest of string starting from either a quote on the word or the first letter of the word
			string line2 = line.substr((line.find(delim_space)+1), line.find('\0'));


			if(line2[0] == '\"') //word is surrounded by quotes, eliminate them
			{
				line2.erase(line2.begin());
				line2.erase(line2.begin()+(line2.find(delim_quote)));
			}

			//now store word in its own variable for use later
			string the_word = line2.substr(0, line2.find(delim_space));

			//make word uppercase
			this->make_upper(&the_word[0]);

			//remove the word from the hash table
			_dict_hash.remove(the_word);
			cout << the_word << " Succesfully removed!" << endl;
		}
		else if(command == define)
		{
			string define_word = line.substr(7, line.find('\n'));
			this->make_upper(&define_word[0]);

			Word* ptrToWord = _dict_hash.find(define_word);

			if(_dict_hash.contains(define_word))
			cout << "Definition of \"" << define_word << "\" is: " << ptrToWord->definition << endl;
			else
			cout << "Sorry, word not in dictionary." << endl;
		}
		else if(command == load)
		{
			fstream myfile;
			string line_string;
			//string new_word;
			string comma_placeholder;
			int i = 0;

			//parse rest of string to get strings to add to hash
			//contains entire rest of string starting from either a quote on the word or the first letter of the word
			string line2 = line.substr((line.find(delim_space)+1), line.find('\0'));


			if(line2[0] == '\"') //word is surrounded by quotes, eliminate them
			{
				line2.erase(line2.begin());
				line2.erase(line2.begin()+(line2.find(delim_quote)));
			}

			//now store word in its own variable for use later
			string filename = line2.substr(0, line2.find(delim_space));
			string search;
			size_t pos;
  		myfile.open (filename);
  		//Parse the input file and insert the words from each line
			//getline(myfile, string garb1);
			//getline(myfile, string garb2);

			getline (myfile, line_string);
			getline (myfile, line_string);

			while (!myfile.eof())
			{
				getline (myfile, line_string, delim_bracket);

				search = "word";
				pos = line_string.find(search);
				if (pos != string::npos)
						i++;
				else
					break;

				getline (myfile, comma_placeholder, '\n');

				//cut out word and definition to insert into the hash
				string new_word = line_string.substr(14, line_string.find('\"')-1);
				string new_definition = line_string.substr(13, line_string.find('\0'));
				new_definition.erase(0, new_definition.find(':'));
				new_definition.erase(0, (new_definition.find('\"')+1));
				new_definition.erase(new_definition.end()-1, new_definition.end());

				_dict_hash.insert(new_word, Word(new_word, new_definition));

			}
			cout << "Succesfully loaded " << filename << endl;
  		myfile.close();

		}
		else if(command == unload)
		{
			fstream myfile;
			string line_string;
			//string new_word;
			string comma_placeholder;

			//parse rest of string to get strings to add to hash
			//contains entire rest of string starting from either a quote on the word or the first letter of the word
			string line2 = line.substr((line.find(delim_space)+1), line.find('\0'));


			if(line2[0] == '\"') //word is surrounded by quotes, eliminate them
			{
				line2.erase(line2.begin());
				line2.erase(line2.begin()+(line2.find(delim_quote)));
			}

			//now store word in its own variable for use later
			string filename = line2.substr(0, line2.find(delim_space));
			string search;
			size_t pos;
  		myfile.open (filename);
  		//Parse the input file and insert the words from each line
			//getline(myfile, string garb1);
			//getline(myfile, string garb2);

			getline (myfile, line_string);
			getline (myfile, line_string);

			while (!myfile.eof())
			{
				getline (myfile, line_string, delim_bracket);

				search = "word";
				pos = line_string.find(search);
				if (pos != string::npos)
					cout << "UNloading word from ~H`a~S_h~. " << endl;
				else
					break;

				getline (myfile, comma_placeholder, '\n');

				//cut out word and definition to insert into the hash
				string new_word = line_string.substr(14, line_string.find('\"')-1);

				_dict_hash.remove(new_word);

			}
			cout << "Succesfully UNloaded: " << filename << endl;
  		myfile.close();

		}
		else if(command == size)
		{
			cout << "Number of words in Dictionary: " << _dict_hash.size() << endl;
		}
		else if(command == print)
		{
			//print # or print all if only print
			if(line.length() == 5)
			{
				//print all
				cout << endl << "Printing FULL Dictionary" << endl;
				_dict_hash.print(-1);
				cout << endl;
			}
			else
			{
				int i = 0;
			 	char buffer[256];

				//parse and print how many from begining
				string num = line.substr(6, (line.find('\0')));

				cout << endl << "Printing " << num << " words" << endl;

				while(num[i] != '\0')
				{buffer[i] = num[i]; i++;}

				// i = atoi (buffer);

				_dict_hash.print(atoi(buffer));
			}

		}
		else if(command == random)
		{
			//select a random word and print it out
			cout << "Printing out a random word: " << endl << endl;
			_dict_hash.print(-5);

			cout << endl;
		}
		else if(command == clear)
		{
			//empty the hash
			_dict_hash.clear();
		}
		else
		{
			cout << "Invalid Command: \"" << command << "\""<< endl << "Please type \"Help\" for advice." << endl;
		}


return;
}

	public:

		Hashtable<string, Word> _dict_hash;

		Dictionary()	// Default constructor
		 { }

	/**
	 *  Run the main dictionary user interface
	 */
	void run_ui() {
		// print out header
		cout << "+------------------------------------------+" << endl;
		cout << "|-- Welcome to the best dictionary evar! --|" << endl;
		cout << "+------------------------------------------+" << endl;

		string instr;
		cout << " Enter command (^D or EOF quits): ";

		// read in user input until eof
		while (getline(cin, instr)) {
			cout << "Entered: " << instr << endl;
			if(instr == "quit")
			{_dict_hash.clear(); break; }
			this->parseline(instr);

			// call function based on line contents
			// print results

			cout << "Enter command: ";
		}
		cout << "Program finished. " << endl;
	}

};



#endif
