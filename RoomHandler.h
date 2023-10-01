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
	void createWalls();

	std::vector<Wall> walls;

	std::vector<Room> getRooms();
	std::optional<Room> findLargestRoom(const std::vector<RoomId>& rooms);
	std::optional<Room> findRoomWithId(RoomId id);

private:
	std::vector<RoomId> roomTree;
	void processNodes(std::vector<RoomId>& nodes, std::optional<Room> parent);
	Rectangle houseSize;
	std::vector<Room> rooms;

	float wallThickness = 2;

	void findRoomNeighbors();
	//void createDoors(std::vector<Room>& nodes);
};

#endif