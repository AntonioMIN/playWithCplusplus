#include<iostream>
#include<fstream>
#include<deque>
#include"zero.h"
using namespace std;
deque<string> words;
void loadWords()
{
	fstream ifile;
	ifile.open("input.txt",ifstream::in);
	int count;
	string str;
	ifile>>count;
	for(int i=0;i<count;i++)
	{
		ifile>>str;
		words.push_back(str);
	}
}
void Hangman()
{
	string str=words[random()%words.size()];
	deque<bool> corrected(str.size(),false);
	deque<char> misses;
	int life=6;
	while(life)
	{
		cls();
		cout<<"Life : "<<life<<endl;
		for(int i=0;i<str.size();i++)
		{
			if(corrected[i]) cout<<ends<<str[i];
			else cout<<"  ";
		}
		cout<<endl;
		for(int i=0;i<str.size();i++)
		{
			cout<<ends<<"_";
		}
		cout<<"\nMisses : ";
		for(int i=0;i<misses.size();i++) cout<<misses[i]<<ends;

		char guess;
		bool flag=false;

		do{
			flag=false;
			cout<<"\nGuess : ";
			cin>>guess;
			if('A'<=guess && guess<='Z') guess-='A'+'a';
			for(int i=0;i<misses.size() && !flag;i++)
			{
				if(guess==misses[i]) flag=true;
			}
		}while(flag);

		bool correct=false;
		for(int i=0;i<str.size();i++)
		{
			if(str[i]==guess)
			{
				correct=true;
				corrected[i]=true;
			}
		}
		if(!correct)
		{
			misses.push_back(guess);
			--life;
		}
		else
		{
			bool finish=true;
			for(int i=0;i<corrected.size() && finish;i++)
			{
				if(!corrected[i]) finish=false;
			}
			if(finish)
			{
				cout<<"You Win!"<<endl;
				cout<<"Answer : "<<str<<endl;
				pause();
				return;
			}
		}
	}
	cout<<"You Lose!"<<endl;
	cout<<"Answer : "<<str<<endl;
	pause();
}
int main()
{
	loadWords();
	while(true)
	{
		cls();
		cout<<"Hangman Game\n1. Start\n0. Exit\n-> ";
		int c;
		cin>>c;
		if(c==1) Hangman();
		else if(c==0) break;
	}
	return 0;
}
