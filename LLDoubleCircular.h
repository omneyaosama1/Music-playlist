#pragma once
#include <iostream>
using namespace std;
typedef string ElementType;

class LLDoubleCircular
{
private:

    class Node {
    public:
        ElementType songPath, songTitle;
        Node* next;
        Node* previous;
        Node(const ElementType& songTitle, const ElementType& songPath) :songTitle(songTitle), songPath(songPath), next(0), previous(0) {}
    };

    typedef Node* NodePointer;
    NodePointer first;

    NodePointer getNodeAtIndex(int index)
    {
        NodePointer temp = first;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp;
    }

public:
    LLDoubleCircular();

    ~LLDoubleCircular();

    void addSong(const ElementType& songTitle, const ElementType& songPath);

    void removeSong(const ElementType& songTile);

    void printPlaylist() const;

    int numberOfSongs();

    void searchForASong(const ElementType& songTitle);

    void ShufflePlaylist();

    void moveSong(const ElementType& movedSongTitle, const ElementType& afterSongTitle);

    void shiftForward(const ElementType& currentSongTitle);

    void shiftBackward(const ElementType& currentSongTitle);

    void exitTheProgram();

    void displayMenu();
};