// FloorPlanGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//#include "SquarifiedTreemap.hpp"
#include "Room.h"
#include "RoomHandler.h"

int main()
{
    std::vector<RoomId> roomOrder = {
        RoomId("Living room", 11),
        RoomId("Kitchen area", 8, {RoomId("Pantry", 2), RoomId("Kitchen", 3), RoomId("Laundry", 1)}),
        RoomId("Dining room", 6),
        RoomId("Bedroom", 10),
        RoomId("Bathroom", 3)
    };
    /*
    std::vector<RoomId> roomOrder = {
        RoomId("Living room", 15),
        RoomId("Kitchen area", 5, {RoomId("Pantry", 1), RoomId("Kitchen", 3), RoomId("Laundry", 1)}),
        RoomId("Master bedroom", 10),
        RoomId("Bedroom 2", 8),
        RoomId("Bathroom", 3)
    };
    */

    int width = 600, height = 400;

    Rectangle container = { width, height };
    RoomHandler roomHandler = RoomHandler(roomOrder, container);

    roomHandler.createRooms();
    
    return 0;
}