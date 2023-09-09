#include <bits/stdc++.h>
using namespace std;
#include <chrono>



vector<int> A(15), C(15), T(15), G(15);
vector<vector<int>> kCount;
vector<string> data;
vector<vector<int>> dis;
vector<int> cum_hamming(4,0);
vector<char> res(15);
int epsilon=100;
char decode(int i){
    switch(i){
        case 0:
            return 'A';
        case 1:
            return 'C';
        case 2:
            return 'T';
        case 3:
            return 'G';
    }
}
void setDistance(){
    for(int i=0; i<cum_hamming.size(); i++){
        vector<int> aux(4, cum_hamming[i]);
        dis[i]=aux;
    }
}

void count(int pos, string s, int cont){
     switch(s[pos]){
            case 'A':
                dis[cont][1]++;
                dis[cont][2]++;
                dis[cont][3]++;
                break;
            case 'C':
                dis[cont][0]++;
                dis[cont][2]++;
                dis[cont][3]++;
                break;
            case 'T':
                dis[cont][1]++;
                dis[cont][0]++;
                dis[cont][3]++;
                break;
            case 'G':
                dis[cont][0]++;
                dis[cont][2]++;
                dis[cont][1]++;
                break;
    }
    
}
int greedy(){
    int min=INT_MAX; 
    int mini;
    for(int i=0; i<4;i++){
        int sum=0;
        for(int j = 0; j<dis.size();j++){
            sum += dis[j][i] *dis[j][i];
        }
        if(sum<min){
            min = sum;
            mini = i;
        }else if(sum == min){
            if(rand()%2>0){
                min = sum;
                mini = i;
            }
        }
    }
    return mini;
}
void updateCum(int pos){
    for(int i =0; i<cum_hamming.size();i++){
        cum_hamming[i]=dis[i][pos];
    }
}

// void count(string s){
//     for(int i=0; i<15; i++){
//         switch(s[i]){
//             case 'A':
//                 A[i]++;
//                 break;
//             case 'C':
//                 C[i]++;
//                 break;
//             case 'G':
//                 G[i]++;
//                 break;
//             case 'T':
//                 T[i]++;
//                 break;
//         }

//     }
// }
void print2(){
    //cout<<"Priting greedy" <<endl;
    for(int i=0;i<cum_hamming.size();i++){
        cout<<cum_hamming[i]<<" ";
    }cout<<endl;

}
void print3(){
    //cout<<"Priting respuesta" <<endl;
    for(int i=0;i<15;i++){
        cout<<res[i]<<" ";
    }cout<<endl;

}
void print(){
    for(int i=0; i<cum_hamming.size(); i++ ){
        cout<<"imprimiendo "<< i<<endl;
        for(int j=0;j<4; j++){
            cout<<dis[i][j]<<" ";
        }
        cout<<endl;
    }
}
int calcCost(){
    int cost=0;
    for(int i=0;i<cum_hamming.size();i++){
        cost+= cum_hamming[i]*cum_hamming[i];
    }
    return cost;
}
main(int argc, char *argv[]){
    int i=1;
    // while(i<argc){
    //     cout<<"argumento: " <<i<<" "<<argv[i]<<endl;
    //     i++;
    // }
    
    std::string filename, line;
    filename = "t2.txt";
    std::ifstream newFile(filename);
    
    if (newFile.is_open()) {
        while (newFile.peek() != EOF) {
                //cout<<"------------------------------------"<<endl;
                getline(newFile, line);
                data.push_back(line);
        }
        
        //print();
    newFile.close();
    }else{
        cout<<"non"<<endl;
    }
    auto start = std::chrono::system_clock::now();
    
    cum_hamming.resize(data.size()-1, 0);
    dis.resize(data.size()-1);
    for(int i=0; i<15; i++){
            int cont=0;
            setDistance();
            //print();
            for(int j=0; j<data.size()-1;j++) {
                //cout<<"------------------------------------"<<endl;
                //cout<<"entra"<<endl;
                getline(newFile, line);
                count(i,data[j],cont);
                cont++;
                //cout<<"Hace el count :>"<<endl;
            
            }
            //print();
            int aux = greedy();
            //cout<<"Hace el greedy :>"<<endl;
            res[i]=decode(aux);
            //cout<<"Hace la asignacion :>"<<endl;
            updateCum(aux);
            //print2();
            
            //cout<<"Hace el cum :>"<<endl;
            
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> time = end-start;
        print3();
        cout<<"con costo: "<<calcCost()<<endl;
        std::cout << "elapsed time: " << time.count() << "s\n";
        
    // kCount.push_back(A);
    // kCount.push_back(C);
    // kCount.push_back(T);
    // kCount.push_back(G);
    // string argv1 = argv[1];
    //print2();
    // if(argv1 == "greedy"){
    //     cout<<"resolviendo con greedy deterministico"<<endl;
    //     greedy();
    //     print2();
    // }else if(argv1== "greedy-p"){
    //     string argv3 = argv[3];
    //     if(argv3.size()){
    //         epsilon=stoi(argv3);
    //     }
    //     eGreedy();
    //     cout<<"resolviendo con greedy aleatorizado y epsilon = "<<epsilon<<endl;
    //     print2();
    // }

    //print2();
}