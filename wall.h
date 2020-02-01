#ifndef WALL_H
#define WALL_H

class Wall{
    int cells_[2];
public:
	Wall(int c1,int c2){
		cells_[0]=c1;
		cells_[1]=c2;
	}
	Wall(){
		cells_[0]=cells_[1]=-1;
	}
	void set(int c1,int c2){
		cells_[0]=c1;
		cells_[1]=c2;
	}
	int cell1() const{return cells_[0];}
	int cell2() const{return cells_[1];}
};

#endif