// stlsl.h : Declares and Defines the STL Serialization Libray (STL-SL) template classes.
// Author: Aniruddha Jayant Jahagirdar (ajDOTsubscribeAT-THE-RATEgmailFULL-STOPcom)
// Date: October 2, 2006
// Revision: 0.1

//required for STL-SL classes
#include <string>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include<iostream>

//required for 'stl_trait_writer' and 'file_trait_reader'
#include <fstream>



//Basic datatype serializer class.
//Triggers the read or write to the serialization file for the basic datatypes.
//NOTE: This class has been tweaked to work with the 'stl_trait_writer' class.
template <class val_trait>
class value_trait
{
public:



	void serialize(const val_trait& val, std::ofstream &pen)
	{
		pen << val << "\n"; //a tweak for 'stl_trait_writer' class defined above.
		//pen << val;		//correct code, this should replace above line of code, should you impliment your own 'stl_trait_writer' class
		
		pen.flush();
	}

	void load(val_trait& val, std::ifstream &pen)
	{
	
        pen >> val;
        std::string dump;
        std::getline(pen,dump);
		
	}
	void loadkey(val_trait& val,std::ifstream &pen)
	{
		
		std::getline(pen,val);
       
	}
};

//Associative-list datatype serializer class.
//Triggers the read or write to the serialization file for the Associative-list datatypes.
//This class takes care of STL types -- map, multimap, set, multiset
template <class key_type, class mapped_type >
class map_value_trait
{
public:	
	typedef typename std::map<key_type,mapped_type> associative_list_type;
	typedef typename associative_list_type::size_type size_type;
	typedef typename associative_list_type::key_type key_type;
	typedef typename mapped_type data_type;
	typedef typename associative_list_type::iterator itr;

	void serialize (associative_list_type& val,std::ofstream &pen )
	{
		value_trait<size_type> size_filer;
		itr i;		
		size_filer.serialize (val.size(), pen);

		for(i=val.begin(); i != val.end(); i++)
		{
			value_trait<key_type> val_trait_key_filer;
			value_trait<data_type> val_trait_data_filer;

			val_trait_key_filer.serialize(i->first,pen);
			val_trait_data_filer.serialize(i->second,pen);
		}
	}

	void load (associative_list_type& val, std::ifstream &pen )
	{
		value_trait<size_type> size_reader;
		size_type val_size=0;
		size_reader.load(val_size, pen);

		for(; val_size > 0; val_size--)
		{
			key_type key;
			
			 /* explicit key-type is used to simplify the matter. We have string as the key
			              type and need not make it customizable in our case*/
			value_trait<key_type> val_trait_key_reader;
			val_trait_key_reader.load(key, pen);
			data_type data_element;
			value_trait<data_type> val_trait_data_reader;
			val_trait_data_reader.load(data_element, pen);
			val.insert (std::pair<key_type, data_type> (key, data_element));
		}

	}
};



