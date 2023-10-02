#include <iostream>

#include "Room.h"
#include "RoomHandler.h"

int main()
{
    srand(static_cast <unsigned> (time(0)));

    std::vector<RoomId> roomOrder = {
        RoomId("Living room", 10),
        //RoomId("Living area", 11, {RoomId("Living roomArea", 10, {RoomId("Living", 4), RoomId("Dead", 4)}), RoomId("Some room", 3)}),
        RoomId("Kitchen area", 10, {RoomId("Pantry", 2), RoomId("Kitchen", 3), RoomId("Laundry", 1)}),
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

    std::cout << "Rooms : [";
    for (const auto& room : roomHandler.getRooms()) {
        std::cout << "[" << room.x << ", " << room.y << ", " << room.width << ", " << room.height << "], ";
    }
    std::cout << "]" << std::endl << std::endl;

    std::cout << "Walls : [";
    for (const auto& wall : roomHandler.walls) {
        for (const auto& lineSeg : wall.lineSegments) {
            std::cout << "[" << lineSeg.startX << ", " << lineSeg.startY << ", " << lineSeg.endX<< ", " << lineSeg.endY << "], ";
        }
    }
    std::cout << "]" << std::endl << std::endl;

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