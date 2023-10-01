#pragma once

#ifndef ROOM_HANDLER
#define ROOM_HANDLER

#include <stack>
#include <unordered_map>

#include "Room.h"
#include "SquarifiedTreemap.hpp"
#include <optional>

class RoomHandler
{
public:
	RoomHandler(std::vector<RoomId> roomTree, Rectangle houseSize);
	void createRooms();

	std::vector<Wall> walls;

	std::vector<Room> getRooms();

	std::optional<Room> findLargestRoom(std::vector<RoomId>& rooms);
	std::optional<Room> findRoomWithId(RoomId id);

private:
	std::vector<RoomId> roomTree;
	void processNodes(std::vector<RoomId>& nodes, std::optional<Room> parent);
	Rectangle houseSize; // houseSize.Width, houseSize.Height (I think)
	std::vector<Room> rooms;
	std::vector<RoomId> areas;

	void findRoomNeighbors();
};

#endif