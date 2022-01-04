#ifndef DEKART_H
#define DEKART_H
#include "random"
class search_node
{
public:
    int x;
    int y;

    search_node* left;
    search_node* right;

//    dekart_node(int x, int y, Treap left = null, Treap right = null)
//    {
//        this.x = x;
//        this.y = y;
//        this.Left = left;
//        this.Right = right;
//    }
    search_node(int k) {
        x = k;
        left = right = 0;
        y = rand()%1000;
    }
    search_node(){
        x = 0;
        left = right = 0;
        y = rand()%1000;
    }
    search_node(int  x1, int y1,search_node* left1 = nullptr, search_node* right1 = nullptr)
        {
            x = x1;
            y = y1;
            left = left1;
            right = right1;
        }
    search_node* Merge(search_node* L, search_node* R)
    {
        if (L == nullptr) return R;
        if (R == nullptr) return L;

        if (L->y > R->y)
        {
            search_node* newR = Merge(L->right, R);
            return new search_node(L->x, L->y, L->left, newR);
        }
        else
        {
            search_node* newL = Merge(L, R->left);
            return new search_node(R->x, R->y, newL, R->right);
        }
    }

    void Split(int x1, search_node* L, search_node* R)
    {
        search_node* newTree = nullptr;
        if (this->x <= x1)
        {
            if (this->right == nullptr)
                R = nullptr;
            else
                (this->right)->Split(x1, newTree,  R);
            L = new search_node(this->x, y, this->left, newTree);
        }
        else
        {
            if (left == nullptr)
                L = nullptr;
            else
                left->Split(x1, L,  newTree);
            R = new search_node(this->x, y, newTree, right);
        }
    }

    search_node* Add(int x)
    {
        search_node* l;
        search_node* r;
        Split(x,  l,  r);
        search_node* m = new search_node(x, rand());
        return Merge(Merge(l, m), r);
    }

    search_node* Remove(int x)
    {
        search_node* l;
        search_node* m;
        search_node* r;
        Split(x - 1,  l,  r);
        r->Split(x, m, r);
        return Merge(l, r);
    }
};

#endif // DEKART_H
