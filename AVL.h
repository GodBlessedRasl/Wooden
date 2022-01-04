#ifndef AVL_H
#define AVL_H
struct avl_node // структура для представления узлов дерева
{
    int element;
    int high;
    avl_node* left;
    avl_node* right;
    avl_node(int k) {
        element = k;
        left = right = nullptr;
        high = 1;
    }
    avl_node(){
        element = 0;
        left = right = nullptr;
        high = 0;
    }
};
class avl{
public:
    void push(int x){
        root = insert(root, x);
    }
    void pop(int x){
        root = remove(root, x);
    }
    int height(avl_node* p)
    {
        return p?p->high:0;
    }
    bool check(avl_node* cur, int x){
        if(cur == nullptr){
            return 1;
        }else if(cur->element == x){
            return 0;
        } else{
            return (check(cur->left, x) && check(cur->right, x));
        }
    }
    avl_node* get(){
        return root;
    }
    int bfactor(avl_node* p)
    {
        return height(p->right)-height(p->left);
    }

    void fixheight(avl_node* p)
    {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->high = (hl>hr?hl:hr)+1;
    }

    avl_node* rotateright(avl_node* p) // правый поворот вокруг p
    {
        avl_node* q = p->left;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }

    avl_node* rotateleft(avl_node* q) // левый поворот вокруг q
    {
        avl_node* p = q->right;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }

    avl_node* balance(avl_node* p) // балансировка узла p
    {
        fixheight(p);
        if( bfactor(p)==2 )
        {
            if( bfactor(p->right) < 0 )
                p->right = rotateright(p->right);
            return rotateleft(p);
        }
        if( bfactor(p)==-2 )
        {
            if( bfactor(p->left) > 0  )
                p->left = rotateleft(p->left);
            return rotateright(p);
        }
        return p; // балансировка не нужна
    }

    avl_node* insert(avl_node* p, int k) // вставка ключа k в дерево с корнем p
    {
        if(!check(p, k)){
            return p;
        }
        if( !p ) return new avl_node(k);
        if( k<p->element )
            p->left = insert(p->left,k);
        else
            p->right = insert(p->right,k);
        return balance(p);
    }

    avl_node* findmin(avl_node* p) // поиск узла с минимальным ключом в дереве p
    {
        return p->left?findmin(p->left):p;
    }

    avl_node* removemin(avl_node* p) // удаление узла с минимальным ключом из дерева p
    {
        if( p->left==0 )
            return p->right;
        p->left = removemin(p->left);
        return balance(p);
    }

    avl_node* remove(avl_node* p, int k) // удаление ключа k из дерева p
    {
        if( !p ) return 0;
        if( k < p->element )
            p->left = remove(p->left,k);
        else if( k > p->element )
            p->right = remove(p->right,k);
        else //  k == p->key
        {
            avl_node* q = p->left;
            avl_node* r = p->right;
            delete p;
            if( !r ) return q;
            avl_node* min = findmin(r);
            min->right = removemin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }
private:
    avl_node* root = nullptr;
};

#endif // AVL_H
