#include <iostream>

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

    // Line segments:
    // for wall in roomHandler.walls
    //      for lineSegment in wall.lineSegments

    // for room in roomHandler.getRooms()
    //     access room.x, room.y, room.width, room.height
    //     here you can also find room.roomId
    //          roomId contains: room name (roomId.name), input size

    // house size: roomHandler.houseSize (todo: make a getter)

    return 0;
}