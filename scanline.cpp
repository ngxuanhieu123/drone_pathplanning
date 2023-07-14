#include<iostream>
#include<vector>

using namespace std;


struct edge{
    int xofy_min;
    int y_min;
    int xofy_max;
    int y_max;
    float slopeInverse;
    bool check = 0;
};

void sort_edge(vector<edge> &my_edge){
    edge temp;
    int i, j;
    for(i = 1; i< my_edge.size(); i++){
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
    
    for(int k=0; k < my_edge.size(); k++){
        if(my_edge[k].y_min == my_edge[k].y_max){
            my_edge.erase(my_edge.begin()+k);
        }
    }

}

std::vector<std::pair<int, int>> check_intersection(vector<edge> &sorted_edge){
    std::vector<std::pair<int,int>> spec_points;
    for(int i=0; i< sorted_edge.size(); i++){
        for(int j= i; j<sorted_edge.size(); j++){
            if(sorted_edge[i].xofy_min == sorted_edge[j].xofy_min && sorted_edge[i].y_min == sorted_edge[j].y_min){
                spec_points.push_back(std::make_pair(sorted_edge[i].xofy_min,sorted_edge[i].y_min));
            }

            if(sorted_edge[i].xofy_max == sorted_edge[j].xofy_max && sorted_edge[i].y_min == sorted_edge[j].y_max){
                spec_points.push_back(std::make_pair(sorted_edge[i].xofy_max,sorted_edge[i].y_max));
            }
        }
    }
    return spec_points;
}

void scan_fill(vector<edge> &sorted_edge, std::vector<std::pair<int,int>> &spec_points){
    vector<int> x;
    int scan;
    scan = sorted_edge[0].y_min;
    for(int i=0; i<sorted_edge.size(); i++){
        float temp_y_max = static_cast<float>(sorted_edge[i].y_max);
        float temp_y_min = static_cast<float>(sorted_edge[i].y_min);
        float temp_xofy_max = static_cast<float>(sorted_edge[i].xofy_max);
        float temp_xofy_min = static_cast<float>(sorted_edge[i].xofy_min);
        sorted_edge[i].slopeInverse = (sorted_edge[i].xofy_max-sorted_edge[i].xofy_min)/(sorted_edge[i].y_max-sorted_edge[i].y_min);
    }
    while(scan != sorted_edge[sorted_edge.size()-1].y_max){
        x.clear();

        for(int i = 0; i<sorted_edge.size(); i++){
            if(sorted_edge[i].y_max < scan && sorted_edge[i].y_min >= scan){
                int y_temp = scan;
                int x_temp = sorted_edge[i].xofy_min + sorted_edge[i].slopeInverse*(scan - sorted_edge[i].y_min);

                for(int j = 0; j<spec_points.size(); j++){
                    if(x_temp == spec_points[j].first && y_temp == spec_points[j].second){
                        x.push_back(x_temp);
                    }
                }

                x.push_back(x_temp);
            }
        }
        for(int i=0; i<x.size(); i++){
            cout << x[i]<<endl;
        }
        //cout << "het 1 line" <<endl;
        scan++;
    }
}

int main(){
    edge A, B, C, D, E, F;
    A.y_min = 12;
    A.xofy_min = 12;
    A.y_max = 18;
    A.xofy_max = 12;

    B.y_min = 18;
    B.xofy_min = 12;
    B.y_max = 22;
    B.xofy_max = 18;

    C.y_min = 12;
    C.xofy_min = 30;
    C.y_max = 18;
    C.xofy_max = 30;

    D.y_min = 12;
    D.xofy_min = 30;
    D.y_max = 22;
    D.xofy_max = 18;

    E.y_min = 12;
    E.xofy_min = 24;
    E.y_max = 18;
    E.xofy_max = 30;

    F.y_min = 12;
    F.xofy_min = 12;
    F.y_max = 12;
    F.xofy_max = 24;
    vector<edge> my_edge = {A,B,C,D,E,F};
    sort_edge(my_edge);
    
    //for(int i=0; i<my_edge.size(); i++){
    //    cout << my_edge[i].y_min <<" "<<my_edge[i].xofy_min << endl;
    //}
    std::vector<std::pair<int, int>> spec_points = check_intersection(my_edge);

    scan_fill(my_edge, spec_points);
    cout << A.slopeInverse<<endl;
}