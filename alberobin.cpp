#include <iostream>
using namespace std;

template <typename T>
class Albero {
private:
    T dati[100];
    bool valido[100];
    int conteggioNodi;

public:
    Albero() {
        conteggioNodi = 0;
        for (int i = 0; i < 100; ++i) {
            valido[i] = false;
        }
    }

    bool vuoto() const {
        return conteggioNodi == 0;
    }

    void inserisciRadice(const T& valore) {
        if (conteggioNodi < 100) {
            dati[0] = valore;
            valido[0] = true;
            conteggioNodi = 1;
        }
    }

    T leggiRadice() const {
        return vuoto() ? T() : dati[0];
    }

    bool nodoFoglia(int indice) const {
        if (!valido[indice]) return false;
        int sinistro = 2 * indice + 1;
        int destro = 2 * indice + 2;
        return (sinistro >= 100 || !valido[sinistro]) && (destro >= 100 || !valido[destro]);
    }

    int indiceSinistro(int indice) const {
        int sinistro = 2 * indice + 1;
        return (sinistro < 100 && valido[sinistro]) ? sinistro : -1;
    }

    int indiceDestro(int indice) const {
        int destro = 2 * indice + 2;
        return (destro < 100 && valido[destro]) ? destro : -1;
    }

    void aggiungiSinistro(int indice, const T& valore) {
        int sinistro = 2 * indice + 1;
        if (sinistro < 100 && valido[indice] && !valido[sinistro]) {
            dati[sinistro] = valore;
            valido[sinistro] = true;
            ++conteggioNodi;
        }
    }

    void aggiungiDestro(int indice, const T& valore) {
        int destro = 2 * indice + 2;
        if (destro < 100 && valido[indice] && !valido[destro]) {
            dati[destro] = valore;
            valido[destro] = true;
            ++conteggioNodi;
        }
    }

    void eliminaNodo(int indice) {
        if (indice < 100 && valido[indice]) {
            if (nodoFoglia(indice)) {
                valido[indice] = false;
                --conteggioNodi;
            } else {
                int sinistro = 2 * indice + 1;
                int destro = 2 * indice + 2;

                if (sinistro < 100 && valido[sinistro]) {
                    valido[sinistro] = false;
                    --conteggioNodi;
                }

                if (destro < 100 && valido[destro]) {
                    valido[destro] = false;
                    --conteggioNodi;
                }

                valido[indice] = false;
                --conteggioNodi;
            }
        }
    }

    void mostraAlbero() const {
        for (int i = 0; i < 100; ++i) {
            if (valido[i]) {
                cout << "Nodo " << i << ": " << dati[i] << endl;

                int sinistro = indiceSinistro(i);
                int destro = indiceDestro(i);

                if (sinistro != -1 && valido[sinistro]) {
                    cout << "  Figlio sinistro: " << dati[sinistro] << endl;
                } else {
                    cout << "  Figlio sinistro: /" << endl;
                }

                if (destro != -1 && valido[destro]) {
                    cout << "  Figlio destro: " << dati[destro] << endl;
                } else {
                    cout << "  Figlio destro: /" << endl;
                }
            }
        }
    }
};

int main() {
    Albero<int> albero;

    albero.inserisciRadice(3);
    cout << "Inserisco la radice: " << endl;
    albero.mostraAlbero();

    albero.aggiungiSinistro(0, 12);
    albero.aggiungiDestro(0, 26);
    albero.aggiungiSinistro(1, 34);

    cout << "Albero dopo l'inserimento dei figli:" << endl;
    albero.mostraAlbero();

    int nodoCorrente = 0;
    int sinistro = albero.indiceSinistro(nodoCorrente);
    int destro = albero.indiceDestro(nodoCorrente);

    cout << "Nodo " << nodoCorrente << " (" << albero.leggiRadice() << ") ha:" << endl;
    cout << "Figlio sinistro all'indice: " << (sinistro != -1 ? sinistro : -1) << endl;
    cout << "Figlio destro all'indice: " << (destro != -1 ? destro : -1) << endl;

    albero.eliminaNodo(3);
    cout << "Rimuovo il nodo 3: " << endl;
    albero.mostraAlbero();

    return 0;
}
