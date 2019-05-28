#include <iostream>

using namespace std;


struct Parent{
	int row;
	int col;
	
	bool operator==(const Parent& src) const{
		return ((row == src.row) && (col == src.col));
	}

};

struct Site{			//a site in the grid
	Parent parent;      //parent of this grid
	int rank; 
	bool value;         //0 or 1
};

class Percolation{
	int n;			//grid size
    Site** system;		//main grid
	int openCounter;    //count number of disjoint sets

	bool checkBound(int i, int j){
		if (i >= n || j >= n || i < 0 || j < 0) return false;
		return true;
	}

    Parent find(int i, int j){
		int r = system[i][j].parent.row;
		int c = system[i][j].parent.col;
		if (r != i || c != j){
			system[i][j].parent = find(r, c);
		}
		return system[i][j].parent;
	}


	void Union(int x1, int y1, int x2, int y2){
		if (checkBound(x1, y1) == false || checkBound(x2, y2) == false || system[x1][y1].value == 0 || system[x2][y2].value == 0) return;
		Parent xroot = find(x1, y1);
		Parent yroot = find(x2, y2);
		if (xroot == yroot) return;	//in the same set already
        --openCounter;
        if (system[x1][y1].rank < system[x2][y2].rank) 
        system[xroot.row][xroot.col].parent = yroot;
		else if (system[x1][y1].rank > system[x2][y2].rank)
			system[yroot.row][yroot.col].parent = xroot;
		else{
			system[yroot.row][yroot.col].parent = xroot;
			system[xroot.row][xroot.col].rank++;
		}
	}

	bool checkSameRoot(int x1, int y1, int x2, int y2){
		Parent xroot = find(x1, y1);
		Parent yroot = find(x2, y2);
		return (xroot == yroot);
	}

public:

	~Percolation(){	//destructor
		for (int i = 0; i < n; ++i){
			delete[] system[i];
		}
		delete[] system;
	}

	Percolation(int n, bool** input){	//constructor
	    this->n = n;
	    openCounter = 0;
		//init dynamic 2d array nxn
		system = new Site*[n];
		for (int i = 0; i < n; ++i) system[i] = new Site[n];

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				system[i][j].parent.row = i;
				system[i][j].parent.col = j;
				system[i][j].rank = 0;
				system[i][j].value = input[i][j];
				if (input[i][j]) ++openCounter;
			}
		}

		//run the union find algo on all sites
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				if (system[i][j].value == 0) continue;
				//4 directions
                Union(i, j, i + 1, j);
                Union(i, j, i - 1, j);
                Union(i, j, i, j + 1);
                Union(i, j, i, j - 1);				
			}
		}
	}

	

	bool checkPercolate(){
		for (int i = 0; i < n; ++i){	//ith col of top
			for (int j = 0; j < n; ++j){	//jth col of bottom
				//first row and last row
				if (checkSameRoot(0, i, n - 1, j)){
				    //cout<<i<<" "<<j<<endl;
				    return true;
				}
			}
		}
		
		return false;
	}
	
	int getCounter(){
	    return openCounter;
	}
};


int main() {
    int n = 4;
	bool** input = new bool*[n];
	for (int i = 0; i < n; ++i) input[i] = new bool[n];
	
	for (int i = 0; i < n; ++i)
	    for (int j = 0; j < n; ++j) cin>>input[i][j];
	 Percolation* p = new Percolation(4,input);
	 cout<<"Percolate? "<<p->checkPercolate()<<endl;
	 cout<<"Number of sets: "<<p->getCounter()<<endl;
	 return 0;
}