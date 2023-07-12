#include<iostream>

using namespace std;

struct edge{
    //int x_min;
    int y_min;
    //int x_max;
    //int y_max;
    //float slopeInverse;
};

void sort_edge(edge my_edge[], int edge_table_size){
    edge temp;
    int i, j;
    for(i = 1; i< edge_table_size; i++){
        //temp.x_min = my_edge[i].x_min;
        temp.y_min = my_edge[i].y_min;
        //temp.x_max = my_edge[i].x_max;
        //temp.y_max = my_edge[i].y_max;
        //temp.slopeInverse = my_edge[i].slopeInverse;
        j = i - 1;

        while(temp.y_min < my_edge[j].y_min && j>=0){
            //my_edge[j+1].x_min = my_edge[j].x_min;
            //my_edge[j+1].x_max = my_edge[j].x_max;
            my_edge[j+1].y_min = my_edge[j].y_min;
            //my_edge[j+1].y_max = my_edge[j].y_max;
            j = j-1;
        }
        //my_edge[j+1].x_min = temp.x_min;
        //my_edge[j+1].x_max = temp.x_max;
        my_edge[j+1].y_min = temp.y_min;
        //my_edge[j+1].y_max = temp.y_max;

    }
}

int main(){
    edge A, B, C, D, E, F;
    A.y_min = 6;
    B.y_min = 1;
    C.y_min = 7;
    D.y_min = 4;
    E.y_min = 2;
    F.y_min = 9;
    edge my_edge[6] = {A,B,C,D,E,F};
    sort_edge(my_edge, 6);
    for(int i = 0; i<6; i++){
        cout<<my_edge[i].y_min<<endl;
    }
}