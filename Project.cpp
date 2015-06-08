// Project.cpp 
// Final Project
// Name:ZhangFuming  No:5140309508  Class:F1403022

#ifndef _MyList_h
#define _MyList_h

#include <iostream>

template <class T=int> class MyList;

template <class T=int>
MyList<T> operator+(const MyList<T> &l1, const MyList<T> &l2);

template <class T=int>
MyList<T> operator+(const MyList<T> &l1, const T &item);

template <class T=int>
std::ostream &operator<<(std::ostream &os, const MyList<T> &obj);

template<class T>
class MyList{
private:
	T *a;
	int size;
	int capacity;
	
	void double_space();

public:
	MyList(){
		size=0;
		capacity=100;
		a=new T [capacity];
	}
	MyList(int num, const T &item);
	MyList(const MyList &l);
    MyList(T* arr, int len);

	void push(const T &item);
	T pop();
	void insert(int index, const T &item);
	void clean();
	void erase(int start, int end); 
	int get_size();
	T get_item(int index) const;
	MyList get_item(int start, int end) const;
	int count(const T &item);
	void remove(const T &item);


	friend MyList<T> operator+ <T>(const MyList<T> &l1, const MyList<T> &l2); 
    friend MyList<T> operator+ <T>(const MyList<T> &l1, const T &item); 
	MyList &operator=(const MyList &l);
	MyList &operator+=(const T &item);
	MyList &operator+=(const MyList &l);
	T &operator[](int index);
	friend std::ostream & operator<< <T>(std::ostream &os, const MyList<T> &obj);

	void quickSort1(int l, int r);
	void quickSort2(int l, int r);
	void sort(bool less=true);
	void reverse();

	~MyList(){delete [] a;}	
};
#endif


template <class T>
MyList<T> operator+(const MyList<T> &l1, const MyList<T> &l2)
{
	MyList<T> temp;
	temp.size=l1.size+l2.size;
	temp.capacity=l1.capacity+l2.capacity;
	temp.a=new T [temp.capacity];
	for (int i=0; i<l1.size; ++i){
		temp.a[i]=l1.a[i];
	}
	for (int i=0; i<l2.size; ++i){
		temp.a[i+l1.size]=l2.a[i];
	}
	return temp;
}

template <class T>
MyList<T> operator+(const MyList<T> &l1, const T &item)
{
	MyList<T> temp;
	temp.size=l1.size;
	temp.capacity=l1.capacity;
	temp.a=new T [temp.capacity];
	if (temp.size==temp.capacity) temp.double_space();
	temp.a[temp.size++]=item;
	return temp;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const MyList<T> &obj)
{
	os << '[';
	for (int i=0; i<obj.size-1; ++i){
		os << obj.a[i] << ", ";
	}
	os << obj.a[obj.size-1] << ']';
	return os;
}

template <class T>
void MyList<T>::double_space()
{
	T *b;
	if(capacity==0) capacity=1;
	else capacity*=2;
	b=new T [capacity];
	
	for (int i=0; i<size; ++i){
		b[i]=a[i];
	}
	delete [] a;
	a=b;
}

template <class T>
MyList<T>::MyList(int num, const T &item)
{
	capacity=num;
	size=num;
	a=new T [capacity];
		
	for (int i=0; i<size; ++i){
		a[i]=item;
	}
}

template <class T>	
MyList<T>::MyList(T *arr, int len)
{
	capacity=len;
	size=len;
	a=new T [capacity];
	
	for (int i=0; i<size; ++i){
		a[i]=arr[i];
	}
}

template <class T>	
MyList<T>::MyList(const MyList<T> &l)
{
	capacity=l.capacity;
	size=l.size;
	a=new T [capacity];
	for (int i=0; i<size; ++i){
		a[i]=l.a[i];
	}
}

template <class T>
void MyList<T>::push(const T &item)
{
	if (size==capacity) double_space();
	a[size++]=item;
}

template <class T>
T MyList<T>::pop()
{
	T temp;
	temp=a[size-1];
	a[--size].~T();
	return temp;
}

template <class T>
void MyList<T>::insert(int index, const T &item)
{
	if (size==capacity) double_space();
	for (int i=size; i>index; --i){
		a[i]=a[i-1];
	}
	++size;
	a[index]=item;
	
}

template <class T>
void MyList<T>::clean()
{
	for (int i=0; i<size; ++i){
		a[i].~T();
	}
	size=0;
}

template <class T>
void MyList<T>::erase(int start, int end)
{
	for (int i=0; i<size-end-1; ++i){
		a[start+i]=a[end+1+i];
	}
	for (int i=0; i<end-start+1; ++i){
		a[start-end+size-1+i].~T();
	}
	size=size-(end-start+1);
}

template <class T>
int MyList<T>::get_size()
{
	return size;
}

template <class T>
T MyList<T>::get_item(int index) const
{
	return a[index];
}

template <class T>
MyList<T> MyList<T>::get_item(int start, int end) const
{
	MyList<T> temp;
	
	if (end<0){
		if (size+end<start) {
			temp.size=0;
			temp.capacity=0;
			temp.a=new T [size];
			return temp;
		}
		end=size+end;
	}
	
	temp.size=end-start+1;
	temp.capacity=end-start+1;
	temp.a=new T [capacity];
	for (int i=0; i<temp.size; ++i){
		temp.a[i]=a[start+i];
	}
	
	return temp;
}

template <class T>
int MyList<T>::count(const T &item)
{
	int icount;
	
	for (int i=0; i<size; ++i){
		if (a[i]==item) ++icount;
	}
	
	return icount;
}

template <class T>
void MyList<T>::remove(const T &item)
{
	for (int i=0; i<size; ++i){
		if (a[i]==item){
			for (int j=0; j<size-i-1; ++j){
				a[i+j]=a[i+j+1];
			}
			a[size-1].~T();
			--size;
			break;
		}
	}
}

template <class T>
MyList<T> &MyList<T>::operator=(const MyList<T> &l)
{
	if (this==&l) return *this;
	
	delete [] a;
	size=l.size;
	capacity=l.capacity;
	a=new T [capacity];
	for (int i=0; i<size; ++i){
		a[i]=l.a[i];
	}
	
	return *this;
}

template <class T>
MyList<T> &MyList<T>::operator+=(const T &item)
{
	if (size==capacity) double_space();
	a[size++]=item;
	return *this;
}

template <class T>
MyList<T> &MyList<T>::operator+=(const MyList &l)
{
	while (capacity<(size+l.size)) double_space();
	for (int i=0; i<l.size; ++i){
		a[size+i]=l.a[i];
	}
	size+=l.size;
	return *this;
}

template <class T>
T &MyList<T>::operator[](int index)
{
	if (index<0||index>=size){
		
	}
	return a[index];
}

template <class T>
void MyList<T>::reverse()
{
	T temp;
	for (int i=0; i<size/2; ++i){
		temp=a[size-1-i];
		a[size-1-i]=a[i];
		a[i]=temp;
	}
}

template <class T>
void MyList<T>::sort(bool less)
{
	if(less) quickSort1(0, size-1);
	else quickSort2(0, size-1);
}

template <class T>
void MyList<T>::quickSort1(int l, int r)  
{  
    if (l< r)  
    {        
        int i = l, j = r, x = a[l];  
        while (i < j)  
        {  
            while(i < j && a[j]>=x)
                j--;   
            if(i < j)  
                a[i++] = a[j];  
            while(i < j && a[i]<x) 
                i++;   
            if(i < j)  
                a[j--] = a[i];  
        }  
        a[i] = x;  
        quickSort1(l, i - 1);
        quickSort1(i + 1, r);  
    }  
}  

template <class T>
void MyList<T>::quickSort2(int l, int r)  
{  
    if (l< r)  
    {        
        int i = l, j = r, x = a[l];  
        while (i < j)  
        {  
            while(i < j && a[j]<=x)
                j--;   
            if(i < j)  
                a[i++] = a[j];  
            while(i < j && a[i]>x) 
                i++;   
            if(i < j)  
                a[j--] = a[i];  
        }  
        a[i] = x;  
        quickSort2(l, i - 1);
        quickSort2(i + 1, r);  
    }  
}  

using namespace std;
int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
	a[3] = 15; 
	a.sort(); 
	a.reverse(); 
	a += 12; 
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); 
	b = a.get_item(3, -1); 
	a += b; 
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); 
	cout<<b.get_size()<<endl;
	a.erase(2, 6); 
	b = a + a; 
	b.insert(3, 116); 
	b.remove(4); 
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	
	return 0;
}
