#include "BKMove.h"

void BKMove::addRoute(BusRoute* route) {
    if (route == nullptr) throw invalid_argument("route must not be null");
    routes.push_back(route);
}

int BKMove::getRouteCount() const {
    return static_cast<int>(routes.size());
}

BusRoute* BKMove::getRoute(int index) {
    if (index < 0 || index >= static_cast<int>(routes.size())) {
        throw out_of_range("BKMove route index is out of range");
    }
    return routes[index];
}

vector<RouteResult> BKMove::findDirectRoutes(string fromStopId, string toStopId) {
    vector<RouteResult> results;
    for(int i=0; i<(int)routes.size(); i++){
        if(routes[i]->getHopCount(fromStopId, toStopId, OUTBOUND)!=-1){
            results.push_back(RouteResult(routes[i]->getId(), OUTBOUND, routes[i]->getHopCount(fromStopId, toStopId, OUTBOUND)));
        }
        if(routes[i]->getHopCount(fromStopId, toStopId, INBOUND)!=-1){
            results.push_back(RouteResult(routes[i]->getId(), INBOUND, routes[i]->getHopCount(fromStopId, toStopId, INBOUND)));
        }
    }
    QuickSort<RouteResult> sorter;
    sorter.sort(results.data(), results.size(), [](RouteResult &a, RouteResult &b) {
        if (a.hopCount != b.hopCount) return a.hopCount < b.hopCount ? -1 : 1;
        if (a.routeId != b.routeId) return a.routeId < b.routeId ? -1 : 1;
        if (a.direction != b.direction) return a.direction < b.direction ? -1 : 1;
        return 0;
    });

    return results;
    //(void)fromStopId; (void)toStopId;
    //throw logic_error("TODO Q5.1: BKMove::findDirectRoutes");
}

vector<JourneyResult> BKMove::findJourneys(string fromStopId, string toStopId) {
    vector<JourneyResult> results;
 
    // 0 lần chuyển tuyến: các tuyến trực tiếp
    vector<RouteResult> direct = findDirectRoutes(fromStopId, toStopId);
    for (int i = 0; i < (int)direct.size(); i++) {
        results.push_back(JourneyResult(direct[i].routeId, direct[i].direction, direct[i].hopCount));
    }
 
    // 1 lần chuyển tuyến
    for (int i = 0; i < (int)routes.size(); i++) {
        BusRoute* first = routes[i];
        for (int d1 = 0; d1 < 2; d1++) {
            Direction dir1 = (d1 == 0) ? OUTBOUND : INBOUND;
 
            int fromIdx = first->indexStop(fromStopId, dir1);
            if (fromIdx == -1) continue;
 
            for (int j = 0; j < (int)routes.size(); j++) {
                BusRoute* second = routes[j];
                if (first->getId() == second->getId()) continue;   // phải là 2 route ID khác nhau
 
                for (int d2 = 0; d2 < 2; d2++) {
                    Direction dir2 = (d2 == 0) ? OUTBOUND : INBOUND;
 
                    int toIdx = second->indexStop(toStopId, dir2);
                    if (toIdx == -1) continue;
 
                    // Trạm chuyển nằm SAU trạm đi trên chặng 1 (m > fromIdx => không phải trạm xuất phát)
                    int stopCount1 = first->getStopCount(dir1);
                    for (int m = fromIdx + 1; m < stopCount1; m++) {
                        string transferId = first->getStop(m, dir1).getId();
 
                        int secondIdx = second->indexStop(transferId, dir2);
                        // phải nằm TRƯỚC trạm đích trên chặng 2 (secondIdx < toIdx => không phải trạm đích)
                        if (secondIdx == -1 || secondIdx >= toIdx) continue;
 
                        int hop1 = m - fromIdx;
                        int hop2 = toIdx - secondIdx;
                        results.push_back(JourneyResult(first->getId(), dir1,
                                                        transferId,
                                                        second->getId(), dir2,
                                                        hop1 + hop2));
                    }
                }
            }
        }
    }
 
    QuickSort<JourneyResult> sorter;
    sorter.sort(results.data(), (int)results.size(),
                [](JourneyResult& a, JourneyResult& b) -> int {
        if (a.transfers != b.transfers) return a.transfers < b.transfers ? -1 : 1;
        if (a.totalHops != b.totalHops) return a.totalHops < b.totalHops ? -1 : 1;
        if (a.firstRouteId != b.firstRouteId) return a.firstRouteId < b.firstRouteId ? -1 : 1;
        if (a.firstDirection != b.firstDirection) return a.firstDirection < b.firstDirection ? -1 : 1;
        if (a.transferStopId != b.transferStopId) return a.transferStopId < b.transferStopId ? -1 : 1;
        if (a.secondRouteId != b.secondRouteId) return a.secondRouteId < b.secondRouteId ? -1 : 1;
        if (a.secondDirection != b.secondDirection) return a.secondDirection < b.secondDirection ? -1 : 1;
        return 0;
    });
 
    return results;

    //(void)fromStopId; (void)toStopId;
    //throw logic_error("TODO Q5.2: BKMove::findJourneys");
}
