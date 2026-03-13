#include "raylib.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;

struct Edge {
    string destination;
    int distance;
    double trafficFactor;

    double getWeight() const {
        return distance * trafficFactor;
    }
};

struct NodeDisplay {
    string name;
    Vector2 pos;
};

class NavigationSystem {

public:

    unordered_map<string, vector<Edge>> graph;
    unordered_map<string, NodeDisplay> nodes;

    void addNode(string name, Vector2 pos) {
        nodes[name] = {name, pos};
    }

    void addRoute(string src, string dest, int dist) {

        graph[src].push_back({dest, dist, 1});
        graph[dest].push_back({src, dist, 1});
    }

    vector<string> findPath(string start, string end) {

        unordered_map<string,double> dist;
        unordered_map<string,string> parent;

        for(auto &[n,_]:nodes)
            dist[n] = 1e18;

        priority_queue<
            pair<double,string>,
            vector<pair<double,string>>,
            greater<>
        > pq;

        dist[start] = 0;
        pq.push({0,start});

        while(!pq.empty()){

            auto cur = pq.top().second;
            pq.pop();

            if(cur==end) break;

            for(auto &e: graph[cur]){

                double nd = dist[cur] + e.getWeight();

                if(nd < dist[e.destination]){

                    dist[e.destination] = nd;
                    parent[e.destination] = cur;

                    pq.push({nd,e.destination});
                }
            }
        }

        vector<string> path;

        if(dist[end]==1e18) return path;

        for(string v=end; v!=start; v=parent[v])
            path.push_back(v);

        path.push_back(start);

        reverse(path.begin(),path.end());

        return path;
    }
};

int main(){

    InitWindow(1200,750,"Big Map Dijkstra");

    SetTargetFPS(60);

    NavigationSystem nav;

    // ---------- NODES (15) ----------

    nav.addNode("A",{100,600});
    nav.addNode("B",{250,650});
    nav.addNode("C",{400,620});
    nav.addNode("D",{550,650});
    nav.addNode("E",{700,600});

    nav.addNode("F",{150,450});
    nav.addNode("G",{300,450});
    nav.addNode("H",{450,450});
    nav.addNode("I",{600,450});
    nav.addNode("J",{750,450});

    nav.addNode("K",{200,250});
    nav.addNode("L",{350,250});
    nav.addNode("M",{500,250});
    nav.addNode("N",{650,250});
    nav.addNode("O",{800,250});

    // ---------- ROUTES ----------

    nav.addRoute("A","B",4);
    nav.addRoute("B","C",3);
    nav.addRoute("C","D",6);
    nav.addRoute("D","E",5);

    nav.addRoute("A","F",7);
    nav.addRoute("B","G",2);
    nav.addRoute("C","H",4);
    nav.addRoute("D","I",3);
    nav.addRoute("E","J",6);

    nav.addRoute("F","G",3);
    nav.addRoute("G","H",2);
    nav.addRoute("H","I",2);
    nav.addRoute("I","J",3);

    nav.addRoute("F","K",5);
    nav.addRoute("G","L",3);
    nav.addRoute("H","M",4);
    nav.addRoute("I","N",2);
    nav.addRoute("J","O",5);

    nav.addRoute("K","L",2);
    nav.addRoute("L","M",2);
    nav.addRoute("M","N",3);
    nav.addRoute("N","O",4);

    string startNode="A";
    string endNode="O";

    vector<string> path = nav.findPath(startNode,endNode);

    Vector2 carPos = nav.nodes[startNode].pos;

    int pathIndex=0;
    float speed=2;

    while(!WindowShouldClose()){

        Vector2 mp = GetMousePosition();

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){

            for(auto &[name,node]:nav.nodes){

                if(CheckCollisionPointCircle(mp,node.pos,20)){

                    endNode=name;

                    path = nav.findPath(startNode,endNode);

                    carPos=nav.nodes[startNode].pos;

                    pathIndex=0;
                }
            }
        }

        if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){

            for(auto &[name,node]:nav.nodes){

                if(CheckCollisionPointCircle(mp,node.pos,20)){

                    startNode=name;

                    path = nav.findPath(startNode,endNode);

                    carPos=nav.nodes[startNode].pos;

                    pathIndex=0;
                }
            }
        }

        // car move

        if(path.size()>1 && pathIndex < path.size()-1){

            Vector2 target =
            nav.nodes[path[pathIndex+1]].pos;

            Vector2 dir = {
                target.x - carPos.x,
                target.y - carPos.y
            };

            float len = sqrt(dir.x*dir.x+dir.y*dir.y);

            if(len < speed){

                carPos = target;
                pathIndex++;
            }
            else{

                carPos.x += speed*dir.x/len;
                carPos.y += speed*dir.y/len;
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        // roads

        for(auto &[src,edges]:nav.graph)
            for(auto &e:edges)
                DrawLineEx(
                    nav.nodes[src].pos,
                    nav.nodes[e.destination].pos,
                    2,
                    GRAY
                );

        // path

        for(int i=0;i+1<path.size();i++)
            DrawLineEx(
                nav.nodes[path[i]].pos,
                nav.nodes[path[i+1]].pos,
                6,
                ORANGE
            );

        // nodes

        for(auto &[name,node]:nav.nodes){

            Color c=SKYBLUE;

            if(name==startNode) c=GREEN;
            if(name==endNode) c=RED;

            DrawCircleV(node.pos,18,c);

            DrawText(
                name.c_str(),
                node.pos.x-5,
                node.pos.y+20,
                16,
                WHITE
            );
        }

        DrawCircleV(carPos,8,YELLOW);

        DrawText(
        "Left click = destination | Right click = start",
        20,20,20,YELLOW);

        EndDrawing();
    }

    CloseWindow();
}