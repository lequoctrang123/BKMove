#include "BusRoute.h"

BusRoute::BusRoute(string routeId)
    : routeId(routeId), outboundCount(0), built(false) {}

string BusRoute::getId() const {
    return routeId;
}

bool BusRoute::isBuilt() const {
    return built;
}

int BusRoute::getStopCount(Direction direction) {
    // TODO Q3
    (void)direction;
    throw logic_error("TODO Q3: BusRoute::getStopCount");
}

int BusRoute::physicalIndex(int index, Direction direction) {
    // TODO Q3
    (void)index; (void)direction;
    throw logic_error("TODO Q3: BusRoute::physicalIndex");
}

BusStop& BusRoute::getStop(int index, Direction direction) {
    // TODO Q3
    (void)index; (void)direction;
    throw logic_error("TODO Q3: BusRoute::getStop");
}

void BusRoute::build(SLinkedList<BusStop>& outbound, SLinkedList<BusStop>& inbound) {
    // TODO Q3
    (void)outbound; (void)inbound;
    throw logic_error("TODO Q3: BusRoute::build");
}

int BusRoute::getHopCount(string fromStopId, string toStopId, Direction direction) {
    // TODO Q3
    (void)fromStopId; (void)toStopId; (void)direction;
    throw logic_error("TODO Q3: BusRoute::getHopCount");
}
