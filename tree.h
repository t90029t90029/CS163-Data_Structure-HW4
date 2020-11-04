//Shang Chun, Lin : CS163 program#4

//the purpose of this file is to build a tree and store the data from the external file.

#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
const char file_name[] = "song.txt";
const int SIZE = 201;

struct hold_a_song
{
	char * artist;
	char * title;	//title of the song
	char * album;	//title of the album
	char * key[3];
	char * descrip; //description
};

class song
{
	public:
		song();
		~song();
		int add_a_song(hold_a_song & to_add);
		int search_a_song(char * key_value,hold_a_song & hold);
		int remove_a_song(char * artist_to_remove);
		int display();
		char* find_artist();
		char* find_key(int i);
	private:
		char * artist;
		char * title;	//title of the song
		char * album;	//title of the album
		char * key[3];
		char * descrip; //description
};

struct node
{
	song * data;
	node * left;
	node * right;
};

class table
{
	public:
		table();
		~table();
		int remove_all();
		int read_in(hold_a_song & to_add);
		int add(hold_a_song & to_add);
		int search(char * key_value,hold_a_song & hold);
		node* find_ios(node * previous,song * & hold_data);
		int remove(char * artist);
		int display_match(char * key);
		int get_height();
		bool is_efficient(int & counter);
		int display_all();
	
	private:
		int remove_all(node * & root);
		int add(node * & root,hold_a_song & to_add);
		int search(node * root,char * key_value,hold_a_song & hold);
		node* find_ios(node * root,node * previous,song * & hold_data);
		int remove(node * & root,char * artist);
		int display_match(node * root,char * key);
		int get_height(node * root);
		bool is_efficient(int & counter,node * root);
		int display_all(node * root);
		node * root;
};
