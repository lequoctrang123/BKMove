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
    // TODO Q5.1
    (void)fromStopId; (void)toStopId;
    throw logic_error("TODO Q5.1: BKMove::findDirectRoutes");
}

vector<JourneyResult> BKMove::findJourneys(string fromStopId, string toStopId) {
    // TODO Q5.2
    (void)fromStopId; (void)toStopId;
    throw logic_error("TODO Q5.2: BKMove::findJourneys");
}
