/**************************************************************************/
/*                                                                        */
/*   A1 part1 tester file                                                 */
/*                                                                        */
/*   To compile: g++ disjointset.cpp a1q1tester.cpp timer.cpp -std=c++0x  */
/*                                                                        */
/*                                                                        */
/**************************************************************************/

#include "disjointset.h"
#include "timer.h"
#include <string>
#include <iostream>
#include <cstdlib>

bool test1(std::string& error);	
bool test2(std::string& error);	
bool test3(std::string& error);	
bool test4(std::string& error);	
bool test5(std::string& error);	
bool test6(std::string& error);
bool test7(std::string& error);
bool test8(std::string& error);
bool test9(std::string& error);
bool test10(std::string& error);
bool test11(std::string& error);
const int numTests=11;
typedef bool (*TestPtr)(std::string&);

int main(void){
	TestPtr runTest[numTests]={test1, test2, test3, test4, test5, 
		                       test6, test7, test8, test9, test10,
		                   	   test11};
	std::string msg;
	bool result=true;
	int numPassed=0;
	for(int i=0;result && i<numTests;i++){
		result = runTest[i](msg);
		if(!result){
			std::cout << msg << std::endl;
		}
		else{
			numPassed++;
			std::cout << "Test " << i+1 << " passed!" << std::endl;
		}
	}
	if(numPassed == numTests){
		std::cout << "Congratulations! You have passed testing for A1 part 1" << std::endl;
	}
	else{
		std::cout << "Looks like you still have some work left to do" << std::endl;
	}
}
/* test1: make 100 disjoint sets, check return value.  Call makeSet() on 
   sets that are made, ensure that return is false.
*/
bool test1(std::string& error){
	DisjointSet theSet(100);
	bool result;
	bool rc=true;
	for(int i=100;rc && i<105;i++ ){
		result=theSet.makeSet(i);
		if(result==true){
			rc=false;
			error="Error 1a: makeSet() return value error, function should have returned false";
		}
	}
	for(int i=-5;rc && i<0;i++ ){
		result=theSet.makeSet(i);
		if(result==true){
			rc=false;
			error="Error 1b: makeSet() return value error, function should have returned false";
		}
	}
	for(int i=0;rc && i<100;i++){
		result=theSet.makeSet(i);
		if(!result){
			rc=false;
			error="Error 1c: makeSet() return value error, function should have returned true";
		}
	}
	for(int i=0;rc && i<100;i++){
		result=theSet.makeSet(i);
		if(result == true){
			rc=false;
			error="Error 1d: makeSet() return value error, function should have returned false";
		}		
	}
	for(int i=100;rc && i<105;i++ ){
		result=theSet.makeSet(i);
		if(result == true){
			rc=false;
			error="Error 1e: makeSet() return value error, function should have returned false";
		}
	}
	for(int i=-5;rc && i<0;i++ ){
		result=theSet.makeSet(i);
		if(result == true){
			rc=false;
			error="Error 1f: makeSet() return value error, function should have returned false";
		}
	}
	return rc;
}

/*test2: call findSet() on sets with 1 item, it should be rep*/
bool test2(std::string& error){
	DisjointSet theSet(100);
	int result;
	bool rc=true;
	for(int i=0;rc && i<100;i++){
		theSet.makeSet(i);
		result=theSet.findSet(i);
		if(result != i){
			rc=false;
			error="Error 2: findSet() did not return the correct representative";
		}
	}
	return rc;
}

/*test3: create 100 items, merge together into pairs, check
  that their representatives are consistent*/
bool test3(std::string& error){
	DisjointSet theSet(100);
	bool result;
	int rep1;
	int rep2;
	bool rc=true;
	int reps[50][2];
	for(int i=0;i<100;i++){
		theSet.makeSet(i);
	}
	for(int i=0;rc && i<100;i+=2){
		result = theSet.unionSets(i,i+1);
		if(result != true){
			rc=false;
			error="Error 3a: unionSets() did not return the correct value, it should have returned true";
		}
	}
	for(int i=0;rc && i<50;i++){
		reps[i][0]=theSet.findSet(i*2);
		reps[i][1]=theSet.findSet(i*2 +1);
		if(reps[i][0]!=reps[i][1]){
			rc=false;
			error="Error 3b: findSet() is returning two different reps for objects in same set";			
		}
		if(rc && (reps[i][0] != i*2 && reps[i][0] !=(i*2+1))){
			rc=false;
			error="Error 3c: findSet() is returning a value that is not a member of the set";
		}
	}
	for(int i=0;rc && i<100;i+=2){
		result = theSet.unionSets(i,i+1);
		if(result != true){
			rc=false;
			error="Error 3d: unionSets() on objects that already belong to same set should return true";
		}
	}
	for(int i=0;rc && i<50;i++){
		if(reps[i][0]!=theSet.findSet(i*2) || reps[i][1]!=theSet.findSet(i*2+1)){
			rc=false;
			error="Error 3e: findSet() is not returning something different even though set was not altered";			
		}
	}

	return rc;
}

/*test 4: try to perform union sets on non-sets or invalid items*/
bool test4(std::string& error){
	DisjointSet theSet(100);
	bool result;
	bool rc=true;

	//objects 0 to 49 are valid sets, 50 to 99 are not
	for(int i=0;i<50;i++){
		theSet.makeSet(i);
	}
	for(int i=0;i<50;i++){
		result = theSet.unionSets(i,100+(rand()%100));
		if(result!= false){
			rc=false;
			error="Error 4a: unionSets() should return false if one or more of the arguments is not a valid set id";
		}

	}
	for(int i=0;i<50;i++){
		result = theSet.unionSets(100+(rand()%100),i);
		if(result!= false){
			rc=false;
			error="Error 4b: unionSets() should return false if one or more of the arguments is not a valid set id";
		}

	}
	for(int i=0;i<50;i++){
		result = theSet.unionSets(i,(-1-(rand()%100)));
		if(result!= false){
			rc=false;
			error="Error 4c: unionSets() should return false if one or more of the arguments is not a valid set id";
		}

	}
	for(int i=0;i<50;i++){
		result = theSet.unionSets((-1-(rand()%100)),i);
		if(result!= false){
			rc=false;
			error="Error 4d: unionSets() should return false if one or more of the arguments is not a valid set id";
		}
	}
	
	for(int i=0;rc && i<50;i+=2){
		int first=(-1-(rand()%100));
		int second=100+(rand()%100);
		if(rand()%2){
			result=theSet.unionSets(first,second);
		}
		else{
			result=theSet.unionSets(second,first);
		}
		if(result!=false){
			rc=false;
			error="Error 4e: unionSets() should return false if one or more of the arguments is not a valid set id";
		}

	}
	for(int i=0;rc && i<100;i++){
		result = theSet.unionSets(i,99-i);
		if(result!= false){
			rc=false;
			error="Error 4f: unionSets() should return false if one of the arguments is not a set";
		}
	}
	//try again with invalid argument as first parameter
	for(int i=0;rc && i<100;i++){
		result = theSet.unionSets(99-i,i);
		if(result!= false){
			rc=false;
			error="Error 4g: unionSets() should return false if one of the arguments is not a set";
		}
	}
	//try again with non set values as both parameters
	for(int i=50;rc && i<100;i+=2){
		result = theSet.unionSets(i,i+1);
		if(result!= false){
			rc=false;
			error="Error 4h: unionSets() should return false if one or more of the arguments is not a set";
		}
	}


	for(int i=50;rc && i<100;i++){
		result = theSet.unionSets(i,100+(rand()%100));
		if(result!= false){
			rc=false;
			error="Error 4i: unionSets() should return false if one or more of the arguments is invalid";
		}

	}
	return rc;
}


/*test 5: unionSets() on sets that are more than 1 element big*/
bool test5(std::string& error){
	DisjointSet theSet(100);
	bool result;
	int rep1;
	int rep2;
	bool rc=true;
	for(int i=0;i<100;i++){
		theSet.makeSet(i);
	}
	for(int i=0;rc && i<100;i+=2){
		result = theSet.unionSets(i,i+1);
	}
	for(int i=0;rc && i<50;i+=2){
		result=theSet.unionSets(i*2,(i+1)*2);
		if(result==false){
			rc=false;
			error="Error 5a: unionSets() returned false, it should have returned true as sets should have been unioned";
		}
		else{
			if(theSet.findSet(i*2)!=theSet.findSet((i+1)*2)){
				rc=false;
				error="Error 5b: uninonSet() should have combined the two sets and their reps should be same";
			}
		}
	}
	return rc;
}

/*Test 6: further testing on unionSets() and findSet()*/
bool test6(std::string& error){
	DisjointSet theSet(100);
	bool result;
	int rep1;
	int rep2;
	bool rc=true;
	for(int i=0;i<100;i++){
		theSet.makeSet(i);
	}
	for(int i=0;rc && i<100;i+=2){
		result = theSet.unionSets(i,i+1);
	}
	for(int i=0;rc && i<50;i+=2){		
		theSet.unionSets(i*2,(i+1)*2);
	}
	for(int i=0,j=99;rc && i<48;i+=4,j-=4){
		result=theSet.unionSets(i,j);
		if(result==false){
			rc=false;
			error="Error 6a: unionSets() returned false, it should have returned true";
		}
	}
	for(int i=0,j=99;rc && i<48;i+=4,j-=4){
		int newRep=theSet.findSet(i);
		for(int k=0;rc && k<4;k++){
			if(theSet.findSet(i+k)!=newRep){
				rc=false;
				error ="Error 6b: findSet() did not return a consistent representative";
			}
			if(theSet.findSet(j-k)!=newRep){
				rc=false;
				error="Error 6c: findSet() did not return a consistent representative";
			}
		}
	}
	result=theSet.unionSets(97,50);
	if(result == false){
		rc=false;
		error="Error 6d: unionSets() returned false, it should have returned true";
	}
	int newRep=theSet.findSet(0);
	for(int i=0;rc && i<4;i++){
		if(theSet.findSet(i)!=newRep){
			rc=false;
			error ="Error 6e: findSet() did not return a consistent representative";
		}
	}
	for(int i=0;rc && i<4;i++){
		if(theSet.findSet(99-i)!=newRep){
			rc=false;
			error ="Error 6f: findSet() did not return a consistent representative";
		}
	}
	for(int i=0;rc && i<4;i++){
		if(theSet.findSet(i+48)!=newRep){
			rc=false;
			error ="Error 6g: findSet() did not return a consistent representative";
		}
	}
	return rc;
}

/*Test 7: Test copy constructor*/
bool test7(std::string& error){
	DisjointSet theSet(100);
	bool result;
	int rep1;
	int rep2;
	bool rc=true;
	for(int i=0;i<100;i++){
		theSet.makeSet(i);
	}
	for(int i=0;rc && i<100;i+=2){
		result = theSet.unionSets(i,i+1);
	}
	for(int i=0;rc && i<50;i+=2){	
		theSet.unionSets(i*2,(i+1)*2);
	}
	for(int i=0,j=99;rc && i<48;i+=4,j-=4){
		theSet.unionSets(i,j);
	}
	DisjointSet copy=theSet;
	for(int i=0,j=99;rc && i<48;i+=4,j-=4){
		int newRep=copy.findSet(i);
		for(int k=0;rc && k<4;k++){
			if(copy.findSet(i+k)!=newRep){
				rc=false;
				error ="Error 7: Copy constructor did not produce a duplicate with same disjoint sets";
			}
			if(copy.findSet(j-k)!=newRep){
				rc=false;
				error="Error 7b: Copy constructor did not produce a duplicate with same disjoint sets";
			}
		}
	}
	result=theSet.unionSets(97,50);
	if(copy.findSet(97) == copy.findSet(50)){
		rc=false;
		error="Error 7c: Copy constructor appears to not have made a deep copy";
	}
	return rc;	
}


/*Test 8: Test Assignment Operator*/
bool test8(std::string& error){
	DisjointSet theSet(100);
	DisjointSet copy(50);
	DisjointSet copy2(30);
	bool result;
	int rep1;
	int rep2;
	bool rc=true;
	for(int i=0;i<50;i++){
		copy.makeSet(i);
	}
	for(int i=0;i<30;i++){
		copy2.makeSet(i);
	}

	for(int i=0;i<100;i++){
		theSet.makeSet(i);
	}
	for(int i=0;rc && i<100;i+=2){
		result = theSet.unionSets(i,i+1);
	}
	for(int i=0;rc && i<50;i+=2){	
		theSet.unionSets(i*2,(i+1)*2);
	}
	for(int i=0,j=99;rc && i<48;i+=4,j-=4){
		theSet.unionSets(i,j);
	}
	copy2=copy=theSet;
	for(int i=0,j=99;rc && i<48;i+=4,j-=4){
		int newRep=copy.findSet(i);
		for(int k=0;rc && k<4;k++){
			if(copy.findSet(i+k)!=newRep){
				rc=false;
				error ="Error 8a: copy assignment operator did not produce a duplicate with same disjoint sets";
			}
			if(copy.findSet(j-k)!=newRep){
				rc=false;
				error="Error 8b: copy assignment operator did not produce a duplicate with same disjoint sets";
			}
		}
	}
	for(int i=0,j=99;rc && i<48;i+=4,j-=4){
		int newRep=copy2.findSet(i);
		for(int k=0;rc && k<4;k++){
			if(copy2.findSet(i+k)!=newRep){
				rc=false;
				error ="Error 8c: possible return value error in assignment operator";
			}
			if(copy2.findSet(j-k)!=newRep){
				rc=false;
				error="Error 8d: possible return value error in assignment operator";
			}
		}
	}
	result=theSet.unionSets(97,50);
	if(copy.findSet(97) == copy.findSet(50)){
		rc=false;
		error="Error 8e: assignment operator appears to not have made a deep copy";
	}
	if(copy2.findSet(97) == copy2.findSet(50)){
		rc=false;
		error="Error 8e: assignment operator appears to not have made a deep copy";
	}

	return rc;	
}

/*Test 9: Test move constructor*/
bool test9(std::string& error){
	DisjointSet theSet(100);
	bool result;
	int rep1;
	int rep2;
	bool rc=true;
	for(int i=0;i<100;i++){
		theSet.makeSet(i);
	}
	for(int i=0;rc && i<100;i+=2){
		result = theSet.unionSets(i,i+1);
	}
	for(int i=0;rc && i<50;i+=2){	
		theSet.unionSets(i*2,(i+1)*2);
	}
	for(int i=0,j=99;rc && i<48;i+=4,j-=4){
		theSet.unionSets(i,j);
	}
	DisjointSet copy=std::move(theSet);
	for(int i=0,j=99;rc && i<48;i+=4,j-=4){
		int newRep=copy.findSet(i);
		for(int k=0;rc && k<4;k++){
			if(copy.findSet(i+k)!=newRep){
				rc=false;
				error ="Error 9a: move constructor did not produce a duplicate with same disjoint sets";
			}
			if(copy.findSet(j-k)!=newRep){
				rc=false;
				error= "Error 9b: move constructor did not produce a duplicate with same disjoint sets";
			}
		}
	}

	return rc;	
}


/*Test 10: Test Move Assignment Operator*/
bool test10(std::string& error){
	DisjointSet theSet(100);
	DisjointSet copy(50);
	bool result;
	int rep1;
	int rep2;
	bool rc=true;
	for(int i=0;i<50;i++){
		copy.makeSet(i);
	}
	for(int i=0;i<100;i++){
		theSet.makeSet(i);
	}
	for(int i=0;rc && i<100;i+=2){
		result = theSet.unionSets(i,i+1);
	}
	for(int i=0;rc && i<50;i+=2){	
		theSet.unionSets(i*2,(i+1)*2);
	}
	for(int i=0,j=99;rc && i<48;i+=4,j-=4){
		rep1=theSet.findSet(i);
		rep2=theSet.findSet(j);
		result=theSet.unionSets(i,j);
	}
	copy=std::move(theSet);
	for(int i=0,j=99;rc && i<48;i+=4,j-=4){
		int newRep=copy.findSet(i);
		for(int k=0;rc && k<4;k++){
			if(copy.findSet(i+k)!=newRep){
				rc=false;
				error ="Error 10a: move assignment did not produce a duplicate with same disjoint sets";
			}
			if(copy.findSet(j-k)!=newRep){
				rc=false;
				error= "Error 10b: move assignment did not produce a duplicate with same disjoint sets";
			}
		}
	}

	return rc;	
}
/*Test 11: Timing runs, no errors for these.*/
bool test11(std::string& error){

	Timer t;
	Timer t2;
	DisjointSet set1(50000);
	DisjointSet set2(50000);
	t.reset();
	for(int i=0;i<50000;i++){
		t.start();
		set1.makeSet(i);
		set2.makeSet(i);
		t.stop();
	}
	std::cout << "100000 makeSet(): " << t.currtime() << std::endl;

	t2.reset();
	for(int i=0;i<49999;i++){
		t2.start();
		set1.unionSets(i,i+1);
		t2.stop();
	}
	std::cout << "49999 unionSets(): " << t2.currtime() << std::endl;
	t2.reset();
	for(int i=0;i<49999;i++){
		int choice=rand()%(i+1);
		t2.start();
		set2.unionSets(i+1,choice);
		t2.stop();
	}
	t.reset();
	std::cout << "another 49999 unionSets(): " << t2.currtime() << std::endl;
	for(int i=0;i<50000;i++){
		t.start();
		set2.findSet(i);
		t.stop();
	}
	std::cout << "another 50000 findSets(): " << t.currtime() << std::endl;


	return true;
}