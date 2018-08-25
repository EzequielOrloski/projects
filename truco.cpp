#include "truco.h"
void Truco::Distribui(){
    int naipe, valor;
	for(int i = 0; i < 3; i++){
        valor = rand() % 8;
        naipe = rand() % 4;
        switch(naipe){
            case 0:
                cout << "carta " << valor << " de copas" << endl;
                break;
            case 1:
                cout << "carta " << valor << " de ouro" << endl;
                break;
            case 2:
                cout << "carta " << valor << " de paus" << endl;
                break;
            case 3:
                cout << "carta " << valor << " de espadas" << endl;
                break;
        }
	}
}
int main(){
    Truco* t = new Truco();
    t->Distribui();


}
