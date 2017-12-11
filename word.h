/**
 *
 *  Word object for storing a single word in our dictionary hash table
 *   Aaron S. Crandall <acrandal@gmail.com>
 *   Copyright 2017 - Educational use only
 *
 */

#ifndef __WORD_H
#define __WORD_H

#include <string>

using namespace std;

class Word
{
	public:

	string myword;
	string definition;

	Word( ) : myword( "" ), definition( "" ) { }
	Word( string w, string def ) : myword( w ), definition( def ) { }

	string to_string()
	{
		string ret = myword + " : " + definition;
		return ret;
	}

};

#endif
