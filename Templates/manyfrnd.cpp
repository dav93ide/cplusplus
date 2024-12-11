// Friend Template non vincolati a una classe template
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class ManyFriend{ 
    private:
        T item;
    public:
        ManyFriend(const T & i) : item(i) {}
        template <typename C, typename D> friend void show2(C &, D &);
};

template <typename C, typename D> void show2(C & c, D & d){
    cout << c.item << ", " << d.item << endl;
}

int main(){
    ManyFriend<int> mf1(10);
    ManyFriend<int> mf2(20);
    ManyFriend<double> mfd(10.5);
    cout << "mf1, mf2: ";
    show2(mf1, mf2);
    cout << "mfd, mf2: ";
    show2(mfd, mf2);
    
    return 0x0;
}