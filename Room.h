/*
 * @author Liam Towne
 * @version Spring 2025
 * 
 * A header for the Room class
*/

#ifndef ROOM_H
#define ROOM_H

class Room
{ 
    private:
        int roomNumber;
        int numConnections;
        int* connections;

    public: 
        Room(int roomNumber, int numConnections, int* connections);
        Room();
        ~Room();
        int getRoomNumber();
        int* getConnections();
        void setConnections(int* connections);
        void newConnection(int connection);
        int getNumConnections();
        bool hasConnections();
        bool containsConnection(int connection);
};

#endif