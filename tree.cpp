//Shang Chun, Lin : CS163 program#4

//the purpose of this file is to build a tree and store the data from the external file.

#include "tree.h"

using namespace std;


song::song()	//constructor
{
	artist = NULL;
	title = NULL;
	album = NULL;
	for(int i=0;i<3;++i)
	{
		key[i] = NULL;
	}
	descrip = NULL;
}

song::~song()	//destructor
{
	if(artist)
	{
		delete []artist;
	}
	if(title)
	{
		delete []title;
	}
	if(album)
	{
		delete []album;
	}
	if(key[0])
	{
		for(int i=0;i<3;++i)
		{
			delete []key[i];
			key[i] = NULL;
		}
	}
	if(descrip)
	{
		delete []descrip;
	}
	artist = NULL;
	title = NULL;
	album = NULL;
	descrip = NULL;
}

int song::add_a_song(hold_a_song & to_add)	//to add the data of a song into a single node in the tree
{
	if(!to_add.artist)
	{
		return 0;
	}
	artist = new char[strlen(to_add.artist)+1];
	strcpy(artist,to_add.artist);
	title = new char[strlen(to_add.title)+1];
	strcpy(title,to_add.title);
	album = new char[strlen(to_add.album)+1];
	strcpy(album,to_add.album);
	for(int i=0;i<3;++i)
	{
		key[i] = new char[strlen(to_add.key[i])+1];
		strcpy(key[i],to_add.key[i]);
	}
	descrip = new char[strlen(to_add.descrip)+1];
	strcpy(descrip,to_add.descrip);

	return 1;
}

int song::search_a_song(char * key_value,hold_a_song & hold)	//to search a song with a key word through the tree
{
	if(!key_value)
	{
		return 0;
	}
	int success = 0;
	int i = 0;
	while(i<3)
	{
		if(strcmp(key_value,key[i]) == 0)
		{
			hold.artist = new char[strlen(artist)+1];
			strcpy(hold.artist,artist);
			hold.title = new char[strlen(title)+1];
			strcpy(hold.title,title);
			hold.album = new char[strlen(album)+1];
			strcpy(hold.album,album);
			for(int i=0;i<3;++i)
			{
				hold.key[i] = new char[strlen(key[i])+1];
				strcpy(hold.key[i],key[i]);
			}
			hold.descrip = new char[strlen(descrip)+1];
			strcpy(hold.descrip,descrip);
			success = 1;
			i = 3;
		}
		++i;
	}
	return success;
}

int song::remove_a_song(char * artist_to_remove)	//to remove the data of a song by the artist name in the tree
{
	if(!artist_to_remove)
	{
		return 0;
	}
	if(strcmp(artist,artist_to_remove) == 0)
	{
		delete []artist;
		delete []title;
		delete []album;
		for(int i=0;i<3;++i)
		{
			delete []key[i];
			key[i] = NULL;
		}
		delete []descrip;
		artist = NULL;
		title = NULL;
		album = NULL;
		descrip = NULL;

		return 1;
	}
	return 0;
}

int song::display()	//to display the data of a song in a node
{
	if(!artist || !title || !album || !key[0] || !descrip)
	{
		return 0;
	}
	cout<<"Artist : "<<artist<<endl;
	cout<<"The song : "<<title<<endl;
	cout<<"The album : "<<album<<endl;
	for(int i=0;i<3;++i)
	{
		if(key[i])
		{
			cout<<"The key word : "<<key[i]<<endl;
		}
	}
	cout<<"The description : "<<descrip<<endl;
	return 1;
}

char* song::find_artist()	//serve for other functions to provide the private data -- artist name
{
	if(!artist)
	{
		return NULL;
	}
	return artist;
}

char* song::find_key(int i)	//serve for other functions to provide the private data -- a key word
{
	if(!key[i])
	{
		return NULL;
	}
	return key[i];
}

table::table()		//constructor
{
	root = NULL;
}

table::~table()		//destructor
{
	int success = 0;
	success = remove_all();
}

int table::remove_all()		//to destroy everything in the tree -- just serve for the destructor (this one is a wrapper function)
{
	if(!root)
	{
		return 0;
	}
	return remove_all(root);
}

int table::remove_all(node * & root)	//recursion part
{
	if(!root)
	{
		return 0;
	}
	int remove = 0;
	remove += remove_all(root->left) + remove_all(root->right);
	if(root)
	{
		root->data->~song();
		delete root->data;
		root->data = NULL;
		delete root;
	}
	root = NULL;
	return 1+remove;
}

int table::add(hold_a_song & to_add)	//to add a node into the tree with the new data (this one is a wrapper function)
{
	if(!to_add.artist || !to_add.title || !to_add.album || !to_add.key[0] || !to_add.descrip)
	{
		return 0;
	}
	if(!root)
	{
		node * temp = new node;
		temp->data = new song; 
		if(!temp->data->add_a_song(to_add))
		{
			delete temp->data;
			delete temp;
			return 0;
		}
		temp->left = temp->right = NULL;
		root = temp;
		return 1;
	}
	return add(root,to_add);
}

int table::add(node * & root, hold_a_song & to_add)	//recursion part
{
	if(!root)
	{
		node * temp = new node;
		temp->data = new song;
		if(!temp->data->add_a_song(to_add))
		{
			delete temp->data;
			delete temp;
			return 0;
		}
		temp->left = temp->right = NULL;
		root = temp;
		return 1;
	}
	int success = 0;
	if(strcmp(to_add.artist,root->data->find_artist()) < 0)
	{
		success = add(root->left,to_add);
	}	
	else if(strcmp(to_add.artist,root->data->find_artist()) >= 0)
	{
		success = add(root->right,to_add);
	}
	return success;
}

int table::read_in(hold_a_song & to_add)	//to read the data from the external file
{
	int count = 0;
	ifstream file_in;
	file_in.open(file_name);

	if(file_in)
	{
		file_in.get(to_add.artist,SIZE,'|');
		file_in.ignore(100,'|');
		while(!file_in.eof())
		{
			file_in.get(to_add.title,SIZE,'|');
			file_in.ignore(100,'|');

			file_in.get(to_add.album,SIZE,'|');
			file_in.ignore(100,'|');

			for(int i=0;i<3;++i)
			{	
				file_in.get(to_add.key[i],SIZE,'|');
				file_in.ignore(100,'|');
			}

			file_in.get(to_add.descrip,SIZE,'\n');
			file_in.ignore(300,'\n');

			if(add(to_add))
			{
				++count;
			}

			if(to_add.artist)			//reset
			{
				delete []to_add.artist;
				to_add.artist = NULL;
			}
			if(to_add.title)
			{
				delete []to_add.title;
				to_add.title = NULL;
			}
			if(to_add.album)
			{
				delete []to_add.album;
				to_add.album = NULL;
			}
			for(int i=0;i<3;++i)
			{
				if(to_add.key[i])
				{
					delete []to_add.key[i];
					to_add.key[i] = NULL;
				}
			}
			if(to_add.descrip)
			{
				delete []to_add.descrip;
				to_add.descrip = NULL;
			}

			if(!file_in.eof())
			{
				to_add.artist = new char[SIZE];
				to_add.title = new char[SIZE];
				to_add.album = new char[SIZE];
				for(int i=0;i<3;++i)
				{
					to_add.key[i] = new char[SIZE];
				}
				to_add.descrip = new char[SIZE];
				file_in.get(to_add.artist,SIZE,'|');
				file_in.ignore(100,'|');
			}
		}
		file_in.close();
		file_in.clear();
	}
	return count;
}

int table::search(char * key_value,hold_a_song & hold)		//to search a data by the key word in the tree (this one is a wrapper function)
{
	if(!key_value)
	{
		return 0;
	}
	return search(root,key_value,hold);
}

int table::search(node * root,char * key_value,hold_a_song & hold)	//recursion part
{
	if(!root)
	{
		return 0;
	}
	if(root->data->search_a_song(key_value,hold))
	{
		return 1;
	}
	return search(root->left,key_value,hold) + search(root->right,key_value,hold);
}

node* table::find_ios(node * previous,song * & hold_data)	//return a current pointer pointing to the ios with the pointer pointing to the ios data
{
	if(!root->right)
	{
		return NULL;
	}
	return find_ios(root->right,previous,hold_data);
}
node* table::find_ios(node * root,node * previous,song * & hold_data)	//also get the previous pointer to delete the ios
{
	node* current = NULL;
	if(!root->left)
	{
		hold_data = root->data; 	//share the data by the pointer
		return root;
	}
	previous = root;
	current = find_ios(root->left,previous,hold_data);
	return current;
}

int table::remove(char * artist)	//to remove a node by the artist name from the tree (this one is a wrapper function
{
	if(!artist)
	{
		return 0;
	}
	if(!root)
	{
		return 0;
	}
	return remove(root,artist);
}
int table::remove(node * & root,char * artist)	//recursion part
{
	if(!root)
	{
		return 0;
	}

	int count = 0;

	if(root->data->remove_a_song(artist))
	{
		if(!root->left && !root->right)		//delete leaf
		{
			delete root->data;
			root->data = NULL;
			delete root;
			root = NULL;
			return 1;
		}
		else if(root->left && !root->right)	//delete the node with only one child : left
		{
			node * hold = root->left;
			delete root->data;
			root->data = NULL;
			delete root;
			root = hold;
			return 1;
		}
		else if(!root->left && root->right)	//delete the node with only one child : right
		{
			node * hold = root->right;
			delete root->data;
			root->data = NULL;
			delete root;
			root = hold;
			return 1;
		}
		else					//delete the node with 2 children
		{
			delete root->data;
			node * previous = root;
			node * current = find_ios(previous,root->data);		//current points to the ios node and previous is behind the current, and copy the data from ios
			if(current)
			{
				if(current->right)
				{
					node * hold = current->right;	//hold for ios
					current->data = new song;	//avoid affecting the data which the matching node is pointing to
					delete 	current->data;
					current->data = NULL;
					current->right = NULL;
					if(!previous->right->data)	//determine which way we should connect to the hold data
					{
						previous->right = hold;
					}
					else if(!previous->left->data)
					{
						previous->left = hold;
					}
					return 1;
				}
				else
				{
					current->data = new song;	//avoid affecting the data which the matching node is pointing to
					delete 	current->data;
					current->data = NULL;
					if(!previous->right->data)	//determine the ios was on which way
					{
						previous->right = NULL;
					}
					else if(!previous->left->data)
					{
						previous->left = NULL;
					}
					return 1;
				}
			}
		}
	}

	count = remove(root->left,artist);
	count += remove(root->right,artist);
	return count;
}

int table::display_match(char * key)	//to display a matching data by the key word in the tree (this one is a wrapper function)
{
	if(!root)
	{
		return 0;
	}
	if(!key)
	{
		return 0;
	}
	return display_match(root,key);
}
int table::display_match(node * root,char * key)	//recursion part
{
	if(!root)
	{
		return 0;
	}
	int count = 0;
	int i = 0;
	while(i<3)
	{
		if(strcmp(root->data->find_key(i),key) == 0)
		{
			count += root->data->display();
			i = 3;
		}
		++i;
	}
	i = 0;
	count += display_match(root->left,key) + display_match(root->right,key);
	return count;
}

int table::get_height()		//to get the height of the tree (this one is a wrapper function
{
	if(!root)
	{
		return 0;
	}
	return get_height(root);
}

int table::get_height(node * root)	//recursion part
{
	if(!root)
	{
		return 0;
	}
	int left_height = 0;
	int right_height = 0;
	left_height += get_height(root->left) + 1;
	right_height += get_height(root->right) + 1;
	return max(left_height,right_height);
}

bool table::is_efficient(int & counter)		//to evaluate if the tree is balanced or not (this one is a wrapper function)
{
	if(!root)
	{
		return true;
	}
	return is_efficient(counter,root);
}

bool table::is_efficient(int & counter,node * root)	//recursion part
{
	if(!root)
	{
		return true;
	}

	int left_height = get_height(root->left);
	int right_height = get_height(root->right);
	int balance = left_height - right_height;
	if(balance < 0)
	{
		balance = -balance;
	}
	counter = balance;
	if(balance <= 1 && is_efficient(counter,root->left) && is_efficient(counter,root->right))
	{
		return true;
	}
	return false;
}

int table::display_all()	//to display everything in the tree (this one is a wrapper function)
{
	if(!root)
	{
		return 0;
	}
	return display_all(root);
}

int table::display_all(node * root)	//recursion part
{
	if(!root)
	{
		return 0;
	}
	int count = 0;
	count += root->data->display();
	count += display_all(root->left) + display_all(root->right);
	return count;
}
