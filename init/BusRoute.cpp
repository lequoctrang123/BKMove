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
    if(!built) return 0;
    if(direction==OUTBOUND) return outboundCount;
    return this->stops.size()-outboundCount+2;
    //(void)direction;
    //throw logic_error("TODO Q3: BusRoute::getStopCount");
}

int BusRoute::physicalIndex(int index, Direction direction) {
    if(!built || index<0 || index>=getStopCount(direction)){
        throw out_of_range("Index invalid!");
    }
    if(direction==OUTBOUND) return index;
    return (outboundCount - 1 + index) % stops.size();
    //(void)index; (void)direction;
    //throw logic_error("TODO Q3: BusRoute::physicalIndex");
}

BusStop& BusRoute::getStop(int index, Direction direction) {
    return stops.get(physicalIndex(index, direction));
    //(void)index; (void)direction;
    //throw logic_error("TODO Q3: BusRoute::getStop");
}

void BusRoute::build(SLinkedList<BusStop>& outbound, SLinkedList<BusStop>& inbound) {
    if(!built){
        for(int i=0; i<outbound.size(); i++){
            stops.add(outbound.get(i));
        }
        for(int i=1; i<inbound.size()-1; i++){
            stops.add(inbound.get(i));
        }
        built=1;
        outboundCount=outbound.size();
    }
    else{
        stops.clear();
        for(int i=0; i<outbound.size(); i++){
            stops.add(outbound.get(i));
        }
        for(int i=1; i<inbound.size()-1; i++){
            stops.add(inbound.get(i));
        }
        outboundCount=outbound.size();
    }
    //(void)outbound; (void)inbound;
    //throw logic_error("TODO Q3: BusRoute::build");
}

int BusRoute::getHopCount(string fromStopId, string toStopId, Direction direction) {
    int startIdx=-1;
    int endIdx=-1;
    for(int i=0; i<getStopCount(direction); i++){
        if(getStop(i,direction).getId()==fromStopId){
            startIdx=i;
        }
        if(getStop(i,direction).getId()==toStopId){
            endIdx=i;
        }
    }

    if(startIdx==-1 || endIdx==-1 || startIdx>endIdx){
        return -1;
    }
    return endIdx-startIdx;
    //(void)fromStopId; (void)toStopId; (void)direction;
    //throw logic_error("TODO Q3: BusRoute::getHopCount");
}
