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

/*
* The below function displays the template corresponding to each move, and also computes the total number of productions allowing all 
* combinations of the states
*
* Here, xi is taken which will denote the states in the combinations 
*/
void pda_to_cfg( vector< std::vector<string> > pda , int num_states )
{
	int rows = pda.size();
	int cols;

	int k = 1;
	int i,j,num_terms;
	
	cout << "Since num_states = " << num_states << ", xi will range from i=0 to i = num_states-1\n\n";
	int total_num_productions = 0;
	cout << "If we denote by S the start symbol of the grammar, the productions that we need to begin are those of the form \n";
	cout << "				S -> [ q0,Z,xi ]\n";
	cout << "where q0 is the initial state. Because in accepting strings by empty stack the final state is irrelevant, we \ninclude a production of this type for every possible state xi\n\n";
	total_num_productions = total_num_productions + num_states;
	
	/*
	* All the templates(as per the rule of converting a PDA TO CFG) corresponding to each move are displayed
	*/
	cout << "\n\n\t\t\tTHE GRAMMAR IS\n";
	cout << "-------------------------------------------------------------------------\n";
	
	cout << "S -> [ q0,Z,xi ]\n";
	for( i=0 ; i<rows ; i++ )
	{
		cols = pda[i].size();
		num_terms = cols - 4;

		if( num_terms > 1 )
		{
			/*
			* for a move's template, no. of productions will be (no. of states)^(no. of terms)
			* no. of terms are the columns after the transition state in the csv file
			* 
			* When move is of the type : q0;a;Z;q0;A;Z
			* then production for it would be of the form : [ q0,Z,x0 ] -> a [ q0,A,x1 ][ x1,Z,x0 ]
			*/
			total_num_productions = total_num_productions + pow(num_states,num_terms);
			cout << "[ " << pda[i][0] << "," << pda[i][2] << ",x0 ] -> " << pda[i][1] << " [ " << pda[i][3] << ",";	
			for( j=4 ; j<cols-1 ; j++ )
			{
				if( j== 4 )
				{
					cout << pda[i][j] << ",";
					cout << "x" << k << " ][ ";
				}
				else
				{
					cout << "x" << k << "," << pda[i][j] << "," << "x" << k+1 << " ][ ";
					k++;
				}
			}
			cout << "x" << k << "," << pda[i][j] << "," << "x0 ]\n";
		}
		else if( num_terms == 1 )
		{
			/*
			* When move is of the type : q1;a;A;q1;^ or q1;^;Z;q1;^ (single term which is ^)
			* then the production for it would be of the form : [q1,A,q1] -> a or [q1,Z,q1] -> ^
			* 
			* When move is of the type : q0;c;B;q1;B (single term which is NOT ^, but a non-terminal)
			* then the production for it would be of the form : [ q0,B,x0 ] -> c [ q1,B,x0 ]
			*/			
			if( pda[i][4] == "^" )
			{
				total_num_productions = total_num_productions + 1;
				cout << "[ " << pda[i][0] << "," << pda[i][2] << "," << pda[i][3] << " ] -> " << pda[i][1] << "\n";
			}
			else
			{
				total_num_productions = total_num_productions + pow(num_states,num_terms);
				cout << "[ " << pda[i][0] << "," << pda[i][2] << ",x0 ] -> " << pda[i][1] << " [ " << pda[i][3] << ",";
				cout << pda[i][4] << "," << "x0 ]\n";
			}
		}
	}
	cout << "\nAllowing all combinations of xi , where { i=0 to i=num_states-1 } gives " << total_num_productions << " productions in all.\n";
	cout << "\nTHUS, TOTAL NUMBER OF PRODUCTIONS ARE---------> " << total_num_productions << " \n";
}

int main()
{
	int num_states;
	cout << "\t\t\tEXAMPLE 1:\n\n";
	cout << "\t\t\tSOLVED EXAMPLE FROM JOHN MARTIN PAGE NO. 220\n\n";
	fstream file("p1.csv", ios::in);
    	if(!file.is_open())
	{
		cout << "File not found!\n";
		return 1;
	}
	
    	csvVector csvData;
    	
    	readCSV(file, csvData);
    	vector< std::vector<string> > pda;

    	string s1;

    	/*
    	* FIRST LINE OF THE FILE IS THE NUMBER OF STATES IN THE PDA
    	* EXTRACTING THE FIRST LINE  
    	*/
	csvVector::iterator i = csvData.begin();
	vector<string>::iterator j = i->begin();
	s1 = *j;
	stringstream geek1(s1); 
	geek1 >> num_states;

	i++;

    	for(  ; i != csvData.end(); i++ )
    	{
        	vector<string> temp;
        	for( vector<string>::iterator j = i->begin(); j != i->end(); j++  )
       		{
	    		s1 = *j;
	    		temp.push_back(s1);
		}
        	pda.push_back(temp);  	
 	}
	
	/*
	* In the file, column 0 : State (current state)
	* column 1 : Input symbol
	* column 2 : Stack Symbol
	* column 3 : next transition state
	* column 4 onwards are the term(s) in that move 
	*/
 	int p,q;
	int rows = pda.size();
	int cols;
	cout << "\n\n\t\t\tTHE GIVEN PDA IS\n";
	cout << "-------------------------------------------------------------------------\n";
	cout << "State\t" << "Input\t" << "Stack Symbol\t" << "Move(s)\n";
	cout << "-------------------------------------------------------------------------\n";
	for( p=0 ; p<rows ; p++ )
	{
		cols = pda[p].size();

		cout << pda[p][0] << "\t" << pda[p][1] << "\t" << pda[p][2] << "\t\t(" << pda[p][3] << ",";
		for( q=4 ; q<cols ; q++ )
		{
			cout << pda[p][q];
		}
		cout << ")\n";
	}
	cout << "-------------------------------------------------------------------------\n";

	cout << "\n\n\t\t\tCONVERTING TO CFG :)\n\n";
	
	pda_to_cfg(pda, num_states);
	file.close();
	
	/*
	* The same steps as above followed for example 2
	* Example 2 is just to show that 'all types' of moves are covered in the program
	*/
	cout << "\n\n\n****************************************************************************************************\n\n\n";
	cout << "\t\t\tEXAMPLE 2:\n\n";
	cout << "\t\t\tAN EXAMPLE TO DEMONSTRATE DIFFERENT TYPES OF MOVES\n\n";
	fstream file1("p2.csv", ios::in);
    	if(!file1.is_open())
	{
		cout << "File not found!\n";
		return 1;
	}
	
    	csvVector csvData1;
    	readCSV(file1, csvData1);

    	vector< std::vector<string> > pda1;
    	csvVector::iterator i1 = csvData1.begin();
	vector<string>::iterator j1 = i1->begin();
	s1 = *j1;
	stringstream geek2(s1); 
	geek2 >> num_states;

	i1++;

    	for(  ; i1 != csvData1.end(); i1++ )
    	{
        	vector<string> temp1;
        	for( vector<string>::iterator j1 = i1->begin(); j1 != i1->end(); j1++  )
       		{
	    		s1 = *j1;
	    		temp1.push_back(s1);
		}
        	pda1.push_back(temp1);  	
 	}

 	cout << "\n\n\t\t\tTHE GIVEN PDA IN FILE2 IS\n";
	cout << "-------------------------------------------------------------------------\n";
	cout << "State\t" << "Input\t" << "Stack Symbol\t" << "Move(s)\n";
	cout << "-------------------------------------------------------------------------\n";
	rows = pda1.size();
	
	for( p=0 ; p<rows ; p++ )
	{
		cols = pda1[p].size();
		cout << pda1[p][0] << "\t" << pda1[p][1] << "\t" << pda1[p][2] << "\t\t(" << pda1[p][3] << ",";
		for( q=4 ; q<cols ; q++ )
		{
			cout << pda1[p][q];
		}
		cout << ")\n";
	}
	cout << "-------------------------------------------------------------------------\n";

	cout << "\n\n\t\t\tCONVERTING TO CFG :)\n\n";
	pda_to_cfg(pda1, num_states);

	return 0;
}
