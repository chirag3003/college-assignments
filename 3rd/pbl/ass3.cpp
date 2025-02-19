#include <iostream>

using namespace std;

class graph{
  int cost[10][10];
  int cities;
public:
  graph(){
    cout << "Enter No. Cities: ";
    cin >> cities;

    for(int i = 0 ; i < cities; i++){
      for(int j = 0 ; j < cities; j++){
        /*cout << "Enter Cost: ";*/
        /*cin >> cost[i][j];*/
        cost[i][j] = 999;
      }
    }
  }
  void create();
  void display();
  int prims(int start_v);
};

void graph::create(){
  char ch;
  for(int i = 0 ; i < cities; i++){
    for(int j = 0 ; j < cities; j++){
      cost[i][j] = 999;
    }
  }
}

void graph::display(){
  for(int i = 0 ; i < cities; i++){
    for(int j = 0 ; j < cities; j++){
      cout << cost[i][j] << " ";
    }
    cout << endl;
  }
}

int graph::prims(int start_v){
  int min = 999;
  int min_index = 0;
  for(int i = 0 ; i < cities; i++){
    if(cost[start_v][i] < min){
      min = cost[start_v][i];
      min_index = i;
    }
  }

}




int main()
{
    int a, b, c;
    cout << "Enter three numbers: ";
    cin >> a >> b >> c;
    cout << "The sum of three numbers is: " << a + b + c;
    return 0;
}
