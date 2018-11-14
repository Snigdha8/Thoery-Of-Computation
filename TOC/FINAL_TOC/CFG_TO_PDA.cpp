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
* This function displayes the PDA as per the rules of converting a CFG TO PDA
* Corresponding to each production of each non-terminal, the transition function 'd' is displayed
* Here, 'd' means 'delta' the transition fucntion.
*/
void cfg_to_pda( vector< vector<string> > rules, vector<string> terminals )
{
	int rows = rules.size();
	int cols;
	int i,j;

	for( i=1 ; i<rows ; i++ )
	{
		cols = rules[i].size();
		
		for( j=1 ; j<cols ; j++ )
		{
			cout << "d(q,^," << rules[i][0] << ") -> ";
			cout << "(q," << rules[i][j] << ")\n";  
		}
	}
	
	/*
	* Finally, the transition function for each of the terminals, indicating that they are being popped
	*/
	int t = terminals.size();
	int k;
	for( k=0 ; k<t ; k++ )
	{
		cout << "d(q," << terminals[k] << "," << terminals[k] << ") -> ^\n";
	}
}

int main()
{
	fstream file("g1.csv", ios::in);
    	if(!file.is_open())
	{
		cout << "File not found!\n";
		return 1;
	}
	
    	csvVector csvData;
    	
    	readCSV(file, csvData);
    	vector< vector<string> > rules;
    	vector<string> terminals;

    	/*
    	* The first line in the csv file gives the terminals used in the grammar. We store them in a separate vector of terminals because
    	* they are required in the end when we need to pop 
    	*/
    	string s1;
   	csvVector::iterator i = csvData.begin();
	for( vector<string>::iterator j = i->begin(); j != i->end(); j++  )
    	{
    		s1 = *j;
    		terminals.push_back(s1);
	}
    	rules.push_back(terminals);
    	i++;
	
	/*
	* Data from file is stored in a 2D vector of vectors of string called as 'rules'.
	*/
    	for( ; i != csvData.end(); i++ )
    	{
        	vector<string> temp;
        	for( vector<string>::iterator j = i->begin(); j != i->end(); j++  )
       		{
	    		s1 = *j;
	    		temp.push_back(s1);
		}
        	rules.push_back(temp);  	
 	}
	
	/*
	* The CFG stored in 'rules' is displayed
	*/
 	cout << "\nTHE GRAMMAR IS : \n";
 	int j,k;
	int rows = rules.size();
	int cols;
	for( k=1 ; k<rows ; k++ )
	{
		cols = rules[k].size();
		cout << rules[k][0] << " -> ";
		for( j=1 ; j<cols-1 ; j++ )
		{
			cout << rules[k][j] << " | ";
		}
		cout << rules[k][j] << "\n";
	}

	cout << "\nCONVERTING TO PDA \n";
	cfg_to_pda(rules,terminals);

	return 0;
}
