#include "LLDoubleCircular.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
LLDoubleCircular::LLDoubleCircular()
{
	ifstream playlistFile;
	playlistFile.open("Playlist.txt");

	if (playlistFile.is_open())
	{
		string line;
		while (getline(playlistFile, line))
		{
			stringstream ss(line);
			string songTitle, songPath;

			getline(ss, songTitle, ',');
			getline(ss, songPath);


			NodePointer newNode = new Node(songTitle, songPath);

			if (first == nullptr)
			{
				first = newNode;
				newNode->next = newNode;
				newNode->previous = newNode;
			}
			else
			{

				NodePointer ptrLast = first->previous;
				newNode->next = first;
				newNode->previous = ptrLast;
				ptrLast->next = newNode;
				first->previous = newNode;

			}
		}

		playlistFile.close();


	}
	else
	{
		cerr << "Error opening Playlist file." << endl;
	}
}
LLDoubleCircular::~LLDoubleCircular()
{
	NodePointer current = first, nextnode;
	while (current != nullptr) {
		nextnode = current->next;
		delete current;
		current = nextnode;
		if (current == first)
			break;
	}
	first = nullptr;
}
void LLDoubleCircular::addSong(const ElementType& songTitle, const ElementType& songPath)
{
	NodePointer newSong = new Node(songTitle, songPath);
	if (first == nullptr)
	{
		first = newSong;
		newSong->next = newSong;
		newSong->previous = newSong;
	}
	else
	{

		NodePointer ptrLast = first->previous;
		newSong->next = first;
		newSong->previous = ptrLast;
		ptrLast->next = newSong;
		first->previous = newSong;

	}

}
void LLDoubleCircular::removeSong(const ElementType& songTitle)
{
	if (first == nullptr)
	{
		cout << "List is empty" << endl;
		return;
	}

	NodePointer temp = first;
	do
	{
		if (temp->songTitle == songTitle)
		{
			if (temp == first)
			{
				first = temp->next;
			}

			temp->previous->next = temp->next;
			temp->next->previous = temp->previous;

			cout << songTitle << " is deleted" << endl;

			delete temp;
			return;
		}

		temp = temp->next;
	} while (temp != first);
	cout << "Song not found in the list." << endl;

}
void LLDoubleCircular::searchForASong(const ElementType& songTitle)
{

	bool found = false;
	NodePointer ptr = first;

	if (first == nullptr)
	{
		cerr << "Error: The playlist is empty." << endl;
		return;
	}

	do
	{
		if (ptr->songTitle == songTitle)
		{
			found = true;
			break;
		}
		ptr = ptr->next;

	} while (ptr != first);


	if (found == false)
	{
		cout << "Song not found!" << endl;
		return;
	}
	else if (found == true)
	{
		cout << "Found the song!" << endl;
	}
	else
	{
		cout << "Error!" << endl;
	}
}
void LLDoubleCircular::ShufflePlaylist()
{

	if (first == nullptr || first->next == first) {
		return;
	}

	int n = 0;
	NodePointer temp = first;
	do {
		n++;
		temp = temp->next;
	} while (temp != first);

	srand(time(0));

	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		NodePointer nodeI = getNodeAtIndex(i);
		NodePointer nodeJ = getNodeAtIndex(j);

		string tempST = nodeI->songTitle;
		nodeI->songTitle = nodeJ->songTitle;
		nodeJ->songTitle = tempST;

		string tempSP = nodeI->songPath;
		nodeI->songPath = nodeJ->songPath;
		nodeJ->songPath = tempSP;
	}


}
void LLDoubleCircular::printPlaylist() const
{

	if (first == nullptr)
	{

		cerr << "The playlist is empty." << endl;
		return;

	}
	else
	{
		NodePointer ptr = first;
		do {
			cout << ptr->songTitle << endl;
			ptr = ptr->next;

		} while (ptr != first);
	}

}
int LLDoubleCircular::numberOfSongs()
{
	int counter = 0;
	NodePointer ptr = first;
	while (ptr != nullptr) {
		counter++;
		ptr = ptr->next;
		if (ptr == first) {
			break;
		}
	}
	return counter;

}
void LLDoubleCircular::moveSong(const ElementType& movedSongTitle, const ElementType& afterSongTitle)
{
	if (first == nullptr)
	{
		cerr << "The playlist is empty." << endl;
		return;
	}

	NodePointer current = first;

	do
	{
		if (current->songTitle == movedSongTitle)
		{
			current->previous->next = current->next;
			current->next->previous = current->previous;
			NodePointer destination = first;
			while (destination->songTitle != afterSongTitle)
			{
				destination = destination->next;
				if (destination == first)
				{
					cerr << "song " << afterSongTitle << " not found in the playlist." << endl;
					return;
				}
			}
			current->previous = destination;
			current->next = destination->next;
			destination->next->previous = current;
			destination->next = current;
			cout << "Song " << movedSongTitle << " found in the playlist." << std::endl;
			return;
		}
		current = current->next;
	} while (current != first);
	cout << "song " << movedSongTitle << "  not found in the playlist." << endl;

}
void LLDoubleCircular::shiftForward(const ElementType& currentSongTitle)
{
	if (first == nullptr || first->next == first)
	{
		cout << "The playlist is empty or don't have that song." << endl;
		return;
	}
	else
	{
		NodePointer ptr = first;
		while (ptr != nullptr)
		{
			if (ptr->songTitle == currentSongTitle)
			{
				ptr = ptr->next;
				cout << "The current song is (" << ptr->songTitle << ")" << endl;
				break;
			}
			ptr = ptr->next;
		}
	}
}
void LLDoubleCircular::shiftBackward(const ElementType& currentSongTitle)
{
	if (first == nullptr || first->next == first)
	{
		cout << "The playlist is empty or don't have that song." << endl;
		return;
	}
	else
	{
		NodePointer ptr = first;
		while (ptr != nullptr)
		{
			if (ptr->songTitle == currentSongTitle)
			{
				ptr = ptr->previous;
				cout << "The current song is (" << ptr->songTitle << ")" << endl;
				break;
			}
			ptr = ptr->previous;
		}
	}
}
void LLDoubleCircular::exitTheProgram()
{
	ofstream write;
	write.open("Playlist.txt");
	if (first == nullptr)
	{
		if (write.is_open())
		{
			write << " " << endl;
			cout << "Playlist is saved!" << endl;
		}
		else
			cerr << "Error: opening the file." << endl;
	}
	else {

		if (write.is_open())
		{
			NodePointer ptr = first;
			do {
				write << ptr->songTitle << "\n";
				ptr = ptr->next;

			} while (ptr != first);
			write.close();
			cout << "Playlist is saved!" << endl;
			exit(0);
		}
		else
		{
			cerr << "Error: opening the file." << endl;
		}
	}

}
void LLDoubleCircular::displayMenu()
{
	cout << endl;
	cout << "---------------------------------------" << endl;
	cout << "1) Add a Song.\n"
		<< "2) Remove a Song.\n"
		<< "3) Number of Songs.\n"
		<< "4) Search For a Song.\n"
		<< "5) Shuffle the Playlist.\n"
		<< "6) Move a Song.\n"
		<< "7) Shift Forward.\n"
		<< "8) Shift Backward.\n"
		<< "9) Delete the playlist.\n"
		<< "10) Exit." << endl;
	cout << "---------------------------------------" << endl;

}
int main()
{

		LLDoubleCircular l;
		int option;
		string name, artist;
		string fname, fartist;
		do
		{
			l.printPlaylist();
			l.displayMenu();
			cout << "Select option: ";
			cin >> option;

			switch (option)
			{

			case 1:
				cout << "enter music name and artist name" << endl;

				cin >> name >> artist;
				l.addSong(name, artist);
				break;
			case 2:
				cout << "enter music name and artist name you want to delete" << endl;

				cin >> name >> artist;
				l.removeSong(name);
				break;
			case 3:
				cout << "number of songs " << l.numberOfSongs() << endl;
				break;
			case 4:
				cout << "enter song name and artist that you search about: " << endl;
				cin >> name >> artist;
				l.searchForASong(name);
				break;
			case 5:
				l.ShufflePlaylist();
				break;

			case 6: // elmove feha moshklaa
				cout << "enter song name and artist you want to move " << endl;
				cin >> name;
				cout << "enter song name and artist you want to moved after it" << endl;

				cin >> fname;
				l.moveSong(name, fname);
				break;
			case 7:
				cout << "enter song name and artist  " << endl;
				cin >> name >> artist;
				l.shiftForward(name);
				break;
			case 8:
				cout << "enter song name and artist  " << endl;
				cin >> name >> artist;
				l.shiftBackward(name);
				break;
			case 9:
				l.exitTheProgram();
				break;

			}

		} while (option != 9);
	
}