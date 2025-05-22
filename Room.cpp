/*
 *
 * @author Liam Towne
 * @version Spring 2025
 *
 * A class for a Room object that stores information
 * about the room and its connections to other rooms
*/

#include <iostream>
#include "Room.h"
using namespace std;

// Constructor
Room::Room(int roomNumber, int numConnections, int* connections)
{
    this->roomNumber = roomNumber;
    this->numConnections = numConnections;
    this->connections = new int[numConnections];
    for (int i = 0; i < numConnections; i++)
    {
        this->connections[i] = connections[i];
    }
}

// Default constructor
Room::Room()
{
    this->roomNumber = 0;
    this->numConnections = 0;
}

// Destructor
Room::~Room()
{
}

// Getters and setters:
int Room::getRoomNumber()
{
    return roomNumber;
}

int Room::getNumConnections()
{
    return numConnections;
}

int* Room::getConnections()
{
    return connections;
}

void Room::setConnections(int* connections)
{
    this->connections = connections;
}

void Room::newConnection(int connection)
{
    for (int i = 0; i < numConnections; i++)
    {
        if (connections[i] == 0)
        {
            connections[i] = connection;
            break;
        }
    }
}

// Returns true if the room has available space for a new connection
bool Room::hasConnections()
{    
    bool hasConnections = false;
    for (int i = 0; i < numConnections; i++)
    {
        if (connections[i] == 0)
        {
            hasConnections = true;
        }
    }
    return hasConnections;
}

bool Room::containsConnection(int connection)
{
    for (int i = 0; i < numConnections; i++)
    {
        if (connections[i] == connection)
        {
            return true;
        }
    }
    return false;
}

// End of Room.cpp

