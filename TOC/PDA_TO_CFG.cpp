#include<bits/stdc++.h>
using namespace std;

void pda_to_cfg( vector< std::vector<string> > pda , int num_states )
{
	int rows = pda.size();
	int cols;

	int k = 1;
	int i,j,num_terms;
	cout << "****************************************************************************************************\n";
	cout << "Since no. of states are " << num_states << " xi will range from i=0 to i=num_states-1\n\n";
	int total_num_productions = 0;
	cout << "If we denote by S the start symbol of the grammar, the productions that we need to begin are those of the form \n";
	cout << "				S -> [ q0,Z,xi ]\n";
	cout << "where q0 is the initial state. Because in accepting strings by empty stack the final state is irrelevant, we \ninclude a productionof this type for every possible state xi\n\n";
	total_num_productions = total_num_productions + num_states;

	for( i=0 ; i<rows ; i++ )
	{
		cols = pda[i].size();
		num_terms = cols - 4;

		if( num_terms > 1 )
		{
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
			if( pda[i][4] == "^" )
			{
				cout << "[ " << pda[i][0] << "," << pda[i][2] << "," << pda[i][3] << " ] -> " << pda[i][1] << "\n";
			}
			else
			{
				cout << "[ " << pda[i][0] << "," << pda[i][2] << ",x0 ] -> " << pda[i][1] << " [ " << pda[i][3] << ",";
				cout << pda[i][4] << "," << "x0 ]\n";
			}
		}
	}
}

int main()
{
	int num_states;
	cout << "Enter the number of states in your PDA \n";
	cin >> num_states;

	cout << "Enter the number of moves\n";
	int num_moves;
	cin >> num_moves;

	vector< std::vector<string> > pda;
	int i,num_terms,j;
	string state;
	string input;
	string stack_symbol;
	string transition_state;
	string a;

	for( i=0 ; i<num_moves ; i++ )
	{
		vector<string> temp;
		cout << "Enter the state\n";
		cin >> state;
		temp.push_back(state);

		cout << "Enter the input terminal\n";
		cin >> input;
		temp.push_back(input);

		cout << "Enter the stack symbol\n";
		cin >> stack_symbol;
		temp.push_back(stack_symbol);

		cout << "Enter the transition state\n";
		cin >> transition_state;
		temp.push_back(transition_state);

		cout << "Enter the number of terms\n";
		cin >> num_terms;

		for( j=0 ; j<num_terms ; j++ )
		{
			cout << "Enter term no. " << j+1 << "\n";
			cin >> a;
			temp.push_back(a);
		}

		pda.push_back(temp);
	}

	int rows = pda.size();
	int cols;
	for( i=0 ; i<rows ; i++ )
	{
		cols = pda[i].size();

		cout << pda[i][0] << " " << pda[i][1] << " " << pda[i][2] << " (" << pda[i][3] << ",";
		for( j=4 ; j<cols ; j++ )
		{
			cout << pda[i][j];
		}
		cout << ")\n";
	}

	cout << "CONVERTING TO CFG :)\n\n";
	pda_to_cfg(pda, num_states);
	return 0;
}