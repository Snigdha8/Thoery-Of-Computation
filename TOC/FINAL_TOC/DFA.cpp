/*
* AUTHOR : SNIGDHA PATIL
*/

#include<bits/stdc++.h>
using namespace std;

typedef vector< vector<string> > csvVector;
void readCSV(istream &input, vector< vector<string> > &output)
{
   	string csvLine;
    // read every line from the stream
    while( getline(input, csvLine) )
    {
            istringstream csvStream(csvLine);
           vector<string> csvColumn;
            string csvElement;
            // read every element from the line that is seperated by commas
            // and put it into the vector or strings
            while( getline(csvStream, csvElement, ';') )
            {
                    csvColumn.push_back(csvElement);
            }
            output.push_back(csvColumn);
    }
}

void display( vector< vector<string> > temp )
{
	int rows = temp.size();
	int cols;
	int i,j;
	for( i=0 ; i<rows ; i++ )
	{
		cols = temp[i].size();
		cout << "{";
		for( j=0 ; j<cols-1 ; j++ )
		{
			cout << temp[i][j] << ",";
		}
		cout << temp[i][j];
		cout << "}";
		cout << "\n";
	}
}

/*
* This function checks if transitions of both strings 'a' & 'b' lie in the same set or not
* They will lie in the same set if they are in the same row since same states are stored in a single row of equivalence
*/
bool check_same_row(string s1, string s2, string t1, string t2, vector< vector<string> > equivalence )
{
	int rows = equivalence.size();
	int cols;
	int i,j;
	int yes,yes1;
	int flag = 1;
	int flag1;
	for( i=0 ; i<rows && flag == 1 ; )
	{
		cols = equivalence[i].size();
		yes = 0;
		for( j=0 ; j<cols ; j++ )
		{
			if( s1 == equivalence[i][j] )
				yes++;
			if( t1 == equivalence[i][j] )
				yes++;
		}
		if( yes < 2 )
		{
			i++;
		}
		else if( yes == 2 )
		{
			flag = 0;
		}
			
	}
	
	if( yes == 2 )
	{ 
		flag1 = 1;
		for( i=0 ; i<rows && flag1==1 ; )
		{
			cols = equivalence[i].size();
			yes1 = 0; 
			for( j=0 ; j<cols ; j++ )
			{
				if( s2 == equivalence[i][j] )
					yes1++;
				if( t2 == equivalence[i][j] )
					yes1++;
			}
			if( yes1 < 2 )
			{
				i++;
			}
			else if( yes1 == 2 )
			{
				flag1 = 0;
			}
			
		}
		
		if( yes1 == 2 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

/*
* This function extracts the transition states on input 0 & input 1 of both strings 'a' & 'b' & passes to 'check_same_row function'
*/
bool check( string a, string b, vector< vector<string> > dfa, vector< vector<string> > equivalence )
{
	int i,j;
	int rows = dfa.size();
	int cols;
	string s1,s2,t1,t2;
	/*
	* strings s1 & t1 store the transitions on input 0
	* strings s2 & t2 store the transitions on input 1
	*/
	for( i=0 ; i<rows-1 ; i++ )
	{
		if( dfa[i][0] == a )
		{
			 s1 = dfa[i][1];
			 s2 = dfa[i][2];
		}
		if( dfa[i][0] == b )
		{
			t1 = dfa[i][1];
			t2 = dfa[i][2];
		}
	}
	
	/*
	* If same row then it implies they belong to same set & we return true
	*/
	bool status = check_same_row(s1,s2,t1,t2,equivalence);
	if( status == true )
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
* This function appends the contents of temp to equivalence_new
*/
void push_new_equi( vector< vector<string> > temp, vector< vector<string> >& equivalence_new )
{
	int rows_of_equi = equivalence_new.size();
	int cols;
	int rows = temp.size();
	int i,j;  
	
	for( i=0 ; i<rows ; i++ )
	{
		cols = temp[i].size();
		vector<string> str;
		for( j=0 ; j<cols ; j++ )
		{
			str.push_back(temp[i][j]);
		}
		equivalence_new.push_back(str);
	}
}
	
/*
* If the state 'str' belongs to the set in which the state 's' belongs, then inserting 'str' in the row of state 's' indicating they both
* belong to the same set of states during finding the equivalence.
*/
void insert_in_proper_row( vector< vector<string> >& temp, string s, string str )
{
	int rows = temp.size();
	int i,j;
	int cols;
	int flag = 1;
	for( i=0 ; i<rows && flag == 1 ; i++ )
	{
		if( s == temp[i][0] )
		{
			temp[i].push_back(str);
			flag = 0;
		}
	}
}
			
void copy( vector< vector<string> > equivalence_new, vector< vector<string> >& equivalence )
{
	int rows_new = equivalence_new.size();
	int rows = equivalence.size();
	int diff = rows_new - rows;
	int cols;
	int i,j;
	
	equivalence.clear();
	for( i=0 ; i<rows_new ; i++ )
	{
		cols = equivalence_new[i].size();
		vector<string> str;
		for( j=0 ; j<cols ; j++ )
		{
			str.push_back(equivalence_new[i][j]);
		}
		equivalence.push_back(str);
	}
}

/*
* This function returns the row from vector 2D 'equivalence' which is the set of states on input 0 & input 1
* 
* When col=1, set for input 0 is returned & when col=2, set for input 1 is returned
*/
vector<string> check_on_input( string s, vector< vector<string> > dfa, vector<string> str, int col , vector< vector<string> > equivalence)
{
	int rows = dfa.size();
	int i,j;
	string s1;
	int cols;
	int flag = 1;
	for( i=0 ; i<rows && flag == 1 ; i++ )
	{
		if( s == dfa[i][0] )
		{
			s1 = dfa[i][col];
			flag = 0;
		}
	}
	
	int flag1;
	int store_row;
	rows = equivalence.size();
	for( i=0 ; i<rows ; i++ )
	{
		cols = equivalence[i].size();
		flag1 = 1;
		for( j=0 ; j<cols && flag1 == 1; j++ )
		{
			if( equivalence[i][j] == s1 )
			{
				store_row = i;
				flag1 = 0;
			}
		}
		if( flag1 == 0 )
		{
			break;
		}
	}
	cols = equivalence[store_row].size();
	for( i=0 ; i<cols ; i++ )
	{
		str.push_back(equivalence[store_row][i]);
	}
	return str; 
}

void dfa_to_minstate_dfa( vector< vector<string> > dfa, int num_non_final_states )
{
	/*
	* Equivalence stores the different sets of states in each step corresponding to each equivalence
	* Initially it stores the sets for zero equivalence i.e. a set of non-final states & a set of final states
	*/
	vector< vector<string> > equivalence;
	int i,j;
	int rows = dfa.size();
	int cols;
	vector<string> temp1;
	vector<string> temp2;
	int new_rows;
	string s;
	/*
	* The 'intial num_non_final_states rows' of the file contain the non-final states
	* Whereas, the remaining lines contain the final states
	*/
	
	/*
	* Storing the non-final states in temp1
	*/
	for( i=1 ; i<=num_non_final_states ; i++ )
	{
		s = dfa[i][0];
		temp1.push_back(s); 
	}
	
	/*
	* Storing the final states in temp2
	*/
	for( i = num_non_final_states+1 ; i<rows-1 ; i++ )
	{
		s = dfa[i][0];
		temp2.push_back(s);
	}
	
	/*
	* Ultimately storing the zero equivalence sets in equivalence
	*/
	equivalence.push_back(temp1);
	equivalence.push_back(temp2);
	
	rows = equivalence.size();
	
	/*
	* Outputting the zero equivalence (initial step of minimization of a DFA) 
	*/
	cout << "\nThe first line represents the set of non-final states & the second line represents the set of final states\n";
	for( i=0 ; i<rows ; i++ )
	{
		cols = equivalence[i].size();
		cout << "{";
		for( j=0 ; j<cols-1 ; j++ )
		{
			cout << equivalence[i][j] << ",";
		}
		cout << equivalence[i][j];
		cout << "}";
		cout << "\n";
	}  
	cout << "\n";
	
	vector< vector<string> > equivalence_new;
	bool status;
	int temp_row,k;
	int count;
	int entered;
	int done = 0;
	
	/*
	* done flag = 0 indicates that next unique equivalence can be generated
	*/
	while( done == 0 )
	{
		rows = equivalence.size();
		/*
		* Each row of the 'equivalence 2D vector of vector of strings' (2D string array) will be checked on input '0' 
		* & input '1'. 
		*
		* Accordingly, the newly created sets will then be stored in another 2D vector of vector of strings declared as temp below.
		*
		* After each row of 'equivalence' is broken in sets and stored in temp, then finally the contents of temp are stored
		* or rather appended to a new 2D vector of vector of strings declared as 'equivalence_new' below.
		*
		* When all the rows of equivalence are done by following the above procedure, the contents of 'equivalence_new' are copied
		* back into 'equivalence' and then we iterate again for this new 'equivalence' we just got.
		*
		* Finally, if after iterating for all rows of 'equivalence' we get 'equivalence_new' same as that of 'equivalence', we set
		* done flag to 1 indicating that 'THE DFA HAS NOW BEEN CONVERTED TO A MINIMUM STATE DFA' because finding its next 
		* equiavlence is going to give us the same sets of states as that of the previous equivalence.
		*
		* Basically, in every iteration we are finding out the next equivalence for eg. starting from zero equivalence, then 1
		* equivalence, 2 equivalence, 3 equivalence & so on until we get the same equivalence as that of the preivious one.
		*/
		vector< vector<string> > equivalence_new;
		for( i=0 ; i<rows ; i++ )
		{
			cols = equivalence[i].size();
			
			vector< vector<string> > temp;
			vector<string> states;
			states.push_back(equivalence[i][0]);
			temp.push_back(states);
			
			for( j=1 ; j<cols ; j++ )
			{
				temp_row = temp.size();
				count = 0;
				
				for( k=0 ; k<temp_row ; )
				{	
					status = check(temp[k][0],equivalence[i][j],dfa,equivalence);
					if( status == true )
					{
						insert_in_proper_row(temp,temp[k][0],equivalence[i][j]);
						break;
					}
					else
					{
						k++;
						count++;
					}
				}
				if( k != 0 && count == k )
				{
					vector<string> states;
					states.push_back(equivalence[i][j]);
					temp.push_back(states);
				}
			}
			
			int r1 = temp.size();
			int i1,j1;
			for( i1 = 0 ; i1<r1 ; i1++ )
			{
				equivalence_new.push_back(temp[i1]);
			}
			new_rows = equivalence_new.size();
		}
		
		/*
		* Showing old set of states and new just to show the change in the equivalence after iteration
		*/
		cout << "OLD SET OF STATES WAS" << "\n";
		display(equivalence);
		copy(equivalence_new,equivalence);
		cout << "\nNEW SET OF STATES IS" << "\n";
		display(equivalence_new);
		cout << "\n";
		new_rows = equivalence_new.size();
		if( new_rows == rows )
		{
			done = 1;
		}
	}
	
	/*
	* equivalence now contains the possible states in the minimized DFA
	*/
	rows = 	equivalence.size();
	vector<string> str1;
	vector<string> str2;
	vector< vector<string> > on_input_0;
	vector< vector<string> > on_input_1;
	
	cout << "THE TRANSITION TABLE FOR THE MINIMUM STATE DFA IS :\n";
	
	/*
	* Here, for each newly obtained states of the minimized DFA we check its transition on input 0 & input 1 & thus fill the transition
	* table for the minimized DFA.
	*/
	for( i=0 ; i<rows ; i++ )
	{
	
		str1 = check_on_input(equivalence[i][0],dfa,str1,1,equivalence);
		on_input_0.push_back(str1);
		str1.clear();
		str2 = check_on_input(equivalence[i][0],dfa,str2,2,equivalence);
		on_input_1.push_back(str2);
		str2.clear();
	}
	
	/*
	* Showing the transition table for minimum state dfa obtained
	*/
	cout << "-------------------------------------------------------------\n";
	cout << "STATES\t\t\t " << "ON INPUT 0\t\t " << "ON INPUT 1\t" << "\n";
	cout << "-------------------------------------------------------------\n";
	for( i=0 ; i<rows ; i++ )
	{
		cols = equivalence[i].size();
		cout << "{";
		for( j=0 ; j<cols-1 ; j++ )
		{
			cout << equivalence[i][j] << ",";
		}
		cout << equivalence[i][j];
		cout << "}";
		cout << "\t\t\t ";
		
		cols = on_input_0[i].size();
		cout << "{";
		for( j=0 ; j<cols-1 ; j++ )
		{
			cout << on_input_0[i][j] << ",";
		}
		cout << on_input_0[i][j];
		cout << "}";
		cout << "\t\t\t ";
		
		cols = on_input_1[i].size();
		cout << "{";
		for( j=0 ; j<cols-1 ; j++ )
		{
			cout << on_input_1[i][j] << ",";
		}
		cout << on_input_1[i][j];
		cout << "}";
		cout << "\n";
	}
		
}

int main()
{
	/*
	* Reading DFA transition table from a file
	* First column in the DFA is the states in the DFA.
	* Second column in the DFA is the transition state on input 0 & Third column on input 1.
	* All the states above '*' in the file are non-final states & all the states below are final states 
	*/
	fstream file("dfa.csv", ios::in);
    	if(!file.is_open())
	{
		cout << "File not found!\n";
		return 1;
	}
	
    	csvVector csvData;
    	
    	readCSV(file, csvData);
    	vector< vector<string> > dfa;
    	vector<string> terminals;

    	string s1;
    	csvVector::iterator i = csvData.begin();
	
	int flag = 1;
	int num_non_final_states = 0;
	int num = 0;
    	for( ; i != csvData.end(); i++ )
    	{
        	vector<string> temp;
        	flag = 1;
        	for( vector<string>::iterator j = i->begin(); j != i->end(); j++  )
       		{
	    		s1 = *j;
	    		if( s1 == "*" )
	    		{
	    			flag = 0;
	    			num_non_final_states = num;
	    		}
	    		else
	    		{
	    			temp.push_back(s1);
	    		}
		}
		if( flag != 0 )
		{
        		
        		dfa.push_back(temp);
        		num++;  	
        	}
 	}

 	cout << "\nTHE TRANSITION TABLE FOR THE DFA IS : \n";
 	int j,k;
	int rows = dfa.size();
	int cols;
	k = 0;
	cols = dfa[k].size();
	for( j=0 ; j<cols ; j++ )
	{
		cout << dfa[k][j] << " | ";
	}
	cout << "\n";
	cout << "-----------\n";
	
	for( k=1 ; k<rows ; k++ )
	{
		cols = dfa[k].size();
		for( j=0 ; j<cols ; j++ )
		{
			cout << dfa[k][j] << " | ";
		}
		cout << "\n";
	}
	cout << "-----------\n";
	cout << "\n****************************************CONVERTING TO MINIMUM STATE DFA****************************************** \n";
	dfa_to_minstate_dfa(dfa,num_non_final_states-1);

	return 0;
}
