#include <iostream>
#include <iomanip>

using namespace std;

template <class T>
struct Node
{
	T data;
	int priority;
	Node<T> *next;
};

template <class T>
class Priority_Q
{
	Node<T> *front;
	Node<T> *rear;
	public:
	Priority_Q();
	void enqueue(T data, int p);
	Node<T>* getnode(Node<T> *head);
	void dequeue();
	bool isempty();
	void disp();
	Node<T>* ret_front();
};

template<class T>
Priority_Q<T>::Priority_Q() 
{
	front = NULL;
	rear = NULL;
}


template<class T>
void Priority_Q<T>::enqueue(T data, int p)
{
	Node<T> *tmp;
	Node<T> *temp;
	temp = ret_front();
	tmp = this->getnode(tmp);
	tmp->priority = p;
	tmp->data = data;
	tmp->next = NULL;

	if(front == NULL || rear == NULL)
	{
		rear = tmp;
		front = rear;
	}
	else if(tmp->priority < front->priority)
	{
		tmp->next = front;
		front = tmp;
	}
	else
	{
		while(temp->next!= NULL && (tmp->priority >= temp->next->priority))
			temp = temp->next;

		if(tmp->next == NULL)
		{
			rear = tmp;
			tmp->next = temp;
		}
		tmp->next = temp->next;
		temp->next = tmp;
	}
}


template <class T>
void Priority_Q<T>::dequeue()		//dequeue
{
	//case 1: queue is empty
	if(front == NULL && rear == NULL)
		return;
	else
	{
		//case 2: queue is not empty
		if(front == rear)
		{
			delete front;
			front = rear = NULL;
		}
		else
		{

			Node<T> *temp = front->next;
			delete front;
			front = temp;
		}
	}
}
template <class T>
Node<T>* Priority_Q<T>::ret_front()			
{
	return front;
}

template <class T>
bool Priority_Q<T>::isempty()
{
	if(front == NULL && rear == NULL)
		return true;
	else
		return false;
}

template <class T>
void Priority_Q<T>::disp()			//display the display
{
	std::cout<<std::endl;
	Node<T> *obj = front;
	std::cout<<obj->data;
	obj = obj->next;
	while(obj!=NULL)
	{
		std::cout<<std::endl<<obj->data;
		obj = obj->next;
	}
	std::cout<<std::endl;
}

template <class T>
Node<T>* Priority_Q<T>::getnode(Node<T> *head)
{
	head = new Node<T>;
	head->next = NULL;
	return head;
}

struct p_data				//structure for patient data
{
	int priority;
	string name;
	string phone;
	int age;
	string bgrp;
	char gender;
};
string checkp(int p)			
{
	switch(p)
	{
	case 1: return "Emergency";
	case 2: return "Follow up";
	case 3: return "General";
	}
	return "-1";
}
ostream& operator<<(ostream& out, p_data obj)		
{
	out<<"| "<<setw(8)<<obj.name<<" | "<<setw(11)<<checkp(obj.priority);
	out<<" | "<<setw(6)<<obj.bgrp<<" | "<<setw(3)<<obj.age<<" | ";
	return out;
}
class Patient			//class for priority queue patient
{
	Priority_Q<p_data> pq;
	public:
	void add(p_data);
	void del();
	void display();
};

bool cphone(string phone)
{
	if(phone.size() == 10)
	{
		for(int i=0; i<10; i++)
		{
			if(!isdigit(char(phone[i])))
				return false;
		}
		return true;
	}
	return false;
}

bool cbgp(string bgp)
{
	if(bgp == "A+" || bgp == "A-" || bgp == "AB+" || bgp == "AB-" || bgp == "B+" || bgp == "B-" || bgp == "O+" || bgp == "O-")
	{
		return true;
	}
	else
		return false;
}

bool cname(string name)
{
	int i = 0;
	while(name[i]!='\0')
	{
		if(!isalpha(char(name[i])))
			return false;
		i++;
	}
	return true;
}
void Patient::add(p_data obj)		//add patient to queue according to priority
{

	cout<<"\nEnter patient details: \n";
	cout<<"Name: ";
	cin>>obj.name;
	while(1)
	{
		if(cname(obj.name))
			break;
		cout<<"Invalid name, please try again.\n";
		cin>>obj.name;
	}
	cin.ignore();
	cout<<"\nPhone: ";
	cin>>obj.phone;
	while(1)
	{
		if(cphone(obj.phone))
			break;
		cout<<"Invalid phone number, please try again.\n";
		cin>>obj.phone;
	}
	cout<<"\nBlood group: ";
	cin>>obj.bgrp;
	while(1)
	{
		if(cbgp(obj.bgrp))
			break;
		cout<<"Invalid blood group, please try again.\n";
		cin>>obj.bgrp;
	}
	cout<<"\nAge: ";
	cin>>obj.age;
	cout<<"\nGender (M/F): ";
	cin>>obj.gender;
	cout<<"\nSelect category: \n";
	cout<<"\n\t1. Emergency\n\t2. Follow up appointment\n\t3. General\n\n\t";
	cin>>obj.priority;

	pq.enqueue(obj, obj.priority);
}

void Patient::del()				//delete a queue
{
	pq.dequeue();
}

void Patient::display()			//displaying the patient queue
{
	cout<<"\nPatient Queue is: \n";
	cout<<"\n=============================================\n";
	cout<<"| "<<setw(8)<<"    Name | "<<"     Case    | "<<setw(8)<<" BloodG | "<<setw(5)<<"Age |\n";
	cout<<"===============================================";
	pq.disp();
	cout<<"==============================================\n";
}
int main() {
	int c = 0;
	Patient hosp;
	p_data obj;
	while(c!=4)
	{
		cout<<"\n\n1. Enter new patient details\n2. Dequeue a patient\n3. Display current queue\n4. Exit\n\nEnter your choice: ";
		cin>>c;
		switch(c)
		{

		case 1:
			hosp.add(obj);
			break;

		case 2:
			hosp.del();
			break;

		case 3:
			hosp.display();
			break;

		case 4:
			break;

		default: 
			break;

		}
	}
	return 0;
}