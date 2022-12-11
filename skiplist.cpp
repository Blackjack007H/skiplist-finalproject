#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cassert>
using namespace std;

class SkipList
{
public:
    SkipList(int max_level, int p)
       : max_level(max_level), _p(p)
    {
        head = make_shared<Node>();
        head->data = 0;
        head->level.resize(max_level, 0);
    }

    void insert(int data)
    {
        int level = 0;
        while (rand() % 2 )
            ++ level;
        level = min(level, max_level - 1);

        auto new_node = make_shared<Node>();
        new_node->data = data;
        new_node->level.resize(level + 1, nullptr);

        auto cur = head;
        for (int i = max_level - 1; i >= 0; --i)
        {
            while (cur->level[i] && cur->level[i]->data < data)
                cur = cur->level[i];
            if (i <= level)
            {
                new_node->level[i] = cur->level[i];
                cur->level[i] = new_node;
            }
        }
    }

    bool find(int data)
    {
        auto cur = head;
        for (int i = max_level - 1; i >= 0; --i)
        {
            while (cur->level[i] && cur->level[i]->data < data)
                cur = cur->level[i];
            if (cur->level[i] && cur->level[i]->data == data)
                return true;
        }
        return false;
    }

    void erase(int data)
    {
        auto cur = head;
        for (int i = max_level - 1; i >= 0; --i)
        {
            while (cur->level[i] && cur->level[i]->data < data)
                cur = cur->level[i];
            if (cur->level[i] && cur->level[i]->data == data)
                cur->level[i] = cur->level[i]->level[i];
        }
    }

    void print()
    {
        cout<<"\n*****Skip List*****"<<"\n";
        for (int i = max_level - 1; i >= 0; --i)
        {
            auto cur = head->level[i];
            cout<<"Level "<<i<<": ";
            while (cur)
            {
                cout << cur->data << " ";
                cur = cur->level[i];
            }
            cout << endl;
        }
    }

private:
    struct Node
    {
        int data;
        vector<shared_ptr<Node>> level;
    };
    shared_ptr<Node> head;
    int max_level ;
    int _p;
};

void test()
{
    SkipList list(3,3);
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(6);
    list.insert(7);
    list.insert(8);
    list.insert(9);
    list.insert(10);
    list.print();
    assert(list.find(1));
    assert(list.find(2));
    assert(list.find(3));
    assert(list.find(4));
    assert(list.find(5));
    assert(list.find(6));
    assert(list.find(7));
    assert(list.find(8));
    assert(list.find(9));
    assert(list.find(10));
    assert(!list.find(11));
    assert(!list.find(0));
    list.erase(4);
    list.erase(2);
    list.print();
}

int main()
{
    srand((unsigned int)time(0));
    test();
    return 0;
}
