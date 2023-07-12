#include <iostream>
#include <cmath>
#include <vector>
#include<limits>
#include <utility>
#include <iomanip>

// Node: Đơn vị nhỏ nhất trong map
// CurrentNode: Node hiện tại đang được khám phá
// ChildNodes: Các Node có thể đi tới từ CurrentNode
//parentNode: Node mà từ node này có thể đi tới các childnodes
// VisitedNode: Node đã được khám phá.
// Q: Tập hợp các ChildNodes chưa được khám phá

struct Node  // Định nghĩa kiểu dữ liệu Node
{

public:
    int x, y;  // Tọa độ
    float G_cost; // Khoảng cách từ CurrentNode tới StartNode được tính thông qua các parentNode
    float H_cost; // Khoảng cách từ node được khởi tạo tới FinalNode
    float J_cost; // = G_cost + H_cost
    Node *parent; // parent node
    bool check_childNode = 0;
    bool check_visited = 0;

    Node(){}
};

float update_G_cost(Node& A, Node& B)
{
    int x = A.x;
    int x1 =B.x;
    int y = A.y;
    int y1= B.y;
    float G = A.G_cost + sqrt(pow((x - x1), 2) + pow((y - y1), 2));
    return G;
}

float calculate_H_cost(Node &A, Node &Final){
    int hx = A.x;
    int hy = A.y;
    int x1 = Final.x;
    int y1 = Final.y;
    float H;
    H = sqrt(pow((hx - x1), 2) + pow((hy - y1), 2));
    return H;
}

float calculate_J_cost(Node &A){
    float J = A.H_cost + A.G_cost;
    return J;
}

class Map
{
    public:
    int Map_x; 
    int Map_y;
    Node *point;
    Node *StartNode;
    Node *FinalNode;
    std::vector<Node*> Obs; // vector chứa các node là vật cản
    Map(int x, int y) : Map_x(x),Map_y(y){ 
        point = new Node[Map_x*Map_y];    // Khởi tạo Map là 1 array kiểu dữ liệu Node
        for(int iy = 0; iy<Map_y; iy++){  // Khởi tạo tọa độ x,y cho node
            for(int ix = 0; ix<Map_x; ix++){
                point[iy*Map_x +ix].x = ix;
                point[iy*Map_x + ix].y = iy; 
            }
        }
        for(int i = 0; i<Map_x*Map_y; i++){ // Khởi tạo G_cost cho tất cả các node ở thời điểm đầu = infinity
            point[i].G_cost = std::numeric_limits<float>::infinity();
        }
    }

};

std::vector<std::pair<int,int>> A_star(Map World_Map){
    
    Node* CurrentNode;
    World_Map.StartNode->G_cost = 0;
    CurrentNode = World_Map.StartNode;
    std::vector<Node*> Visited; // queue to store all nodes have been visited
    Visited.push_back(World_Map.StartNode);
    World_Map.StartNode->check_visited = 1;
    std::vector<Node*> Q; // queue to store all nodes have been taken into consideration
    while (CurrentNode != World_Map.FinalNode)
    {
        std::vector<Node*> ChildNodes;
        if(CurrentNode->x-1 >=0 && CurrentNode->y+1 >=0 && CurrentNode->x-1 <World_Map.Map_x && CurrentNode->y+1 <World_Map.Map_y){
            Node *ChildNode_1 = &World_Map.point[(CurrentNode->y + 1)*World_Map.Map_x + CurrentNode->x - 1];
            ChildNodes.push_back(ChildNode_1);
        }
        if(CurrentNode->x >=0 && CurrentNode->y+1 >=0 && CurrentNode->x <World_Map.Map_x && CurrentNode->y+1 <World_Map.Map_y){
            Node *ChildNode_2 = &World_Map.point[(CurrentNode->y + 1)*World_Map.Map_x + CurrentNode->x];
            ChildNodes.push_back(ChildNode_2);
        }
        if(CurrentNode->x+1>=0 && CurrentNode->y+1>=0 && CurrentNode->x+1 <World_Map.Map_x && CurrentNode->y+1 <World_Map.Map_y){
            Node *ChildNode_3 = &World_Map.point[(CurrentNode->y + 1)*World_Map.Map_x + CurrentNode->x + 1];
            ChildNodes.push_back(ChildNode_3);
        }
        if(CurrentNode->x+1>=0 && CurrentNode->y>=0 && CurrentNode->x+1 <World_Map.Map_x && CurrentNode->y <World_Map.Map_y){
            Node *ChildNode_4 = &World_Map.point[(CurrentNode->y)*World_Map.Map_x + CurrentNode->x + 1];
            ChildNodes.push_back(ChildNode_4);
        }
        if(CurrentNode->x+1>=0 && CurrentNode->y-1>=0 && CurrentNode->x+1 <World_Map.Map_x && CurrentNode->y-1 <World_Map.Map_y){
            Node *ChildNode_5 = &World_Map.point[(CurrentNode->y - 1)*World_Map.Map_x + CurrentNode->x + 1];
            ChildNodes.push_back(ChildNode_5);
        }
        if(CurrentNode->x>=0 && CurrentNode->y-1>=0 && CurrentNode->x<World_Map.Map_x && CurrentNode->y-1 <World_Map.Map_y){
            Node *ChildNode_6 = &World_Map.point[(CurrentNode->y - 1)*World_Map.Map_x + CurrentNode->x];
            ChildNodes.push_back(ChildNode_6);
        }
        if(CurrentNode->x-1>=0 && CurrentNode->y-1>=0 && CurrentNode->x-1 <World_Map.Map_x && CurrentNode->y-1 <World_Map.Map_y){
            Node *ChildNode_7 = &World_Map.point[(CurrentNode->y - 1)*World_Map.Map_x + CurrentNode->x-1];
            ChildNodes.push_back(ChildNode_7);
        }
        if(CurrentNode->x-1>=0 && CurrentNode->y>=0 && CurrentNode->x-1 <World_Map.Map_x && CurrentNode->y<World_Map.Map_y){
            Node *ChildNode_8 = &World_Map.point[(CurrentNode->y)*World_Map.Map_x + CurrentNode->x-1];
            ChildNodes.push_back(ChildNode_8);
        }
        // update parent node and G_cost of ChildNode
        for(int i=0; i<ChildNodes.size(); i++){
            float Temp_G = update_G_cost(*CurrentNode, *ChildNodes[i]);
            if(Temp_G < ChildNodes[i]->G_cost){
                ChildNodes[i]->G_cost = Temp_G;
                ChildNodes[i]->parent = CurrentNode;
            }
        }
        // Store childnodes into Q queue
        for(int i=0; i<Q.size(); i++){
            for(int j=0; j<ChildNodes.size(); j++){
                if(ChildNodes[j]==Q[i]){
                    ChildNodes[j]->check_childNode = 1;
                    break;
                }
            }
        }
        for(int i=0; i<ChildNodes.size(); i++){
            if(ChildNodes[i]-> check_childNode !=1){
                Q.push_back(ChildNodes[i]);
            }
        }
        // Find the node has the lowest J cost in Q queue and assign it as current node
        Node* Q_min;
        Q_min = Q[0];
        for(int i=0; i<Q.size(); i++){
            Q[i]->H_cost = calculate_H_cost(*Q[i], *World_Map.FinalNode);
            Q[i]->J_cost =calculate_J_cost(*Q[i]);
        }
        for(int i=0; i<Q.size(); i++){
            for(int j=0; j<World_Map.Obs.size();j++){
                if(Q[i]==World_Map.Obs[j]){
                    Q[i]->J_cost = std::numeric_limits<float>::infinity();
                    break;
                }
            }
        }
        for(int i=0; i<Q.size(); i++){
            if(Q[i]->check_visited != 1 && Q[i]->J_cost < Q_min->J_cost){
                Q_min = Q[i];                
            }
        }
        
        CurrentNode = Q_min;
        CurrentNode->check_visited = 1;
        for(int i=0; i<Q.size();i++){
            if(Q[i]->check_visited == 1){
                Q.erase(Q.begin()+i);
            }
        }
        Visited.push_back(CurrentNode);
    }
    for(int i=0; i<Visited.size(); i++){
        std::cout << Visited[i]->x << Visited[i]->y <<std::endl;
    }
    std::vector<std::pair<int,int>> result;
    
    std::vector<Node*> Path;
    Path.push_back(World_Map.FinalNode);
    Node *trackback;
    trackback = Visited[Visited.size()-1];

    while(trackback->parent != World_Map.StartNode){
        trackback = trackback->parent;
        Path.insert(Path.begin(),trackback);
    }
    
    for(int i=0; i<Path.size(); i++){
        result.push_back(std::make_pair(Path[i]->x, Path[i]->y));
    }
    
    return result;
    //for(int i=0; i<Path.size(); i++){
    //    std::cout << Path[i]->x <<Path[i]->y << std::endl;
    //}
}

std::pair<int,int> realWorld_to_myWorld(double long_big, double long_small, double lat_big, double lat_small, double res){
    
    double temp_x = (long_big - long_small)/res+1;
    int myWorld_x = static_cast<int>(temp_x);
    double temp_y = (lat_big - lat_small)/res;
    int myWorld_y = static_cast<int>(temp_y);
    return std::make_pair(myWorld_x, myWorld_y);
}

std::pair<double,double> myWorld_to_realWorld(int myWorld_x, int myWorld_y, double res, double lat_small, double long_small){
    double temp_x = static_cast<double>(myWorld_x);
    double realWorld_x = (temp_x-1)*res + long_small;
    double temp_y = static_cast<double>(myWorld_y);
    double realWorld_y = (temp_y-1)*res + lat_small;
    return std::make_pair(realWorld_x, realWorld_y);
}

int main(){
    
    Map mymap(5,3);
    mymap.StartNode = &mymap.point[0];
    //std::cout << mymap.point[10].x << " "<<mymap.point[10].y <<" "<<mymap.point[10].G_cost<<std::endl;
    //std::cout <<mymap.StartNode <<std::endl;
    //std::cout <<mymap.StartNode->x <<" "<<mymap.StartNode->y;
    mymap.Obs = {&mymap.point[7],&mymap.point[8], &mymap.point[12], &mymap.point[13]};
    mymap.FinalNode = &mymap.point[12];
    std::vector<std::pair<int,int>> result = A_star(mymap);
    for(int i=0; i< result.size(); i++){
        std:: cout <<result[i].first << " "<< result[i].second << std::endl;
    }
    /*
    double x2 = 20.123456;
    double x1 = 10.123456;
    double y2 = 50.123456;
    double y1 = 10;
    double res = 0.000001;
    std::pair<int,int> result = realWorld_to_myWorld(x2,x1,y2,y1,res);
    std::cout << result.first <<" "<< result.second <<std::endl;
    int myWorld_x = 10000000;
    int myWorld_y = 40123456;
    std::pair<double,double> ha = myWorld_to_realWorld(myWorld_x, myWorld_y,res,y1,x1);
    std::cout<<std::setprecision(15) << ha.first << " " << ha.second << std::endl;
    */
    
}
