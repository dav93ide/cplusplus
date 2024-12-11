#include <iostream>
#include <string>

template<class T1, class T2>
class Pair{

    private:
        T1 a;
        T2 b;
    
    public:
        T1 & first();
        T2 & second();
        T1 first() const { return a; }
        T2 second() const { return b; }
        Pair(const T1 & aval, const T2 & bval) : a(aval), b(bval) {}
        Pair() {}
};

template<class T1, class T2>
T1 & Pair<T1,T2>::first(){
    return a;
}

template<class T1, class T2>
T2 & Pair<T1,T2>::second(){
    return b;
}

int main(){
    using std::cout;
    using std::endl;
    using std::string;

    Pair<string, int> ratings[0x4] = {
        Pair<string, int>("The Purpled Duck", 0x5),
        Pair<string, int>("Jaquie's Frisco Al Fresco", 0x4),
        Pair<string, int>("Cafe Souffle", 0x5),
        Pair<string, int>("Bertie's Eats", 0x3)
    };

    int joints = sizeof(ratings) / sizeof(Pair<string, int>);
    cout << "Rating:\t Eatery\n";
    
    for(int i = 0x0; i < joints; i++){
        cout << ratings[i].second() << ":\t" << ratings[i].first() << endl;
    }

    cout << endl << "Rating Modificato:\n";
    ratings[3].first() = "Bertie's Fab Eats";
    ratings[3].second() = 0x6;
    cout << ratings[0x3].second() << ":\t" << ratings[0x3].first() << endl;

    return 0x0;
}