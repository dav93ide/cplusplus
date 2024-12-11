// Template Friends vincolati a una classe template
#include <iostream>
using std::cout;
using std::endl;

template <typename T> void counts();
template <typename T> void report(T &);

template <typename TT>
class HasFriendT {
    private:
        TT item;
        static int ct;

    public:
        HasFriendT(const TT & i) : item(i) {ct++;}
        ~HasFriendT() {ct--;}
        friend void counts<TT>();
        friend void report<>(HasFriendT<TT> &);
};

template <typename T>
int HasFriendT<T>::ct = 0;

template <typename T>
void counts(){                                                                  // definizione della funzione friend template
    cout << "template size: " << sizeof(HasFriendT<T>) << "; ";
    cout << "template counts(): " << HasFriendT<T>::ct << endl;
}

template <typename T>
void report(T & hf){
    cout << hf.item << endl;
}

int main(){
    counts<int>();
    HasFriendT<int> h1(10);
    HasFriendT<int> h2(20);
    HasFriendT<double> hb(10.5);
    report(h1);
    report(h2);
    report(hb);
    cout << "counts<int>() output:\n";
    counts<int>();
    cout << "counts<double>() output:\n";
    counts<double>();

    return 0x0;
}