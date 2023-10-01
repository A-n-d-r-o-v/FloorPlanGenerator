#include "RoomHandler.h"

RoomHandler::RoomHandler(std::vector<RoomId> roomTree, Rectangle houseSize) {
	this->roomTree = roomTree;
	this->houseSize = houseSize;
}

void RoomHandler::createRooms() {
	processNodes(this->roomTree, {});
	findRoomNeighbors();
	//createDoors(this->rooms); // !! TODO !!
}

void RoomHandler::createWalls()
{
	for (const auto& room : rooms) {
		
	}
}

void RoomHandler::processNodes(std::vector<RoomId>& nodes, std::optional<Room> parent)
{
	Rectangle container;
	if (parent.has_value()) {
		Room* room = &parent.value();
		container = Rectangle{ (float)(room->width), (float)(room->height), (float)(room->x), (float)(room->y) };
	}
	else {
		container = houseSize;
	}
	std::vector<std::pair<Room, std::vector<RoomId>>> roomIdsWithChildren;
	std::vector<RoomId> childrenToVisit;

	// Process root nodes
	Array<Number> dataPoints;
	for (auto& node : nodes) {
		if (parent.has_value()) {
			node.area = parent.value().roomId.name;
		}

		dataPoints.emplace_back((float)node.size);

		if (node.hasChildren) {
			int idx = 0;
			for (auto& child : node.children) {
				childrenToVisit.emplace_back(child);
				idx++;
			}
		}
	}
	// datapoints
	// container
	auto result = SolveSquarifiedTreemap(dataPoints, container);
	for (int i = 0; i < result.size(); ++i) {
		auto& rect = result[i];
		auto& childRoomId = nodes[i];
		Room room = Room(rect.X, rect.Y, rect.Width, rect.Height, childRoomId);
		this->rooms.emplace_back(room);

		if (childRoomId.hasChildren) {
			std::pair<Room, std::vector<RoomId>> roomChildren = std::make_pair(room, childrenToVisit);
			roomIdsWithChildren.emplace_back(roomChildren);
		}
	}

	if (!roomIdsWithChildren.empty()) {
		for (auto& room : roomIdsWithChildren) {
			std::vector<RoomId> children = room.second;
			Room parent = room.first;
			processNodes(children, std::make_optional(parent));
		}
	}
}

void RoomHandler::findRoomNeighbors()
{
	for (auto& room : this->rooms) {
		if (room.roomId.hasChildren) {
			continue;
		}
		for (auto& other : this->rooms) {
			if (&room == &other || other.roomId.hasChildren) {
				continue;
			}

			bool xOverlap = (room.x <= (other.x + other.width)) && ((room.x + room.width) >= other.x);
			bool yOverlap = (room.y <= (other.y + other.height)) && ((room.y + room.height) >= other.y);

			if (!xOverlap || !yOverlap) {
				continue;
			}
			room.addNeighbor(other);

			// Create wall segments
			float xStart = std::max(room.x, other.x);
			float xEnd = std::min(room.x + room.width, other.x + other.width);

			float yStart = std::max(room.y, other.y);
			float yEnd = std::min(room.y + room.height, other.y + other.height);

			walls.emplace_back(Wall(xStart, yStart, xEnd, yEnd));

		}
	}
}

/*
void RoomHandler::createDoors(std::vector<Room>& rooms)
{
	std::cout << "I'm alive 1" << std::endl;
	std::stack<std::vector<RoomId>> childrenToVisit;
	for (int room_idx = 0; room_idx < rooms.size(); ++room_idx) {
		for (int next_idx = 0; next_idx < rooms.size(); ++next_idx) {
			if (next_idx <= room_idx) {
				continue;
			}
			Room room = rooms[room_idx];
			auto roomNeighbors = rooms[room_idx].getNeighbors();
			auto& otherRoom = rooms[next_idx];
			/*
			if (otherRoom.roomId.hasChildren) {
				std::cout << "I'm alive 2" << std::endl;
				childrenToVisit.push(otherRoom.roomId.children);
				// Largest (TODO: connected?) room among children
				std::optional<Room> largestChild = findLargestRoom(otherRoom.roomId.children);
				std::cout << largestChild.has_value() << std::endl;
				if (largestChild.has_value()) {
					otherRoom = largestChild.value();
				}
				else {
					continue;
				}
				std::cout << "I'm alive 5" << std::endl;
			}
			
			if (true) {}
			else {
				// Other is a neighbor to room
				bool isNeighbor = false;
				for (auto& nbor : roomNeighbors) {
					if (&otherRoom == &nbor) {
						isNeighbor = true;
						break;
					}
				}

				if (isNeighbor) {
					rooms[room_idx].addConnectedNeighbor(otherRoom);
					otherRoom.isConnectedToStart = true;
				}
			}
		}
	}
	while (!childrenToVisit.empty()) {
		std::vector<Room> asRooms;
		std::vector<RoomId> next = childrenToVisit.top();
		childrenToVisit.pop();
		for (auto& roomId : next) {
			asRooms.emplace_back(*findRoomWithId(roomId));
		}
		createDoors(asRooms);
	}
*/


std::vector<Room> RoomHandler::getRooms()
{
	return this->rooms;
}

std::optional<Room> RoomHandler::findLargestRoom(const std::vector<RoomId>& rooms) {
	RoomId largestRoomId = rooms[0];

	for (const RoomId& roomId : rooms) {
		if (roomId.size > largestRoomId.size) {
			largestRoomId = roomId;
		}
	}
	std::optional<Room> optionalLargestRoom = findRoomWithId(largestRoomId);

	if (optionalLargestRoom.has_value()) {
		std::cout << "I'm alive!" << std::endl;
		Room largestRoom = optionalLargestRoom.value();
		std::cout << "still!" << std::endl;
		return largestRoom;
	}
	return {};
}

std::optional<Room> RoomHandler::findRoomWithId(RoomId id)
{
	for (const auto& room : this->rooms) {
		if (room.roomId == id) {
			return std::make_optional(room);
		}
	}
	return {};
}
