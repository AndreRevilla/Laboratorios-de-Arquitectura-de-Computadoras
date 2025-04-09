#include <iostream>
#include <bitset>
using namespace std;

const int n = 4;

// Convierte de entero con signo a bitset complemento 2
bitset<n> entero_a_bitset(int num) {
    if (num < 0)
        return bitset<n>((1 << n) + num);
    else
        return bitset<n>(num);
}

// Convierte de bitset complemento 2 a entero con signo
int bitset_a_entero(bitset<n> bits) {
    if (bits[n - 1] == 1)
        return -((~bits).to_ulong() + 1);
    else
        return bits.to_ulong();
}
int bitset_a_entero(bitset<2 * n> bits) {
    if (bits[2 * n - 1] == 1)
        return -((~bits).to_ulong() + 1);
    else
        return bits.to_ulong();
}

// Suma binaria
bitset<n> suma(bitset<n> a, bitset<n> b) {
    int res = bitset_a_entero(a) + bitset_a_entero(b);
    return entero_a_bitset(res);
}

// Resta binaria
bitset<n> resta(bitset<n> a, bitset<n> b) {
    int res = bitset_a_entero(a) - bitset_a_entero(b);
    return entero_a_bitset(res);
}

// Shift aritmetico a la derecha de A, Q y Q-1
void shift_aritmetico(bitset<n>& A, bitset<n>& Q, int& Q_1) {
    int msb_A = A[n - 1];
    int lsb_A = A[0];
    int lsb_Q = Q[0];

    Q_1 = lsb_Q;

    Q >>= 1;
    Q[n - 1] = lsb_A;

    A >>= 1;
    A[n - 1] = msb_A;
}

// Algoritmo de Booth
void algoritmoBooth(int multiplicando, int multiplicador) {
    bitset<n> M = entero_a_bitset(multiplicando);
    bitset<n> Q = entero_a_bitset(multiplicador);
    bitset<n> A(0);
    int Q_1 = 0;
    int count = n;

    cout << "\nAlgoritmo de Booth\n";
    cout << "Multiplicando (M): " << M << " (" << multiplicando << ")\n";
    cout << "Multiplicador (Q): " << Q << " (" << multiplicador << ")\n";

    while (count--) {
        cout << "\nA: " << A << " Q: " << Q << " Q-1: " << Q_1 << "\n";

        if (Q[0] == 1 && Q_1 == 0) {
            A = resta(A, M);
            cout << "A = A - M -> " << A << "\n";
        } else if (Q[0] == 0 && Q_1 == 1) {
            A = suma(A, M);
            cout << "A = A + M -> " << A << "\n";
        }

        shift_aritmetico(A, Q, Q_1);
        cout << "Shift -> A: " << A << " Q: " << Q << " Q-1: " << Q_1 << "\n";
    }

    bitset<2 * n> resultado((A.to_ulong() << n) | Q.to_ulong());
    int resultado_decimal = bitset_a_entero(bitset<2*n>(resultado.to_ulong()));

    cout << "\nResultado final (binario): " << resultado << "\n";
    cout << "Resultado final (decimal): " << resultado_decimal << "\n";
}

int main() {
    int multiplicando, multiplicador;

    cout << "Ingrese el multiplicando: ";
    cin >> multiplicando;
    cout << "Ingrese el multiplicador: ";
    cin >> multiplicador;

    algoritmoBooth(multiplicando, multiplicador);
    return 0;
}
