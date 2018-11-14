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
		for( j=0 ; j<cols ; j++ )
		{
			cout << temp[i][j] << "  ";
		}
		cout << "\n";
	}
}

bool check_same_row(string s1, string s2, string t1, string t2, vector< vector<string> > equivalence )
{
	//cout << "inside check row!!\n";
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
			//cout << " yes    matched!!\n";
			flag = 0;
		}
			
	}
	
	if( yes == 2 )
	{
		//cout << "ok here^^^^^^^^^66\n" << "and rows are" << rows << "\n"; 
		flag1 = 1;
		for( i=0 ; i<rows && flag1==1 ; )
		{
			cols = equivalence[i].size();
			//cout << "cols are inside checck_same_row " << cols << "\n";
			yes1 = 0; 
			for( j=0 ; j<cols ; j++ )
			{
				if( s2 == equivalence[i][j] )
					yes1++;
				if( t2 == equivalence[i][j] )
					yes1++;
				
				//cout << "yes1 is " << yes1 << "\n";
			}
			if( yes1 < 2 )
			{
				i++;
			}
			else if( yes1 == 2 )
			{
				//cout << "yes1   matched!!\n";
				flag1 = 0;
			}
			
		}
		//cout << "yes1 is " << yes1 << "\n";
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

bool check( string a, string b, vector< vector<string> > dfa, vector< vector<string> > equivalence )
{
	//cout << "inside check!!\n";
	int i,j;
	int rows = dfa.size();
	//cout << "rows is in check " << rows << "\n";
	int cols;
	string s1,s2,t1,t2;
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

void push_new_equi( vector< vector<string> > temp, vector< vector<string> >& equivalence_new )
{
	//cout << "inside pushhhhshshshshhshshs\n";
	//display(equivalence_new);
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
	//display(equivalence_new);
	/*else
	{
		for( i=0 ; i<rows ; i++ )
		{
			equivalence_new.push_back();
		}
	}*/
}
	

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
	//cout << "DIFF  IS " << diff << "\n";
	/*for( i=0 ; i<diff ; i++ )
	{
		vector<string> str1;
		for( j=0 ; j<10 ; j++ )
		{
			str1.push_back("*");
		}
		equivalence.push_back(str1);
	}  */
	
	for( i=0 ; i<rows_new ; i++ )
	{
		cols = equivalence_new[i].size();
		vector<string> str;
		for( j=0 ; j<cols ; j++ )
		{
			//equivalence[i][j] = equivalence_new[i][j];	
			str.push_back(equivalence_new[i][j]);
		}
		equivalence.push_back(str);
	}
}

void dfa_to_minstate_dfa( vector< vector<string> > dfa, int num_non_final_states )
{
	vector< vector<string> > equivalence;
	int i,j;
	int rows = dfa.size();
	//cout << "rowsssssssssssssssssssssssssss " << rows << "\n";
	int cols;
	vector<string> temp1;
	vector<string> temp2;
	int new_rows;
	string s;
	//non final states
	for( i=1 ; i<=num_non_final_states ; i++ )
	{
		//cout << dfa[i][0] << "\n";
		s = dfa[i][0];
		//cout << s << "\n";
		temp1.push_back(s); 
		//cout << "*\n";
	}
	//final states
	//cout << "rows are " << rows << "\n";
	for( i = num_non_final_states+1 ; i<rows-1 ; i++ )
	{
		//cout << dfa[i][0] << "\n";
		s = dfa[i][0];
		//cout << s << "\n";
		temp2.push_back(s);
		//cout << "&\n"; 
	}
	
	equivalence.push_back(temp1);
	equivalence.push_back(temp2);
	
	//cout << "\n0 equi is -----> \n";
	rows = equivalence.size();
	
	for( i=0 ; i<rows ; i++ )
	{
		cols = equivalence[i].size();
		for( j=0 ; j<cols ; j++ )
		{
			cout << equivalence[i][j] << "  ";
		}
		cout << "\n";
	}  
	
	vector< vector<string> > equivalence_new;
	bool status;
	int temp_row,k;
	int count;
	int entered;
	int done = 0;
	while( done == 0 )
	{
		rows = equivalence.size();
		//cout << "rows issssssss " << rows << "\n";
		vector< vector<string> > equivalence_new;
		for( i=0 ; i<rows ; i++ )
		{
			cols = equivalence[i].size();
			
			vector< vector<string> > temp;
			vector<string> states;
			states.push_back(equivalence[i][0]);
			temp.push_back(states);
			
			//display(temp);
	
			for( j=1 ; j<cols ; j++ )
			{
				temp_row = temp.size();
				//cout << "temp row size " << temp_row << "\n";
				count = 0;
				//entered = 0;
				for( k=0 ; k<temp_row ; )
				{	
					//cout << "yo";
					
					status = check(temp[k][0],equivalence[i][j],dfa,equivalence);
					if( status == true )
					{
						/*vector<string> states;
						states.push_back(equivalence[i][0]);
						states.push_back(equivalence[i][j]);
						temp.push_back(states);  */
						//cout << "yay\n";
						insert_in_proper_row(temp,temp[k][0],equivalence[i][j]);
						break;
					}
					else
					{
						k++;
						count++;
						//entered = 1;
					}
				}
				if( k != 0 && count == k )
				{
					vector<string> states;
					states.push_back(equivalence[i][j]);
					temp.push_back(states);
				}
			}
			
			
			//push_new_equi(temp,equivalence_new);
			int r1 = temp.size();
			int i1,j1;
			for( i1 = 0 ; i1<r1 ; i1++ )
			{
				equivalence_new.push_back(temp[i1]);
			}
			//copy(temp,equivalence_new);
			//cout << "after copying \n";
			new_rows = equivalence_new.size();
			//cout << "NEWWWWWWWW ROWSSSSSSS AREEEE --->" << new_rows << "\n";
			//display(equivalence_new);
			//display(temp);
		}
		
		cout << "OLD IS " << "\n";
		display(equivalence);
		copy(equivalence_new,equivalence);
		cout << "NEW EQUIS ISSSSSSSSSSSSSSSSSSS" << "\n\n";
		display(equivalence_new);
		
		new_rows = equivalence_new.size();
		//cout << "new rows is " << new_rows << "^^^^^^^^ rows is " << rows << "\n"; 
		
		if( new_rows == rows )
		{
			done = 1;
		}
	}	
}

int main()
{
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
        	//cout << "num is " << num << "\n";
 	}
 	//cout << " and now num is " << num << "\n";

 	cout << "\nTHE TRANSITION TABLE FOR THE DFA IS : \n";
 	int j,k;
	int rows = dfa.size();
	
	//cout << "main rows " << rows << "\n";
	int cols;
	for( k=0 ; k<rows ; k++ )
	{
		cols = dfa[k].size();
		for( j=0 ; j<cols ; j++ )
		{
			cout << dfa[k][j] << "  ";
		}
		cout << "\n";
	}
	
	//cout << "num_non_final are : " << num_non_final_states-1 << "\n";
	cout << "\nCONVERTING TO MINIMUM STATE DFA---------> \n";
	dfa_to_minstate_dfa(dfa,num_non_final_states-1);

	return 0;
}
