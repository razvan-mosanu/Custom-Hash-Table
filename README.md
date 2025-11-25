# ⚡ Fast Custom Hash Map for Competitive Programming

O implementare performantă și sigură a unei tabele de dispersie (Hash Table) în C++, optimizată special pentru **programarea competitivă**. 

Această structură de date este concepută pentru a fi mai rapidă decât `std::unordered_map` și rezistentă la cazurile de test "anti-hash" (care provoacă coliziuni deliberate), folosind un seed aleatoriu și algoritmul `splitmix64`.

## 🚀 Caracteristici Principale

- **🛡️ Anti-Hack Hashing:** Utilizează `splitmix64` combinat cu un seed bazat pe `chrono::steady_clock`. Aceasta previne coliziunile pe platforme precum Codeforces, unde `std::unordered_map` poate fi încetinit intenționat.
- **⚡ Performanță:** Operațiile de ștergere sunt $O(1)$ folosind tehnica "swap with back" în bucket-uri.
- **📊 Frequency Counter:** Structura reține automat frecvența elementelor (similar cu un `multiset` sau `Counter` din Python), economisind memorie pentru elementele duplicate.
- **📦 Rezolvarea Coliziunilor:** Folosește înlănțuirea (chaining) prin `vector`.

## 🛠️ Cum funcționează

Codul definește o clasă template `Hash<T>` care gestionează inserarea, căutarea și ștergerea.

### Funcția de Hash
Pentru tipul `int`, se folosește o specializare care amestecă biții numărului cu un timestamp curent:
```cpp
x += 0x9e3779b97f4a7c15;
x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
// ... (splitmix64 logic)
```

### Structura Internă
Datele sunt stocate într-un `vector<vector<pair<T, int>>> H`.
- `T`: Valoarea cheii.
- `int`: Numărul de apariții (frecvența).

## 💻 Utilizare

Include clasa în sursa ta C++. Deoarece este un template, funcționează "header-only".

### Exemplu de Cod

```cpp
#include <iostream>
#include "path/to/hash_code.cpp" // Sau copy-paste direct

using namespace std;

int main() {
    // 1. Inițializare (dimensiune default ~660k)
    Hash<int> map; 

    // 2. Inserare
    map.Insert(10);
    map.Insert(10); // Frecvența devine 2
    map.Insert(42);

    // 3. Verificare și Numărare
    if (map.Find(10)) {
        cout << "10 apare de " << map.Count(10) << " ori.\n"; // Output: 2
    }

    // 4. Ștergere
    map.Delete(10); // Scade frecvența la 1
    map.Delete(10); // Scade frecvența la 0 -> Elimină elementul fizic
    
    if (!map.Find(10)) {
        cout << "10 a fost sters complet.\n";
    }

    return 0;
}
```

## ⚙️ API Reference

| Metodă | Descriere | Complexitate (Medie) |
| :--- | :--- | :---: |
| `Hash(int _n)` | Constructor. `_n` este mărimea tabelei (recomandat număr prim). | $O(N)$ |
| `void Insert(T x)` | Adaugă `x`. Dacă există, incrementează contorul. | $O(1)$ |
| `void Delete(T x)` | Scade frecvența lui `x`. Dacă ajunge la 0, îl șterge. | $O(1)$ |
| `int Count(T x)` | Returnează de câte ori apare `x` în tabelă. | $O(1)$ |
| `bool Find(T x)` | Returnează `true` dacă `x` există (frecvență > 0). | $O(1)$ |

## ⚠️ Note

- **Specializare Template:** Codul curent conține logica de hashing (`splitmix64`) implementată doar pentru `int`. Dacă dorești să folosești `long long` sau `string`, trebuie să adaugi o specializare pentru `HashFunction<long long>` etc.
- **Include-uri:** Codul folosește `<bits/stdc++.h>`. Dacă compilezi pe un mediu non-GCC (ex: MSVC sau Clang pe macOS), va trebui să incluzi manual: `<vector>`, `<chrono>`, `<utility>`.

## 🤝 Contribuții

Acesta este un snippet pentru uz personal în concursuri. Simte-te liber să faci fork și să adaugi suport pentru alte tipuri de date!

---
*Happy Coding!* 🧑‍💻
