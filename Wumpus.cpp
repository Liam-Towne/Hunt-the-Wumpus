/*
 *
 * @author Liam Towne
 * @version Spring 2025
 *
 * A program for playing the text-based
 * adventure game Hunt The Wumpus 
*/

#include <iostream>
#include <algorithm> // For random_shuffle
#include "Room.h"
using namespace std;

class Wumpus
{
private:
    Room dungeon[12]; 
    int playerRoom;
    int wumpusRoom;
    int swordRoom; 
    int pitRoom; // Bonus functionality for room with pit
    bool playerHasSword = false;
public:
    Wumpus();
    ~Wumpus();
    int getPlayerRoom();
    void setPlayerRoom(int playerRoom);
    int getWumpusRoom();
    int getSwordRoom();
    int getPitRoom();
    bool getPlayerHasSword();
    void setPlayerHasSword(bool playerHasSword);
    Room* getDungeon();
};

// Constructor
Wumpus::Wumpus()
{
    srand(time(0));

    playerRoom = 0;
    wumpusRoom = 0;
    swordRoom = rand() % 12 + 1;
    do {
        pitRoom = rand() % 12 + 1;
    } while (pitRoom == swordRoom);
    do {
        playerRoom = rand() % 12 + 1;
    } while (playerRoom == wumpusRoom || playerRoom == swordRoom || playerRoom == pitRoom);
    do {
        wumpusRoom = rand() % 12 + 1;
    } while (wumpusRoom == playerRoom || wumpusRoom == swordRoom || wumpusRoom == pitRoom);   

    // An array populated with numConnections each room will have 
    // Using 30 connections for an average of 2.5 connections per room.
    int connectionsLeft = 12;
    int connectionsPerRoom[12] = {1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4};    

    for (int i = 1; i <= 12; i++)
    {   
        int random = rand() % connectionsLeft;
        int numConnections = connectionsPerRoom[random];   
        connectionsPerRoom[random] = connectionsPerRoom[connectionsLeft-1];
        connectionsLeft--;

        int* connections = new int[numConnections];
        for (int j = 0; j < numConnections; j++)
        {
            connections[j] = 0;
        }

        Room room = Room(i, numConnections, connections);
        dungeon[i-1] = room;
    }

    // Fill the connection pool based on desired degrees
    int connectionPool[30];
    int poolIndex = 0;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < dungeon[i].getNumConnections(); j++) {
            connectionPool[poolIndex] = dungeon[i].getRoomNumber();
            poolIndex++;
        }
    }

    random_shuffle(connectionPool, connectionPool + 30);

    for (int i = 0; i < 30; i += 2) {
        int roomA = connectionPool[i];
        int roomB = connectionPool[i + 1];

        // Find new valid pair if rooms are the same
        if (roomA == roomB || dungeon[roomA - 1].containsConnection(roomB)) {
            for (int j = i + 2; j < 30; j++) {
                if (connectionPool[j] != roomA && !dungeon[roomA - 1].containsConnection(connectionPool[j])) {
                    std::swap(connectionPool[i + 1], connectionPool[j]);
                    roomB = connectionPool[i + 1];
                    break;
                }
            }
        }

        dungeon[roomA - 1].newConnection(roomB);
        dungeon[roomB - 1].newConnection(roomA);
    }

}
// Destructor
Wumpus::~Wumpus()
{
}

/// Getters and setters:
int Wumpus::getPlayerRoom()
{
    return playerRoom;
}

void Wumpus::setPlayerRoom(int pRoom)
{
    playerRoom = pRoom;
}

int Wumpus::getWumpusRoom()
{
    return wumpusRoom;
}

int Wumpus::getSwordRoom()
{
    return swordRoom;
}

int Wumpus::getPitRoom()
{
    return pitRoom;
}

bool Wumpus::getPlayerHasSword()
{
    return playerHasSword;
}

void Wumpus::setPlayerHasSword(bool playerHasSword)
{
    this->playerHasSword = playerHasSword;
}

Room* Wumpus::getDungeon()
{
    return dungeon;
}

int main()
{
    cout << "Welcome to Hunt the Wumpus!" << endl;
    cout << "You are in a dark dungeon with 12 rooms." << endl;
    cout << "Your goal is to kill the Wumpus." << endl;
    cout << "Be careful, there are pits in some rooms. You can feel a draft if you are near a pit." << endl;
    cout << "There is a sword in one of the rooms. You will need to be carrying the sword in order to kill the Wumpus." << endl;
    cout << "If you run into the Wumpus without the sword, the Wumpus will eat you." << endl;
    cout << "You can smell the Wumpus if you are in an adjacent room." << endl;
    cout << "Good luck!" << endl << endl;

    if (true);

    Wumpus game = Wumpus();

    Room* dungeon = game.getDungeon();

    // Debugging 
    
    cout << "Debugging: Sword Room: " << game.getSwordRoom() << endl;
    cout << "Debugging: Pit Room: " << game.getPitRoom() << endl;
    cout << "Debugging: Wumpus Room: " << game.getWumpusRoom() << endl << endl;
    cout << "Debugging: Dungeon Connections: " << endl;
    for (int i = 0; i < 12; i++)
    {
        cout << "Room " << dungeon[i].getRoomNumber() << ": ";
        for (int j = 0; j < dungeon[i].getNumConnections(); j++)
        {
            cout << dungeon[i].getConnections()[j] << " ";
        }
        cout << endl;
    }
    cout << endl; // End debugging

    while (true)
    {
        // Game loop
        int currentRoom = game.getPlayerRoom();
        cout << "You are in Room " << currentRoom << "." << endl;

        if (game.getPlayerHasSword() == true)
        {
            cout << "You carry the Sword." << endl;
        }

        if (currentRoom == game.getSwordRoom() && game.getPlayerHasSword() == false)
        {
            cout << "You find and pick up the Sword." << endl;
            game.setPlayerHasSword(true);
        }

        if (currentRoom == game.getPitRoom())
        {
            cout << "You enter the room... " << endl << "And fall directly into a pit! You lose." << endl;
            break;
        }

        if (currentRoom == game.getWumpusRoom())
        {
            if (game.getPlayerHasSword() == true)
            {
                cout << "You find the Wumpus." << endl << "You strike down the Wumpus with your Sword! You win!" << endl;
                break;
            } else
            {
                cout << "You find the Wumpus." << endl << "However, you do not have the Sword. The Wumpus eats you. You lose." << endl;
                break;
            }
        }

        for (int i = 0; i < dungeon[currentRoom-1].getNumConnections(); i++)
        {
            int connectedRoomNumber = dungeon[currentRoom-1].getConnections()[i];

            if (connectedRoomNumber == game.getWumpusRoom())
            {
                cout << "You can smell the Wumpus." << endl;
            }

            if (connectedRoomNumber == game.getPitRoom())
            {
                cout << "You can feel a draft." << endl;
            }
        }

        cout << "You can move to Room(s): ";
        for (int i = 0; i < dungeon[currentRoom-1].getNumConnections(); i++)
        {
            if (dungeon[currentRoom-1].getConnections()[i] != 0) {
                cout << dungeon[currentRoom-1].getConnections()[i] << " ";
            }            
        }
        cout << endl;

        int nextRoom;
        cout << "Enter the room you'd like to move to: ";
        cin >> nextRoom;
        if (cin.fail() || dungeon[currentRoom-1].containsConnection(nextRoom) == false)
        {
            cout << "Invalid input. Please enter a connected room number." << endl << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        game.setPlayerRoom(nextRoom);
        cout << endl;
    }

    return 0;
}


