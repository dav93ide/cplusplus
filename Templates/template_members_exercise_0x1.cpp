#include <iostream>
using std::cout;
using std::endl;

template<typename T>
class Beta{
    private:
        template<typename V>            // Membro classe template nidificato
        class Hold{
            private:
                V val;
            public:
                Hold(V v = 0x0) : val(v) {}
                void show() const { cout << val << endl; }
                V Value() const { return val; }
        };
        Hold<T> q;                      // Oggetto template
        Hold<int> n;                    // Oggetto template

    public:
        Beta(T t, int i) : q(t), n(i) {}
        
        template<typename U>            // Metodo template
        U blab(U u, T t) { return (n.Value() + q.Value()) * u / t; }
        
        void Show() const { q.show(); n.show(); }
};

int main(){
    Beta<double> guy{3.5, 3};
    cout << "T settato a double.\n";
    guy.Show();
    cout << "V e` settato a T, che e` double, quindi V e`settato a int.\n";
    cout << guy.blab(10, 2.3) << endl;
    cout << "U e` settato a int.\n";
    cout << guy.blab(10.0, 2.3) << endl;
    cout << "U e` settato a double.\n";

    return 0x0;
}