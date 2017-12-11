/**
 *  Basic hash table implementation
 *   Aaron S. Crandall - 2017 <acrandal@gmail.com>
 *
 */

#ifndef __HASH_H
#define __HASH_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <list>


using namespace std;
/*
	private:
		void rehash();
		int hash_function(KEYTYPE key);

	public:
		bool insert(KEYTYPE key, VALTYPE val);
		bool contains(KEYTYPE key);
		int remove(KEYTYPE key);
		VALTYPE* find(KEYTYPE key);
		int size();            // Elements currently in table
		bool empty();          // Is the hash empty?
		float load_factor();   // Return current load factor
		void clear();          // Empty out the table
		int bucket_count();    // Total number of buckets in table
		void print(int num);	 // Print all words
*/

template <typename KEYTYPE, typename VALTYPE>
class Hashtable
{
private:
		// main hash table table
		vector< list<VALTYPE> > _hash;
		int numElements = 0;

		/**
		 *  Rehash the table into a larger table when the load factor is too large
		 */
		void rehash() {
			//resize vector to nextprime
			int number = (_hash.size() * 2);
			int i = 2;
			int j = 0;
			bool insert = false;
			list<VALTYPE> temp;

			for(int i = 2; i < number; i++)
			{
				if(i == number)
				{ break; }

				if(number % i == 0)
				{ i = 2; number++; }
			}

			//copy every element in current hash into temp list
			//create temp list
			while(j < _hash.size())
			{
				for(auto it = _hash[j].begin(); it != _hash[j].end(); it++)
				{
					temp.push_back(*it);
				}
				_hash[j].clear();
				j++;
			}

			//clear old array and then resize
			_hash.resize(number);

			//resize numElements to zero while we reinsert all elements
			numElements = 0;

			//hash every element in temp list and insert into new resized vector
			for(auto it2 = temp.begin(); it2 != temp.end(); it2++)
			{
				string word = (*it2).myword;
				this->insert(word, *it2);
			}

			return;


			//resize array
			//walk through hash and hashfunction(each element)
		}

		/**
		 *  Function that takes the key (a string or int) and returns the hash key
		 *   This function needs to be implemented for several types it could be used with!
		 */
		int hash_function(int key) {
			cout << " Hashing with int type keys." << endl;
			return(key % _hash.size());
		}

		int hash_function(string key) {
			//cout << " Hashing with string type keys." << endl;
			unsigned int hashVal = 0;

			for(char ch : key)
			hashVal = 37 * hashVal + ch;

			hashVal %= _hash.size();

			return hashVal;
		}


	public:
		/**
		 *  Basic constructor
		 */

		Hashtable( int startingSize = 101 )
		{
			_hash.resize(startingSize);
		}

		/**
		 *  Add an element to the hash table
		 */
		bool insert(KEYTYPE key, VALTYPE val) {
			//key is the "word" to convert to the key, val is the word object to put into the linked list at element[hashedKey];

			/*
				step one: 	convert key to hashed key
				step two:		check hashedKey location to see if we already have this word and definition, if we do, remove the current one and then proceed to insert as per usual
				step three:	rehash if load factor is >= 1
			*/

			//STEP ONE
			int hashedKey = hash_function(key);

			//STEP TWO
			if( contains(key) )
			{
				//Find and overwrite old data object with new passed in val
				for(auto it = _hash[hashedKey].begin(); it != _hash[hashedKey].end(); it++)
				{
					if(it->myword == key)
					{
						it->definition = val.definition;
					}
				}
			}
			else
			{
				//insert into the list
				_hash[hashedKey].push_back(val);
				numElements++;
			}

			//STEP THREE
			float loadFactor = load_factor();
			if(loadFactor >= 1)
			{
				rehash();
			}

			return(true);
		}

		/**
		 *  Return whether a given key is present in the hash table
		 */
		bool contains(KEYTYPE key) {

			//hash the key to find its location
			int hashedKey = hash_function(key);

			//check to see if linked list already contains a value equal to key
			//we should traverse the list at hashed key location with an STL iterator
			for(auto it = _hash[hashedKey].begin(); it != _hash[hashedKey].end(); it++)
			{
				if(it->myword == key)
				{
					return(true);
				}
			}
			return(false);
		}


		/**
		 *  Completely remove key from hash table
		 *   Returns number of elements removed, NAHHH how about removing the word searched for only.
		 *	implemented both....
		 */
		int remove(KEYTYPE key) {
			//accepts a int or string as the key

			//hash the key to find its location
			int hashedKey = hash_function(key);
			int numRemoved = 0;

			for(auto it = _hash[hashedKey].begin(); it != _hash[hashedKey].end(); it++)
			{
				if(it->myword == key)
				{
					_hash[hashedKey].erase(it);
					numRemoved++;
					numElements--;
					break;
				}
			}

			return(numRemoved);


/* naively remove the entire list if you hate the user and want them to suffer
			for(auto it = _hash[hashedKey].begin(); it != _hash[hashedKey].end(); it++)
			{
				//update numElements
				numElements--;
			}

			//clear the list
			_hash[hashedKey].clear();
			//or
			//it.erase( _hash[hashedKey].begin(), _hash[hashedKey].end() );
*/
		}

		/**
		 *  Searches the hash and returns a pointer
		 *   Pointer to Word if found, or nullptr if nothing matches
		 */
		VALTYPE* find(KEYTYPE key) {
			//hash the key to find its location
			int hashedKey = hash_function(key);

			for(auto it = _hash[hashedKey].begin(); it != _hash[hashedKey].end(); it++)
			{
				if(it->myword == key)
				{
					return(&(*it));
				}
			}

			return nullptr;
		}

		/**
		 *  Return current number of elements in hash table
		 */
		int size() {
			return(numElements);
		}

		/**
		 *  Return true if hash table is empty, false otherwise
		 */
		bool empty() {

			if(numElements == 0)
			return(true);
			else
			return(false);

		}
		void print(int num) {
			if(num == -5)
			{
				int index = rand()%100;
				if(_hash.empty())
				{
					cout << "Dictionary is EMPTY!" << endl;
					return;
				}
				while(1){
					if(_hash[index].empty())
					{
							//find new word
							index = rand()%100;
					}
					else{
					cout << _hash[index].front().myword << endl;
					return;
					}
				}
			}
			if(num == -1){
				for(int i = 0; i < _hash.size(); i++)
				{
					for(auto it = _hash[i].begin(); it != _hash[i].end(); it++)
					{
						cout << it->myword << endl;
					}
				}
			}
			else{
				int numPrinted = 0;
				for(int i = 0; i < _hash.size(); i++)
				{
					for(auto it = _hash[i].begin(); it != _hash[i].end(); it++)
					{
						cout << it->myword << endl;
						numPrinted++;
						if(numPrinted == num){return;}
					}
				}
			}
			return;
		}


		/**
		 *  Calculates the current load factor for the hash
		 */
		float load_factor() {
			float loadFactor = (float)numElements / (float)_hash.size();
			return (loadFactor);
		}

		/**
		 *  Returns current number of buckets (elements in vector)
		 */
		int bucket_count() {
			return (_hash.size());
		}

		/**
		 *  Deletes all elements in the hash
		 */
		void clear() {
			int i = 0;

			for(int i = 0; i < _hash.size(); i++)
			{
				_hash[i].clear();
			}
			numElements = 0;

			return;
		}

};


#endif
