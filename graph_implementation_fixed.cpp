#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

class GraphMatrix{
    public:
        GraphMatrix(ifstream& graph, ofstream& outputFile) : output(outputFile) {
            string temp;
            string firstline;
            getline(graph, firstline);
            istringstream iss(firstline);
            iss >> this->lenght;
            matrix.resize(this->lenght, vector<bool>(this->lenght, 0));
            
            while (getline(graph, temp)){
                int i, j;
                istringstream iss(temp);
                iss >> i >> j;
                matrix[i - 1][j - 1] = 1;
                matrix[j - 1][i - 1] = 1;
            }
        }

        void degree(){
            auto start = chrono::steady_clock::now();
            int dmax = 0;
            int dmin = 0;
            float partsum = 0;
            float dmedium = 0;
            vector<int> medlist;
            int med;

            for (int i = 0; i < this->lenght; i++){
                float degree = 0;
                for (int j = 0; j < this->lenght; j++){
                    if (this->matrix[i][j] == 1){
                        degree++;
                    }
                }

                if (degree > dmax){
                    dmax = degree;
                }

                if (i == 0){
                    dmin = degree;
                }
                else{
                    if (degree < dmin){
                        dmin = degree;
                    }
                }

                partsum += degree;
                medlist.push_back(degree);
            }

            dmedium = (partsum * 1.0) / this->lenght;
            sort(medlist.begin(), medlist.end());

            if(this->lenght % 2 == 1){
                med = medlist[this->lenght/2];
            }
            else{
                med = (medlist[this->lenght / 2] + medlist[(this->lenght / 2) - 1]) / 2;
            }

            auto time = chrono::steady_clock::now() - start;
            output << "Grau Maximo: " << dmax << endl;
            output << "Grau Minimo: " << dmin << endl;
            output << "Grau Medio: " << dmedium << endl;
            output << "Mediana do Grau: " << med << endl;
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }

        void BFS(int vertex){
            auto start = chrono::steady_clock::now();
            vector<int> marksdistance(this->lenght, -1);
            vector<int> tree(this->lenght, -1);
            queue<int> vertexqueue;

            marksdistance[vertex - 1] = 0;
            tree[vertex - 1] = 0;
            vertexqueue.push(vertex - 1);

            while (vertexqueue.empty() == false){
                int actual = vertexqueue.front();
                vertexqueue.pop();

                for (int i = 0; i < this->lenght; i++){
                    if (this->matrix[actual][i] != 0){
                        if (marksdistance[i] == -1){
                            marksdistance[i] = marksdistance[actual] + 1;
                            tree[i] = actual + 1;
                            vertexqueue.push(i);
                        }
                    }
                }
            }

            auto time = chrono::steady_clock::now() - start;
            output << "[";
            for(int i = 0; i < this->lenght; i++){
                output << "(" << i + 1 << ": " << marksdistance[i] << ", " << tree[i] << "), ";
            }
            output << "]" << endl;
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }

        void DFS(int vertex){
            auto start = chrono::steady_clock::now();
            vector<int> marksdistance(this->lenght, -1);
            vector<int> tree(this->lenght, -1);
            stack<int> vertexstack;

            marksdistance[vertex - 1] = 0;
            tree[vertex - 1] = 0;
            vertexstack.push(vertex - 1);

            while (vertexstack.empty() == false){
                int actual = vertexstack.top();
                vertexstack.pop();

                for (int i = 0; i < this->lenght; i++){
                    if (this->matrix[actual][i] != 0){
                        if (marksdistance[i] == -1){
                            marksdistance[i] = marksdistance[actual] + 1;
                            tree[i] = actual + 1;
                            vertexstack.push(i);
                        }
                    }
                }
            }

            auto time = chrono::steady_clock::now() - start;
            output << "[";
            for(int i = 0; i < this->lenght; i++){
                output << "(" << i + 1 << ": " << marksdistance[i] << ", " << tree[i] << "), ";
            }
            output << "]" << endl;
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }

        void distance(int vertex, int target){
            auto start = chrono::steady_clock::now();
            int d = -1;
            vector<int> marksdistance(this->lenght, -1);
            queue<int> vertexqueue;

            marksdistance[vertex - 1] = 0;
            vertexqueue.push(vertex - 1);
            bool find = false;

            if (target == vertex){
                d = 0;
            }
            else{
                while (vertexqueue.empty() == false && find == false){
                    int actual = vertexqueue.front();
                    vertexqueue.pop();

                    for (int i = 0; i < this->lenght; i++){
                        if (this->matrix[actual][i] != 0){
                            if (marksdistance[i] == -1){
                                marksdistance[i] = marksdistance[actual] + 1;
                                if (i == target - 1){
                                    d = marksdistance[i];
                                    find = true;
                                }
                                vertexqueue.push(i);
                            }
                        }
                    }
                }
            }

            auto time = chrono::steady_clock::now() - start;
            output << d << endl;
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }  

        void diameter(){
            auto start = chrono::steady_clock::now();
            int diameter = 0;

            for(int i = 0; i < this->lenght; i++){
                int vertex = i;
                vector<int> marksdistance(this->lenght, -1);
                int maxdistance = 0;
                queue<int> vertexqueue;

                marksdistance[vertex] = 0;
                vertexqueue.push(vertex);

                while (vertexqueue.empty() == false){
                    int actual = vertexqueue.front();
                    vertexqueue.pop();

                    for (int j = 0; j < this->lenght; j++){
                        if (this->matrix[actual][j] != 0){
                            if (marksdistance[j] == -1){
                                marksdistance[j] = marksdistance[actual] + 1;
                                if (marksdistance[j] > maxdistance){
                                    maxdistance = marksdistance[j];
                                }
                                vertexqueue.push(j);
                            }
                        }
                    }
                }

                if (maxdistance > diameter){
                    diameter = maxdistance;
                }
            }  

            auto time = chrono::steady_clock::now() - start;
            output << diameter << endl;
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }

        void fastdiameter(){
            auto start = chrono::steady_clock::now();
            int d;
            pair<int,int> max1 = {0, 0};
            vector<int> marksdistance(this->lenght, -1);
            queue<int> vertexqueue;

            marksdistance[0] = 0;
            vertexqueue.push(0);

            while (vertexqueue.empty() == false){
                int actual = vertexqueue.front();
                vertexqueue.pop();

                for (int i = 0; i < this->lenght; i++){
                    if (this->matrix[actual][i] != 0){
                        if (marksdistance[i] == -1){
                            marksdistance[i] = marksdistance[actual] + 1;
                            vertexqueue.push(i);
                            if(marksdistance[i] > max1.second){
                                max1 = {i, marksdistance[i]};
                            }
                        }
                    }
                }
            }

            vector<int> marksdistance2(this->lenght, -1);
            queue<int> vertexqueue2;
            int max2 = 0;

            marksdistance2[max1.first] = 0;
            vertexqueue2.push(max1.first);

            while (vertexqueue2.empty() == false){
                int actual = vertexqueue2.front();
                vertexqueue2.pop();

                for (int i = 0; i < this->lenght; i++){
                    if (this->matrix[actual][i] != 0){
                        if (marksdistance2[i] == -1){
                            marksdistance2[i] = marksdistance2[actual] + 1;
                            vertexqueue2.push(i);
                            if(marksdistance2[i] > max2){
                                max2 = marksdistance2[i];
                            }
                        }
                    }
                }
            }

            d = max2;

            auto time = chrono::steady_clock::now() - start;
            output << d << endl;
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }  

        void CC(){
            auto start = chrono::steady_clock::now();
            vector<int> marks(this->lenght, 0);
            vector<pair<int, int>> component;
            int n = 1;

            for(int i = 0; i < this->lenght; i++){
                if (marks[i] == 0){
                    int CClenght = 1;
                    queue<int> vertexqueue;
                    marks[i] = n;
                    vertexqueue.push(i);

                    while (vertexqueue.empty() == false){
                        int actual = vertexqueue.front();
                        vertexqueue.pop();

                        for (int j = 0; j < this->lenght; j++){
                            if (this->matrix[actual][j] != 0){
                                if (marks[j] == 0){
                                    marks[j] = n;
                                    CClenght++;
                                    vertexqueue.push(j);
                                }
                            }
                        }
                    }

                    pair<int, int> x = {CClenght, n};
                    component.push_back(x);
                    n++;
                }
            }

            sort(component.rbegin(), component.rend());

            auto time = chrono::steady_clock::now() - start;
            for(int i = 0; i < component.size(); i++){
                output << "Componente de Tamanho " << component[i].first << ":" << "[";
                for(int j = 0; j < this->lenght; j++){
                    if(marks[j] == component[i].second){
                        output << j + 1 << ", ";
                    }
                }
                output << "]" << endl;
            }
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }

    private:
        int lenght;
        vector<vector<bool>> matrix;
        ofstream& output;
};

class GraphList{
    public:
        GraphList(ifstream& graph, ofstream& outputFile) : output(outputFile) {
            string temp;
            string firstline;
            getline(graph, firstline);
            istringstream iss(firstline);
            iss >> this->lenght;
            this->list.resize(this->lenght);

            while (getline(graph, temp)){
                int i, j;
                istringstream iss(temp);
                iss >> i >> j;
                this->list[i - 1].push_front(j - 1);
                this->list[j - 1].push_front(i - 1);
            }

            for(int i = 0; i < this->lenght; i++){
                this->list[i].sort();
            }
        }

        void degree(){
            auto start = chrono::steady_clock::now();
            int dmax = 0;
            int dmin = 0;
            int partsum = 0;
            float dmed = 0;
            int med;
            vector<int> medlist;

            for(int i = 0; i < this->lenght; i++){
                int degree = 0;
                for(int j : this->list[i]){
                    degree++;
                }

                if(i == 0){
                    dmin = degree;
                }
                if(degree > dmax){
                    dmax = degree;
                }
                if(degree < dmin){
                    dmin = degree;
                }

                partsum += degree;
                medlist.push_back(degree);
            }

            dmed = (1.0 * partsum) / this->lenght;
            sort(medlist.begin(), medlist.end());

            if(this->lenght % 2 == 1){
                med = medlist[this->lenght/2];
            }
            else{
                med = (medlist[this->lenght / 2] + medlist[(this->lenght / 2) - 1]) / 2;
            }

            auto time = chrono::steady_clock::now() - start;
            output << "Grau Maximo: " << dmax << endl;
            output << "Grau Minimo: " << dmin << endl;
            output << "Grau Medio: " << dmed << endl;
            output << "Mediana do Grau: " << med << endl;
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }

        void BFS(int vertex){
            auto start = chrono::steady_clock::now();
            vector<int> marksdistance(this->lenght, -1);
            vector<int> tree(this->lenght, -1);
            queue<int> vertexqueue;

            marksdistance[vertex - 1] = 0;
            tree[vertex - 1] = 0;
            vertexqueue.push(vertex - 1);

            while(vertexqueue.empty() != true){
                int actual = vertexqueue.front();
                vertexqueue.pop();

                for(auto i = this->list[actual].begin(); i != this->list[actual].end(); i++){
                    if(marksdistance[*i] == -1){
                        marksdistance[*i] = marksdistance[actual] + 1;
                        tree[*i] = actual + 1;
                        vertexqueue.push(*i);
                    }
                }
            }

            auto time = chrono::steady_clock::now() - start;
            output << "[";
            for(int i = 0; i < this->lenght; i++){
                output << "(" << i + 1 << ": " << marksdistance[i] << ", " << tree[i] << "), ";
            }
            output << "]" << endl;
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }

        void DFS(int vertex){
            auto start = chrono::steady_clock::now();
            vector<int> marksdistance(this->lenght, -1);
            vector<int> tree(this->lenght, -1);
            stack<int> vertexstack;

            marksdistance[vertex - 1] = 0;
            tree[vertex - 1] = 0;
            vertexstack.push(vertex - 1);

            while(vertexstack.empty() != true){
                int actual = vertexstack.top();
                vertexstack.pop();

                for(auto i = this->list[actual].begin(); i != this->list[actual].end(); i++){
                    if(marksdistance[*i] == -1){
                        marksdistance[*i] = marksdistance[actual] + 1;
                        tree[*i] = actual + 1;
                        vertexstack.push(*i);
                    }
                }
            }

            auto time = chrono::steady_clock::now() - start;
            output << "[";
            for(int i = 0; i < this->lenght; i++){
                output << "(" << i + 1 << ": " << marksdistance[i] << ", " << tree[i] << "), ";
            }
            output << "]" << endl;
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }

        void distance(int vertex, int target){
            auto start = chrono::steady_clock::now();
            vector<int> marksdistance(this->lenght, -1);
            queue<int> vertexqueue;
            int d = -1;
            bool find = false;

            marksdistance[vertex - 1] = 0;
            vertexqueue.push(vertex - 1);

            if(vertex == target){
                d = 0;
            }
            else{
                while(vertexqueue.empty() != true && find == false){
                    int actual = vertexqueue.front();
                    vertexqueue.pop();

                    for(auto i = this->list[actual].begin(); i != this->list[actual].end(); i++){
                        if(marksdistance[*i] == -1){
                            marksdistance[*i] = marksdistance[actual] + 1;
                            vertexqueue.push(*i);
                            if(*i == target - 1){
                                d = marksdistance[*i];
                                find = true;
                                break;
                            }
                        }
                    }
                }
            }

            auto time = chrono::steady_clock::now() - start;
            output << d << endl;
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }

        void diameter(){
            auto start = chrono::steady_clock::now();
            int d = 0;

            for(int i = 0; i < this->lenght; i++){
                vector<int> marksdistance(this->lenght, -1);
                queue<int> vertexqueue;
                marksdistance[i] = 0;
                vertexqueue.push(i);
                int maxdistance = 0;

                while(vertexqueue.empty() != true){
                    int actual = vertexqueue.front();
                    vertexqueue.pop();

                    for(auto j = this->list[actual].begin(); j != this->list[actual].end(); j++){
                        if(marksdistance[*j] == -1){
                            marksdistance[*j] = marksdistance[actual] + 1;
                            if(maxdistance < marksdistance[*j]){
                                maxdistance = marksdistance[*j];
                            }
                            vertexqueue.push(*j);
                        }
                    }
                }

                if(maxdistance > d){
                    d = maxdistance;
                }
            }

            auto time = chrono::steady_clock::now() - start;
            output << d << endl;
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }

        void fastdiameter(){
            auto start = chrono::steady_clock::now();
            vector<int> marksdistance(this->lenght, -1);
            queue<int> vertexqueue;
            int d;
            pair<int, int> max1 = {0, 0};

            marksdistance[0] = 0;
            vertexqueue.push(0);

            while(vertexqueue.empty() != true){
                int actual = vertexqueue.front();
                vertexqueue.pop();

                for(auto i = this->list[actual].begin(); i != this->list[actual].end(); i++){
                    if(marksdistance[*i] == -1){
                        marksdistance[*i] = marksdistance[actual] + 1;
                        if(marksdistance[*i] > max1.second){
                            max1 = {*i, marksdistance[*i]};
                        }
                        vertexqueue.push(*i);
                    }
                }
            }

            // Second BFS from the farthest vertex found
            vector<int> marksdistance2(this->lenght, -1);
            queue<int> vertexqueue2;
            int max2 = 0;

            marksdistance2[max1.first] = 0;
            vertexqueue2.push(max1.first);

            while(vertexqueue2.empty() != true){
                int actual = vertexqueue2.front();
                vertexqueue2.pop();

                for(auto i = this->list[actual].begin(); i != this->list[actual].end(); i++){
                    if(marksdistance2[*i] == -1){
                        marksdistance2[*i] = marksdistance2[actual] + 1;
                        if(marksdistance2[*i] > max2){
                            max2 = marksdistance2[*i];
                        }
                        vertexqueue2.push(*i);
                    }
                }
            }

            d = max2;

            auto time = chrono::steady_clock::now() - start;
            output << d << endl;
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }

        void CC(){
            auto start = chrono::steady_clock::now();
            vector<int> marks(this->lenght, 0);
            vector<pair<int,int>> component;
            int n = 1;

            for(int i = 0; i < this->lenght; i++){
                if(marks[i] == 0){
                    int CClenght = 1;
                    queue<int> vertexqueue;
                    marks[i] = n;
                    vertexqueue.push(i);

                    while(vertexqueue.empty() != true){
                        int actual = vertexqueue.front();
                        vertexqueue.pop();

                        for(auto j = this->list[actual].begin(); j != this->list[actual].end(); j++){
                            if(marks[*j] == 0){
                                marks[*j] = n;  // Fixed: was marks[actual], should be n
                                CClenght++;
                                vertexqueue.push(*j);
                            }
                        }
                    }

                    pair<int, int> x = {CClenght, n};
                    component.push_back(x);
                    n++;
                }
            }

            sort(component.rbegin(), component.rend());

            auto time = chrono::steady_clock::now() - start;
            for(int i = 0; i < component.size(); i++){
                output << "Componente de Tamanho " << component[i].first << ":" << "[";
                for(int j = 0; j < this->lenght; j++){
                    if(marks[j] == component[i].second){
                        output << j + 1 << ", ";
                    }
                }
                output << "]" << endl;
            }
            output << "Tempo de Execução: "<< chrono::duration_cast<chrono::milliseconds>(time).count() << "ms" << endl;
        }

    private:
        int lenght;
        vector<forward_list<int>> list;
        ofstream& output;
};

int main(){
    ifstream graph;
    graph.open("grafo_1.txt");
    ofstream matrixoutput("matrixoutput.txt");
    GraphMatrix matrix(graph, matrixoutput);
    graph.close();
    //matrix.degree();
    //matrix.BFS(6);
    //matrix.DFS(6);
    //matrix.distance(6, 122);
    //matrix.CC();
    matrixoutput.close();

    graph.open("grafo_2.txt");
    ofstream listoutput("listoutput.txt");
    GraphList list(graph, listoutput);
    //list.degree();
    //list.BFS(2);
    list.DFS(2);
    //list.distance(6,12);
    //list.diameter();
    //list.CC();
    graph.close();
    listoutput.close();

    return 0;
}
