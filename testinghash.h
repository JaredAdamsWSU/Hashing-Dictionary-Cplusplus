/*
 *  Testing file for hash table
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *
 *  Tests the hashtable class with words (dictionary use)
 *
 */

#include "hashtable.h"
#include "word.h"

//**************************************************************
void test_hash_empty() {
	cout << "  [t] Testing empty()" << endl;;
	Hashtable<string, Word> ht;

	cout << "   [t] If is empty -     ";
	( ht.empty() ) ? cout << "pass" : cout << "fail";
	cout << endl;


	ht.insert( "test", Word{ "test", "def" } );
	cout << "   [t] If is not empty - ";
	( ht.empty() == false ) ? cout << "pass" : cout << "fail";
	cout << endl;
}

//**************************************************************
void test_hash_size() {
	cout << "  [t] Testing size()" << endl;;
	Hashtable<string, Word> ht;
	for( int i = 0; i < 4; i++ )
	{
		cout << "   [t] Size " << i << " : " << ht.size();
		( i == ht.size() ) ? cout << " - pass" : cout << " - fail";
		cout << endl;
		ht.insert( to_string(i), Word(to_string(i), "number") );
	}
	for( int i = 3; i > -1; i-- )
	{
		ht.remove( to_string(i) );
		cout << "   [t] Size " << i << " : " << ht.size();
		( i == ht.size() ) ? cout << " - pass" : cout << " - fail";
		cout << endl;
	}
}

//**************************************************************
void test_hash_contains() {
	cout << "  [t] Testing contains()" << endl;;
	Hashtable<string, Word> ht;

	ht.insert( "wordA", Word("wordA", "It's a word!") );
	cout << "   [t] Contains wordA (yes)";
	( ht.contains( "wordA" ) ) ? cout << " - pass" : cout << " - fail";
	cout << endl;
	cout << "   [t] Contains wordNO (no)";
	( !ht.contains( "wordNO" ) ) ? cout << " - pass" : cout << " - fail";
	cout << endl;


}

//**************************************************************
void test_hash_remove() {
	cout << "  [t] Testing remove()" << endl;;
	Hashtable<string, Word> ht;

	ht.insert( "wordA", Word("wordA", "It's a word!") );
	cout << "   [t] Contains wordA (yes)";
	( ht.contains( "wordA" ) ) ? cout << " - pass" : cout << " - fail";
	cout << endl;

	cout << "   [t] Removing WordA: " << endl;
	int count = ht.remove( "wordA" );
	cout << "        Count (1): " << count;
	( count == 1 ) ? cout << " - pass" : cout << " - fail";   cout << endl;
	cout << "        Contains (no): ";
	( !ht.contains( "wordA" ) ) ? cout << " - pass" : cout << " - fail";
	cout << endl;
}

//**************************************************************
void test_hash_find() {
	cout << "  [t] Testing find()" << endl;;
	Hashtable<string, Word> ht;

	ht.insert( "myWord", Word("myWord", "It's a word!") );
	cout << "   [t] Contains myWord (yes)";
	( ht.contains( "myWord" ) ) ? cout << " - pass" : cout << " - fail";
	cout << endl;

	Word* found = ht.find( "myWord" );
	cout << "   [t] myWord should be : myWord : It's a word!" << endl;
	cout << "   [t] myWord instead is: ";

	if( found != nullptr ) {
 		cout << found->to_string();

		if( "myWord : It's a word!" == found->to_string() )
			cout << " - pass";
		else
			cout << " - fail";
	}
	else
		cout << " - fail";
	cout << endl;
}

//**************************************************************
// Test load factor (force initial size, insert a couple, output)
void test_hash_loadfactor() {
	cout << "  [t] Testing loadfactor()" << endl;;
	Hashtable<string, Word> ht;

	for( int i = 0; i < 500; i++ ) {
		ht.insert( to_string(i), Word( to_string(i), "isa word" ) );

		if( i % 33 == 0 ) {
			cout << "   [t] load factor (" << ht.size() << " / "
			 	 << ht.bucket_count() << ") -> ";


			float roundedTarget = (float)((int)(100*(float)ht.size() / (float)ht.bucket_count())) /100;
			float foundTarget = (float)((int)(100*ht.load_factor())) / 100.0;

			cout << roundedTarget << " vs " << foundTarget;
			(roundedTarget == foundTarget) ? cout << " - pass" : cout << " - fail";
			cout << endl;
		}
	}
}

//**************************************************************
// Test clearing out whole hash table
void test_hash_clear() {
	cout << "  [t] Testing clear()" << endl;;
	Hashtable<string, Word> ht;

	int tbsize = 500;
	for( int i = 0; i < tbsize; i++ ) {
		ht.insert( to_string(i), Word( to_string(i), "isa word" ) );
	}
	cout << "   [t] Table should be " << tbsize << " elements and is: " << ht.size();
	( tbsize == ht.size() ) ? cout << " - pass" : cout << " - fail";
	cout << endl;

	cout << "   [t] Calling clear() on table now." << endl;;
	ht.clear();

	cout << "   [t] Table should be " << 0 << " elements and is: " << ht.size();
	( 0 == ht.size() ) ? cout << " - pass" : cout << " - fail";
	cout << endl;

	cout << "   [t] Testing empty() one more time. ";
	( ht.empty() ) ? cout << " - pass" : cout << " - fail";
	cout << endl;

}


//**************************************************************
void run_hashtable_tests() {
    cout << " [t] Testing the hash class itself. " << endl;

    // Create object
	Hashtable<string, Word> h1;

	// NOTE: insert() tested by size() and contains() (at least)
	test_hash_empty();		// Test if empty
	test_hash_size();			// Test size
	test_hash_contains();	// Test contains
	test_hash_remove();		// Test remove
	test_hash_find();			// Test find
	test_hash_loadfactor();	// Test load factor - also rehash()
	test_hash_clear();		// test clear
	cout << " [t] hash class tests complete." << endl;

}
