# PWR Racing Team Dział Software
## Zadanie rekrutacyjne nr.2
Plik z przykładowym zbiorem punktów - "input.txt"
Do rozwiązania problemu wykorzystany został algorytm Grahama, służący do znajdywania zbioru punktów tworzących otoczkę wypukłą

## Algorytm Grahama
### 1. Wybieramy punkt o najmniejszej współrzędnej y.
- Jeśli jest kilka takich punktów, wybieramy ten o najmniejszej współrzędnej x
### 2. Sortujemy wszystkie pozostałe punkty względem kąta nachylenia odcinka łączącego je z wybranym punktem. W przypadku równego kąta wybieramy punkt bliższy .
### 3. Budowanie otoczki wypukłej
- Przechodzimy przez posortowane punkty i dodajemy je do stosu (stos reprezentuje aktualnie budowaną otoczkę).
- Jeśli dodanie nowego punktu powoduje obrót w lewo (zgodny z ruchem zegara), dodajemy punkt do otoczki.
- Jeśli powoduje obrót w prawo (przeciwko ruchowi zegara), usuwamy ostatni punkt ze stosu i sprawdzamy ponownie.
- Kontynuujemy ten proces aż do przejrzenia wszystkich punktów.
### 4. Zwrócenie otoczki wypukłej
- Po przejściu wszystkich punktów, stos zawiera punkty tworzące naszą otoczkę wypukłą
### 5. Ilustracje pomocnicze
![Convex-Hull-using-Graham-Scan-1](https://github.com/user-attachments/assets/74429bef-cef0-4c4f-b488-ccc36f9a6dcc)
![Convex-Hull-using-Graham-Scan-2](https://github.com/user-attachments/assets/93ac0112-99e4-4fa7-b8ff-11eacf531589)
