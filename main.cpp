//Shang-Chun,Lin  CS163 program#4 assignment
#include "tree.h"

using namespace std;

//the purpose of this file is to test the structs and classes that I have declared in .h file (working as client program)

int main()
{
	table tree;
	char * key_value = NULL;
	int counter = 0;
	hold_a_song hold;	//representing to_add or retrieve as the argument what we have searched
	hold.artist = NULL;
	hold.title = NULL;
	hold.album = NULL;
	for(int i=0;i<3;++i)
	{
		hold.key[i] = NULL;
	}
	hold.descrip = NULL;
//--------this part is to allocate memories to a struct and make use of it to catch the data from the external file-------------------
	hold.artist = new char[SIZE];
	hold.title = new char[SIZE];
	hold.album = new char[SIZE];
	for(int i=0;i<3;++i)
	{	
		hold.key[i] = new char[SIZE];
	}
	hold.descrip = new char[SIZE];

	cout<<"We have read in "<<tree.read_in(hold)<<" data in the tree."<<endl;

	hold.artist = NULL;
	hold.title = NULL;
	hold.album = NULL;
	for(int i=0;i<3;++i)
	{
		hold.key[i] = NULL;
	}
	hold.descrip = NULL;
//-------------------------------------------------------------------------------------------------------------------------------------

	int answer = 0;
	cout<<"Please type a integer number to choose what you want to do."<<endl<<endl
	<<"1 for adding a new song                       , 2 for searching for a particular key word, "<<endl
	<<"3 for removing by the artist name in the tree , 4 for displaying all matches by the key word, "<<endl
	<<"5 for displaying all data in the table,       , 6 for getting the height of the tree."<<endl
	<<"7 for evaluating the tree is balanced or not  , 8 for quitting the program."<<endl;
	cin>>answer;
	cin.ignore(100,'\n');

	while(answer != 8)
	{
		hold.artist = new char[SIZE];
		hold.title = new char[SIZE];
		hold.album = new char[SIZE];
		for(int i=0;i<3;++i)
		{
			hold.key[i] = new char[SIZE];
		}
		hold.descrip = new char[SIZE];
		key_value = new char[SIZE];

		if(answer == 1)
		{
			cout<<"Please type in the artist name."<<endl;
			cin.get(hold.artist,SIZE,'\n');
			cin.ignore(100,'\n');

			cout<<"Please type in the name of the song."<<endl;
			cin.get(hold.title,SIZE,'\n');
			cin.ignore(100,'\n');

			cout<<"Please type in the name of the album."<<endl;
			cin.get(hold.album,SIZE,'\n');
			cin.ignore(100,'\n');

			cout<<"Please type in three key words of the song."<<endl;
			for(int i=0;i<3;++i)
			{
				cin.get(hold.key[i],SIZE,'\n');
				cin.ignore(100,'\n');
			}

			cout<<"Please type in your description of the song."<<endl;
			cin.get(hold.descrip,SIZE,'\n');
			cin.ignore(300,'\n');

			cout<<"We have added "<<tree.add(hold)<<" data in the tree."<<endl;
			
			cout<<"There are "<<tree.display_all()<<" data in the tree."<<endl;
		}

		if(answer == 2)
		{
			cout<<"Please type in a key word of the song for searching."<<endl;
			cin.get(key_value,SIZE,'\n');
			cin.ignore(100,'\n');

			if(tree.search(key_value,hold))
			{
				cout<<"We find it in the tree !!"<<endl;

				cout<<"The information we have searched for the key is : "<<endl;
				cout<<"Artist : "<<hold.artist<<endl;
				cout<<"The song : "<<hold.title<<endl;
				cout<<"The album : "<<hold.album<<endl;
				for(int i=0;i<3;++i)
				{
					cout<<"The key word : "<<hold.key[i]<<endl;
				}
				cout<<"The description : "<<hold.descrip<<endl<<endl;
			}
			else
			{
				cout<<"We didn't find it in the tree !!"<<endl;
			}
		}

		if(answer == 3)
		{
			cout<<"Please type in an artist name for removing the related data in the tree."<<endl;
			cin.get(hold.artist,SIZE,'\n');
			cin.ignore(100,'\n');

			cout<<"We have removed "<<tree.remove(hold.artist)<<" data in the tree."<<endl;

			cout<<"There are "<<tree.display_all()<<" data in the tree."<<endl;
		}

		if(answer == 4)
		{
			cout<<"Please type in a key word to display all matched in the tree."<<endl;
			cin.get(hold.key[0],SIZE,'\n');
			cin.ignore(100,'\n');
			
			cout<<"There are "<<tree.display_match(hold.key[0])<<" matches in the tree."<<endl;
		}

		if(answer == 5)
		{
			cout<<"There are "<<tree.display_all()<<" data in the tree."<<endl;
		}

		if(answer == 6)
		{
			cout<<"The height of the tree is : "<<tree.get_height()<<endl;
		}

		if(answer == 7)
		{
			if(tree.is_efficient(counter))
			{
				cout<<"The tree is balanced."<<endl;
			}
			else
			{
				cout<<"The tree is not balanced."<<endl
				<<"The difference between right subtree and left subtree is : "<<counter<<endl;
			}
		}
		cout<<"Please type a integer number to choose what you want to do."<<endl<<endl
		<<"1 for adding a new song                       , 2 for searching for a particular key word, "<<endl
		<<"3 for removing by the artist name in the tree , 4 for displaying all matches by the key word, "<<endl
		<<"5 for displaying all data in the table,       , 6 for getting the height of the tree."<<endl
		<<"7 for evaluating the tree is balanced or not  , 8 for quitting the program."<<endl;
		cin>>answer;
		cin.ignore(100,'\n');

		if(hold.artist)			//reset
		{
			delete []hold.artist;
			hold.artist = NULL;
		}
		if(hold.title)
		{
			delete []hold.title;
			hold.title = NULL;
		}
		if(hold.album)
		{
			delete []hold.album;
			hold.album = NULL;
		}
		for(int i=0;i<3;++i)
		{
			if(hold.key[i])
			{
				delete []hold.key[i];
				hold.key[i] = NULL;
			}
		}
		if(hold.descrip)
		{
			delete []hold.descrip;
			hold.descrip = NULL;
		}
		if(key_value)
		{
			delete []key_value;
			key_value = NULL;
		}

		if(counter != 0)
		{
			counter = 0;
		}
	}
	return 0;
}
