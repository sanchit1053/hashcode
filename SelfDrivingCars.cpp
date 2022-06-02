#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

class trip{

    public:

    int num;
    pii startPos, endPos;
    int startTime, endTime;

    trip(int tnum,pii tstartPos, pii tendPos, int tstartTime,int tendTime){
        num = tnum;
        startPos = tstartPos;
        tendPos = endPos;
        startTime = tstartTime;
        endTime = tendTime;
    }

    int tripTime(){
        return abs(startPos.first - endPos.first) + abs(startPos.second - endPos.first);
    }
};

class car{

    public:
    int num;
    pii pos, dest;
    int turnsbusy;

    vector<int> rides;

    car(int tnum){
        num = tnum;
        pos = make_pair(0,0);
        turnsbusy = 0;
    }
};

int main(){
    // freopen("input.txt", "r", stdin);
    int row, col, fleet, noRides, bonus, steps;
    cin >> row >> col >> fleet >> noRides>>bonus >> steps;

    vector<trip*> trips(noRides);
    vector<car*> cars(fleet);

    for(int i = 0; i < noRides; i++){
        pii start, end;
        cin >> start.first >> start.second >> end.first >> end.second;
        int startTime, endTime;
        cin >> startTime >> endTime;
        trips[i] = new trip(i, start, end, startTime, endTime);
    }

    for(int i = 0; i < fleet; i++){
        cars[i] = new car(i);
    }


    for(int step = 0; step < steps; step++){
        for(int i = 0; i < fleet; i++){
            if(cars[i]->turnsbusy > 0){
                continue;
            }
            else{
                int triprec = -1;
                float mostPoints = 0;
                for(int tr = 0; tr < trips.size(); tr++){
                    int timetostart = abs(cars[i]->pos.first - trips[tr]->startPos.first) + abs(cars[i]->pos.second - trips[tr]->startPos.second);
                    int triptime = trips[tr]->tripTime();
                    if(step + timetostart + triptime > trips[tr]->endTime){
                        // will not get point;
                        continue;
                    }
                    if(step + timetostart < trips[tr]->startTime){
                        // will need to wait
                        timetostart = trips[tr]->startTime - step ;
                    }

                    if(timetostart > trips[tr]->endTime){
                        // cannot reach in time
                        continue;
                    }

                    int totaltriptime = timetostart + trips[tr]->tripTime();
                    float points = 1.0 * (trips[tr]->tripTime() + bonus)/ totaltriptime;

                    if(points > mostPoints){
                        mostPoints = points;
                        triprec = tr;
                    }
                }
                if(triprec < 0) continue;
                
                cars[i]->rides.push_back(trips[triprec]->num);
                int timetostart = + abs(cars[i]->pos.first - trips[triprec]->startPos.first) + abs(cars[i]->pos.second - trips[triprec]->startPos.second);
                cars[i]->turnsbusy = trips[triprec]->tripTime() + timetostart;
                cars[i]->dest = trips[triprec]->endPos;

                if(timetostart + step < trips[triprec]->startTime){
                    cars[i]->turnsbusy += trips[triprec]->startTime -timetostart - step;
                }
                // cout << triprec << trips.size()<< endl;
                trips.erase(trips.begin() + triprec);
                // cout << "reached" << endl;
            }
        }
        for(auto x : cars){
            x->turnsbusy --;
        }
    }

    // sort(cars.begin(), cars.end(), [](car& a, car& b)->bool{
    //     return a.num < b.num;
    // });

    for(auto x : cars){
        cout << x->rides.size() << " ";
        for(auto y : x->rides){
            cout << y << " ";
        }
        cout << endl;
    }


}