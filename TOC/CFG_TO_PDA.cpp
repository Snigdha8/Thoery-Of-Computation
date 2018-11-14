#include<bits/stdc++.h>
using namespace std;

void cfg_to_pda( vector< vector<string> > rules, vector<char> terminals )
{
	int rows = rules.size();
	int cols;
	int i,j;

	for( i=0 ; i<rows ; i++ )
	{
		cols = rules[i].size();
		
		for( j=1 ; j<cols ; j++ )
		{
			cout << "d(q,^," << rules[i][0] << ") -> ";
			cout << "(q," << rules[i][j] << ")\n";  
		}
	}

	int t = terminals.size();
	int k;
	for( k=0 ; k<t ; k++ )
	{
		cout << "d(q," << terminals[k] << "," << terminals[k] << ") -> ^\n";
	}
}

int main()
{
	int num_terminals;
	int num_non_terminals;
	cout << "Enter the no. of terminals\n";
	cin >> num_terminals;

	int k;
	vector<char> terminals;
	char ch;
	for( k=0 ; k<num_terminals ; k++ )
	{
		cin >> ch;
		terminals.push_back(ch);
	}

	cout << "Enter the no. of non-terminals\n";
	cin >> num_non_terminals;

	int i,j;
	int num_productions;
	string non_terminal;
	vector< vector<string> > rules;
	
	string a;
	for( i=0 ; i<num_non_terminals ; i++ )
	{
		cout << "Enter the non-terminal\n";
		cin >> non_terminal;
		vector<string> temp;
		temp.push_back(non_terminal);

		cout << "Enter the no. of productions of that non-terminal\n";
		cin >> num_productions;
		cout << "Enter the productions\n\n";

		for( j=0 ; j<num_productions ; j++ )
		{
			cin >> a;
			temp.push_back(a);
		}
		rules.push_back(temp);
	}

	int rows = rules.size();
	int cols;
	for( i=0 ; i<rows ; i++ )
	{
		cols = rules[i].size();
		cout << rules[i][0] << " -> ";
		for( j=1 ; j<cols-1 ; j++ )
		{
			cout << rules[i][j] << " | ";
		}
		cout << rules[i][j] << "\n";
	}

	cout << "CONVERTING TO PDA \n";
	cfg_to_pda(rules,terminals);

	return 0;
}