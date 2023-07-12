#include<iostream>
#include <vector>

using namespace std;

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

struct edge{
    int xofy_min;
    int y_min;
    int xofy_max;
    int y_max;
    float slopeInverse;
    bool check = 0;
};

void sort_edge(edge my_edge[], int edge_table_size){
    edge temp;
    int i, j;
    for(i = 1; i< edge_table_size; i++){
        temp.xofy_min = my_edge[i].xofy_min;
        temp.y_min = my_edge[i].y_min;
        temp.xofy_max = my_edge[i].xofy_max;
        temp.y_max = my_edge[i].y_max;
        j = i - 1;

        while(temp.y_min < my_edge[j].y_min && j>=0){
            my_edge[j+1].xofy_min = my_edge[j].xofy_min;
            my_edge[j+1].xofy_max = my_edge[j].xofy_max;
            my_edge[j+1].y_min = my_edge[j].y_min;
            my_edge[j+1].y_max = my_edge[j].y_max;
            j = j-1;
        }

        my_edge[j+1].xofy_min = temp.xofy_min;
        my_edge[j+1].xofy_max = temp.xofy_max;
        my_edge[j+1].y_min = temp.y_min;
        my_edge[j+1].y_max = temp.y_max;

        while(temp.xofy_min < my_edge[j].xofy_min && j>=0){
            my_edge[j+1].xofy_min = my_edge[j].xofy_min;
            my_edge[j+1].xofy_max = my_edge[j].xofy_max;
            my_edge[j+1].y_min = my_edge[j].y_min;
            my_edge[j+1].y_max = my_edge[j].y_max;
            j = j-1;
        }
        my_edge[j+1].xofy_min = temp.xofy_min;
        my_edge[j+1].xofy_max = temp.xofy_max;
        my_edge[j+1].y_min = temp.y_min;
        my_edge[j+1].y_max = temp.y_max;
    }

}

void scan_fill(edge sorted_edge[], int edge_table_size){
    vector<int> y;
    vector<int> x;
    int scan;
    scan = sorted_edge[0].y_min;
    while(scan != sorted_edge[edge_table_size-1].y_max){
        for(int i = 0; i<edge_table_size; i++){

        }
        scan++;
    }
}

int main(){
    edge A, B, C, D, E, F;
    A.y_min = 12;
    A.xofy_min = 12;
    B.y_min = 18;
    B.xofy_min = 12;
    C.y_min = 12;
    C.xofy_min = 30;
    D.y_min = 12;
    D.xofy_min = 30;
    E.y_min = 12;
    E.xofy_min = 24;
    F.y_min = 12;
    F.xofy_min = 12;
    edge my_edge[6] = {A,B,C,D,E,F};
    sort_edge(my_edge, 6);
    for(int i = 0; i<6; i++){
        cout<<my_edge[i].y_min <<" "<<my_edge[i].xofy_min<<endl;
    }
}