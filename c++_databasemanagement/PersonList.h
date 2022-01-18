#include<iostream>
#include<string.h>
#include<fstream>
#include<cstdlib>
using namespace std;
class PersonList{
	
	int age;
	string name;
	PersonList *nextage;
	PersonList *nextname;
	
	public:
		void add(string name, int age);
		bool remove(string name);
		void update(string name, int age);
		void printByAge();
		void printByName();
		void loadFile(string filename);
		void saveToFileByAge(string filename);
		void saveToFileByName(string filename);
};
//////////////////////////////////////////////////////////////////////////////////
PersonList *headage;
PersonList *newnode;
PersonList *headname;
void PersonList::add(string name, int age){
	PersonList *newnode=new PersonList();
	newnode->age=age;
	newnode->name=name;
	newnode->nextage=NULL;
	newnode->nextname=NULL;
	if(headage==NULL){ //boþsa ekledim..
		headage=newnode;
	}
	if(headname==NULL){
		headname=newnode;
	}
	if(newnode->age < headage->age){ // baþa ekledim..
		newnode->nextage=headage;
		headage=newnode;
	}
	if(newnode->name < headname->name){
		newnode->nextname=headname;
		headname=newnode;
	}
	//araya veya sona ekledim..
	PersonList *i=headage;
	while(i->nextage!=NULL && ((i->nextage->age) <= age)){
		i=i->nextage;
	}
	if(i->age!=age){
		PersonList *temp=new PersonList();
		temp->nextage=i->nextage;
		i->nextage=temp;
		temp->age=age;
		temp->name=name;
	}
	PersonList *iter=headname;
	while(iter->nextname!=NULL && ((iter->nextname->name) <= name)){
		iter=iter->nextname;
	}
	if(iter->name!=name){
		PersonList *temp=new PersonList();
		temp->nextname=iter->nextname;
		iter->nextname=temp;
		temp->name=name;
		temp->age=age;
	}
}
//////////////////////////////////////////////////////////////////////////////////
PersonList *bas;
PersonList *tempo;
PersonList *bas1;
PersonList *tempo1;

bool PersonList::remove(string name){
	bas=headname;
	tempo=headname;
	bas1=headage;
	tempo1=headage;
	
	if(bas->name==name){//bastaki isim siliniyorsa..
		headname=bas->nextname;
		while(bas1->age != bas->age){
			bas1=bas1->nextage;
		}
				
		if(bas1->age==headage->age){
			headage=bas1->nextage;
			delete bas1;
			return 1;
		}
		if(bas1->nextage!=NULL && bas1->age > headage->age){
			while(tempo1->nextage->age!=bas1->age){
				tempo1=tempo1->nextage;
			}
			tempo1->nextage=bas1->nextage;
			delete bas1;
			bas1->nextage=NULL;
			return 1;
		}
		if(bas1->nextage==NULL){
			while(tempo1->nextage->age!=bas1->age){
				tempo1=tempo1->nextage;
			}
			tempo1->nextage=NULL;
			delete bas1;
			return 1;
		}
		delete bas;
		return 1;
	}
	//sondaki yada aradaki silincekse..
	bas=bas->nextname;
	while(bas!=NULL){
		if(bas->name==name){
			tempo->nextname=bas->nextname;
			while(bas1->age != bas->age){
				bas1=bas1->nextage;
			}
				
			if(bas1->age==headage->age){
				headage=bas1->nextage;
				delete bas1;
				delete bas;
				return 1;
			}
			if(bas1->nextage!=NULL && bas1->age > headage->age){
				while(tempo1->nextage->age!=bas1->age){
					tempo1=tempo1->nextage;
				}
				tempo1->nextage=bas1->nextage;
				delete bas1;
				delete bas;
				bas1->nextage=NULL;
				return 1;
			}
			if(bas1->nextage==NULL){
				while(tempo1->nextage->age!=bas1->age){
					tempo1=tempo1->nextage;
				}
				tempo1->nextage=NULL;
				delete bas1;
				delete bas;
				return 1;
			}
			
			return 1;
		}
		tempo=bas;
		bas=bas->nextname;
	}
	if(bas==NULL){
		cout<<name<<" does not exists";
		cout<<endl;
		return 0;
	}
}
//////////////////////////////////////////////////////////////////////////////////
void PersonList::update(string name, int age){
	cout<<"\n";
	PersonList::remove(name);
	PersonList::add(name,age);
	cout<<name<<" kisisinin yasi guncellendi !"<<endl;
}
//////////////////////////////////////////////////////////////////////////////////
void PersonList::printByAge(){
	PersonList *ilk=headage;
	if(ilk==NULL){
		cout<<"liste bos!! \n";
	}
	while(ilk!=NULL){
		cout<<ilk->age<<"  "<<ilk->name<<endl;
		ilk=ilk->nextage;
	}
	cout<<"*** end of list by age ***"<<endl;
}
///////////////////////////////////////////////////////////////////////////////////
void PersonList::printByName(){
	PersonList *first=headname;
	if(first==NULL){
		cout<<"liste bos!! \n";
	}
	while(first!=NULL){
		cout<<first->name<<"  "<<first->age<<endl;
		first=first->nextname;
	}
	cout<<"--- end of list by name ---"<<endl;
}
//////////////////////////////////////////////////////////////////////////////////
void PersonList::loadFile(string filename){
	ifstream file;
	file.open(filename.c_str());
	string name;
	int age;
	while(!file.eof()){
		file>>name>>age;
		PersonList::add(name,age);
	}
	file.close();
}
//////////////////////////////////////////////////////////////////////////////////
void PersonList::saveToFileByAge(string filename){
	ofstream file;
	file.open(filename.c_str());
	PersonList *basss=headage;
	while(basss!=NULL){
		file<<basss->age<<" "<<basss->name<<endl;
		basss=basss->nextage;
	}
	file.close();
}
//////////////////////////////////////////////////////////////////////////////////
void PersonList::saveToFileByName(string filename){
	ofstream file;
	file.open(filename.c_str());
	PersonList *bass=headname;
	while(bass!=NULL){
		file<<bass->name<<" "<<bass->age<<endl;
		bass=bass->nextname;
	}
	file.close();
}
//////////////////////////////////////////////////////////////////////////////////

