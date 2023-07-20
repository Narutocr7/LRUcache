#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

//Node to store the data(Linked list)
class Node{
public:
    string key;
    int value;
    Node(string key,int value){
        this->key = key;
        this->value = value;
    }
};

//LRU Cache data structure
class LRUCache{
public:
    int maxSize;
    list<Node> l;
    unordered_map<string,list<Node>::iterator > m;

    LRUCache(int maxSize){
        this->maxSize = maxSize > 1 ? maxSize : 1;
    }

    //3 operations
    void insertKeyValue(string key,int value){
        //2 cases
        //present in cache: cache hit. If it is present in cache, it will be present in map also. 
        if(m.count(key) != 0){
            //update its value
            auto it = m[key];//m[key] gives the address
            it->value = value;
        }
        //not present in cache : cache miss
        else{
            //first check if cache is full
            //if full: we'll hv to delete the last node from list and remove its entry from map as well ans then insert the new k-v pair in the beginning of the list. 
            if(l.size() == maxSize){
                Node last = l.back();
                m.erase(last.key);//removes from hash_map
                l.pop_back();//removes from linked list.    
            }

            Node n(key,value);
            l.push_front(n);
            m[key] = l.begin();
        }
    }

    int* getValue(string key){
        //to get the value, that key shud be present in our map. 
        if(m.count(key) != 0){
            auto it = m[key];
            int value = it->value;
            //before we return the value, we'll hv to move this node to the beginning, bcz it is the most recently accessed.
            l.push_front(*it);
            l.erase(it);
            m[key] = l.begin();
            return &l.begin()->value; 
        }
        //if the value doesn't exist in map and in the cache, every key may not be present(tht's why returning an address)
        return NULL;
    }

    string mostRecentKey(){
        //..ret head of linked list
        return l.front().key;
    }
};

int main(){
    LRUCache lru(3);
    lru.insertKeyValue("mango",10);
    lru.insertKeyValue("apple",20);
    lru.insertKeyValue("guava",30);
    cout<<lru.mostRecentKey()<<endl;

    lru.insertKeyValue("mango",40);
    cout<<lru.mostRecentKey()<<endl;

    int *orders = lru.getValue("mango");
    if(orders != NULL){
        cout<<"Order of mango "<<*orders <<endl;
    }

    lru.insertKeyValue("banana",20);

    if(lru.getValue("apple") == NULL){
        cout<<"apple doesn't exist";
    }
    if(lru.getValue("guava") == NULL){
        cout<<"guava doesn't exist";
    }
    if(lru.getValue("banana") == NULL){
        cout<<"banana doesn't exist";
    }    
    if(lru.getValue("mango") == NULL){
        cout<<"mango doesn't exist";
    }

    return 0;    
}