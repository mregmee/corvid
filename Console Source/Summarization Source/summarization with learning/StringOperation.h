
/* srtClass */

#include<iostream>
#include <string.h>


using namespace std;

class StringOperation
{
public:
	char** make_strings(int );
	char * string_copy(char * s);
	void free_strings(char ** strs);
	int count_strings(char ** strs);
};

char** StringOperation:: make_strings(int num)
	{
		char ** buf = (char **)malloc((num+1) * sizeof(char *));
		for (int j=0; j<num+1; j++) buf[j] = NULL;
			return buf;
	}
char* StringOperation:: string_copy(char * s)
	{
		int size = strlen(s) + 1;
	char * ret = (char *)malloc(size);
	for (int i=0; i<size; i++)  ret[i] = s[i];
	ret[size-1] = 0;
	return ret;
	}

void StringOperation::free_strings(char ** strs)
	{
		//cout << "entering free_strings...\n";
		int i = 0;
	  while (true) {
		//cout << "  i=" << i << ", strs[i]=" << strs[i] << "\n";
		if (strs[i] == NULL) break;
		free(strs[i]);
				i++;
		  }
		  //cout << "free_strings 1\n";
		  free(strs);
		  //cout << "free_strings 2\n";
		}
int StringOperation::count_strings(char ** strs)
	{
		int i = 0;
		while (true) {
		if (strs[i] == NULL) break;
		i++; }
		return i;

	}

