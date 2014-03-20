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

//required for 'stl_trait_writer' and 'file_trait_reader'
#include <fstream>


//Serialization-file writer class.
//This guy writes the data to the file specified by 'file_path'.
//NOTE: This class does not recoginse the data objects containing spaces, tabs, newline 
// charactes in them. This may be fixed by overloading '<<' operator and adding
// escape-sequencing logic in it.
class stl_trait_writer: public std::ofstream
{
public:

	stl_trait_writer(const std::string& file_path):std::ofstream(file_path.c_str())
	{

	}
};

//Serialization-file reader class.
//This guy reads the data from the file specified by 'file_path'.
//NOTE: This class does not recoginse the data objects containing spaces, tabs, newline 
// charactes in them. This may be fixed by overloading '>>' operator and adding
// escape-sequencing logic in it.
class file_trait_reader: public std::ifstream
{
public:

	file_trait_reader(const std::string& file_path):std::ifstream(file_path.c_str())
	{

	}
};

//Serialization filer class.
//This guy presents the set of reader, writer objects responsible for reading and writing 
// to the serialization file.
template <class writer_trait , class reader_trait>
class filer_trait
{
public:

	typedef  writer_trait writer_type;
	typedef  reader_trait reader_type;
};

//Basic datatype serializer class.
//Triggers the read or write to the serialization file for the basic datatypes.
//NOTE: This class has been tweaked to work with the 'stl_trait_writer' class.
template <class val_trait, class val_filer_trait = filer_trait<stl_trait_writer, file_trait_reader> >
class value_trait
{
public:

	typedef typename val_filer_trait::writer_type writer_trait;
	typedef typename val_filer_trait::reader_type reader_trait;

	void serialize(const val_trait& val, writer_trait &pen)
	{
		pen << val << "\n"; //a tweak for 'stl_trait_writer' class defined above.
		//pen << val;		//correct code, this should replace above line of code, should you impliment your own 'stl_trait_writer' class
		pen.flush();
	}

	void load(val_trait& val, reader_trait &pen)
	{
	
        pen >> val;
        std::string dump;
        std::getline(pen,dump);
		
	}
	void loadkey(val_trait& val, reader_trait &pen)
	{
		
		std::getline(pen,val);
       
	}
};

//Associative-list datatype serializer class.
//Triggers the read or write to the serialization file for the Associative-list datatypes.
//This class takes care of STL types -- map, multimap, set, multiset
template <class associative_list_type, class val_filer_trait >
class associative_list_value_trait
{
public:
	typedef typename val_filer_trait::writer_type writer_trait;
	typedef typename val_filer_trait::reader_type reader_trait;

	typedef typename associative_list_type::size_type size_type;
	typedef typename associative_list_type::key_type key_type;
	typedef typename associative_list_type::mapped_type data_type;
	typedef typename associative_list_type::iterator itr;

	void serialize (associative_list_type& val, writer_trait &pen )
	{
		value_trait<size_type, val_filer_trait> size_filer;
		itr i;
		
		size_filer.serialize (val.size(), pen);

		for(i=val.begin(); i != val.end(); i++)
		{
			value_trait<key_type, val_filer_trait> val_trait_key_filer;
			value_trait<data_type, val_filer_trait> val_trait_data_filer;

			val_trait_key_filer.serialize(i->first,pen);
			val_trait_data_filer.serialize(i->second,pen);
		}
	}

	void load (associative_list_type& val, reader_trait &pen )
	{
		value_trait<size_type, val_filer_trait> size_reader;
		size_type val_size=0;
		size_reader.load(val_size, pen);

		for(; val_size > 0; val_size--)
		{
		//	key_type key_element;
			std::string key; /* explicit key-type is used to simplify the matter. We have string as the key
			              type and need not make it customizable in our case*/
			value_trait<std::string, val_filer_trait> val_trait_key_reader;
			val_trait_key_reader.loadkey(key, pen);
			data_type data_element;
			value_trait<data_type, val_filer_trait> val_trait_data_reader;
			val_trait_data_reader.load(data_element, pen);
			val.insert (std::pair<key_type, data_type> (key, data_element));
		}

	}
};



//STL map datatype serializer class.
//Triggers the read or write to the serialization file for the STL map datatype .
template <class val_trait_key, class val_trait_data, class val_filer_trait  > 
class value_trait< std::map<val_trait_key, val_trait_data> , val_filer_trait  > 
{
public:

	typedef typename val_filer_trait::writer_type writer_trait;
	typedef typename val_filer_trait::reader_type reader_trait;

	typedef std::map<val_trait_key, val_trait_data> map_value_trait;

	void serialize (map_value_trait& val, writer_trait &pen )
	{

		associative_list_value_trait<map_value_trait, val_filer_trait> associative_list_value_filer;
		associative_list_value_filer.serialize (val, pen);

	}

	void load (map_value_trait& val, reader_trait &pen )
	{

		associative_list_value_trait<map_value_trait, val_filer_trait> associative_list_value_reader;

		associative_list_value_reader.load (val, pen);
	}
	
};


