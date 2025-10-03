# README - Explicatie cod program

Acest document explica modul in care functioneaza programul si descrie fiecare functie utilizata pentru procesarea imaginilor.

## Introducere
Programul este conceput pentru a incarca, salva, selecta, roti, decupa, aplica filtre si egaliza imagini in diverse formate. Programul suporta atat imagini alb-negru cat si imagini color in format RGB.

### Structuri de date utilizate
1. `typedef struct { int r, g, b; } pixel;`
   - Structura `pixel` reprezinta un pixel color, avand trei componente: rosu (`r`), verde (`g`) si albastru (`b`).

### Macrodefinitii
1. `#define CMAX 50` - Dimensiunea maxima a comenzii citite de la tastatura.
2. `#define FNMAX 100` - Dimensiunea maxima a numelui fisierului.

### Functii principale

#### 1. `void free_memory(int ***imagine, pixel ***imagine_rgb, int linie)`
Aceasta functie elibereaza memoria alocata dinamic pentru matricele de imagine, fie ele alb-negru sau RGB.
- Parcurge liniile matricelor si elibereaza fiecare linie in parte.
- Elibereaza memoria pentru matricele principale si seteaza pointerii la `NULL`.

#### 2. `void load_text_matrix(FILE *file, int ***imagine, int linie, int coloana)`
Incarca o imagine alb-negru dintr-un fisier text.
- Aloca memorie pentru matricea de imagine.
- Citeste valorile pixelilor din fisier si le stocheaza in matrice.

#### 3. `void load_text_rgb_matrix(FILE *file, pixel ***imagine_rgb, int linie, int coloana)`
Incarca o imagine color (RGB) dintr-un fisier text.
- Aloca memorie pentru matricea de pixeli.
- Citeste tripletele de valori (R, G, B) din fisier si le stocheaza in matrice.

#### 4. `void load_binary_matrix(FILE *file, int ***imagine, int linie, int coloana)`
Incarca o imagine alb-negru dintr-un fisier binar.
- Aloca memorie pentru matrice.
- Citeste valorile pixelilor ca octeti si le converteste in intregi pentru stocare.

#### 5. `void load_binary_rgb_matrix(FILE *file, pixel ***imagine_rgb, int linie, int coloana)`
Incarca o imagine color (RGB) dintr-un fisier binar.
- Aloca memorie pentru matricea de pixeli.
- Citeste tripletele de octeti si le converteste in componentele R, G, B ale fiecarui pixel.

#### 6. `void LOAD(...)`
Gestioneaza incarcarea unei imagini in functie de tipul acesteia (text sau binar, alb-negru sau RGB).
- Daca exista deja o imagine incarcata, elibereaza memoria acesteia.
- Deschide fisierul specificat si citeste headerul pentru a determina tipul imaginii.
- Apeleaza functiile corespunzatoare pentru incarcarea imaginii in functie de tipul detectat.

#### 8. `void SELECT(...)`
Permite selectarea unei regiuni dreptunghiulare din imagine.
- Verifica daca imaginea este incarcata.
- Corecteaza coordonatele daca acestea sunt introduse in ordine inversa.
- Verifica validitatea coordonatelor si, daca sunt valide, le salveaza.

#### 9. `void SELECT_ALL(...)`
Selecteaza intreaga imagine.
- Seteaza coordonatele selectiei la dimensiunile imaginii.
- Mai exista o functie auxiliara `void SELECT_ALL2(...)` care are aceiasi functionalitate doar ca nu afiseaza nimic.Este folosita pentru a selecta valorile lui x1,x2,y1,y2 in umrma unui LOAD .

#### 10. `void CROP(...)`
Decupeaza imaginea la regiunea selectata.
- Verifica daca exista o imagine incarcata.
- Creeaza o noua matrice de dimensiuni mai mici, copiaza valorile pixelilor din regiunea selectata si elibereaza memoria vechii matrice.

#### 11. `void save_binary(...)`
Salveaza o imagine in format binar.
- Scrie valorile pixelilor ca octeti intr-un fisier binar.

#### 12. `void save_ascii(...)`
Salveaza o imagine in format text (ASCII).
- Scrie valorile pixelilor intr-un fisier text, folosind spatii intre valori.

#### 13. `void SAVE(...)`
Gestioneaza salvarea unei imagini in functie de modul specificat (`ascii` sau `binar`).
- Deschide fisierul in modul corespunzator si apeleaza functia de salvare potrivita.

#### 14. `void choose(char op[FNMAX], double ker[3][3])`
Functia choose selecteaza nucleul (kernel) corespunzator filtrului specificat de utilizator.
- Daca utilizatorul alege unul dintre filtrele predefinite (EDGE, SHARPEN, BLUR, GAUSSIAN_BLUR), functia copiaza valorile nucleului corespunzator intr-o matrice 3x3 folosind memcpy.
- Nucleul este utilizat ulterior de functia APPLY pentru a calcula noile valori ale pixelilor in functie de filtrul aplicat.

#### 15. `int clamp(int value)`
Functia clamp limiteaza valorile pixelilor intre 0 si 255.
- Daca valoarea calculata depaseste 255, aceasta este setata la 255.
- Daca valoarea este mai mica decat 0, aceasta este setata la 0.

#### 16. `pixel form(pixel **imagine_rgb, int i, int j, double ker[3][3])`
Functia form calculeaza noua valoare a unui pixel color folosind un nucleu de filtrare.
- Parcurge vecinii pixelului curent intr-o matrice 3x3 si aplica valorile nucleului la componentele R, G si B ale pixelilor vecini.
- Sumele rezultate pentru fiecare componenta sunt rotunjite si limitate intre 0 si 255 folosind functia `clamp`.
- Returneaza pixelul filtrat.

#### 17. `void APPLY(...)`
Aplica un filtru pe regiunea selectata a imaginii.
- Verifica daca exista o imagine incarcata. Daca imaginea este alb-negru, afiseaza un mesaj si iese din functie.
- Verifica validitatea filtrului specificat de utilizator.
- Creeaza o matrice temporara in care sunt stocate valorile filtrate ale pixelilor.
- Foloseste functia `form` pentru a calcula noile valori ale pixelilor din regiunea selectata, evitand marginile imaginii unde aplicarea nucleului ar depasi limitele acesteia.
- Copiaza rezultatele filtrate inapoi in matricea originala.
- Elibereaza memoria matricei temporare si afiseaza un mesaj de confirmare

#### 18. `void EQUALIZE(...)`
Functia aplica egalizarea histogramei pe o imagine alb-negru pentru a imbunatati contrastul.
- Daca nu exista nicio imagine incarcata, se afiseaza un mesaj de eroare.
- Daca imaginea este color (RGB), se afiseaza un mesaj care indica faptul ca functia necesita o imagine alb-negru.
- Creeaza un vector histogram de 256 de elemente pentru a contoriza frecventa fiecarei valori de pixel (intre 0 si 255).
- Parcurge fiecare pixel al imaginii si actualizeaza frecventa corespunzatoare in vectorul de histograma.
- Creeaza un vector f care retine distributia cumulativa a valorilor de pixel.
- Distribuie fiecare valoare de pixel pe intervalul [0, 255] proportional cu frecventa cumulativa.
- Parcurge imaginea si inlocuieste fiecare pixel cu noua valoare calculata folosind distributia cumulativa.

#### 19. `void HISTOGRAM(...)`
Functia afiseaza histograma unei imagini alb-negru, folosind un numar specificat de intervale (bins).
- Daca nu exista nicio imagine incarcata, se afiseaza un mesaj de eroare.
- Daca imaginea este color (RGB), se afiseaza un mesaj care indica faptul ca functia necesita o imagine alb-negru.
- Daca numarul de intervale (bins) nu este o putere a lui 2 sau este in afara intervalului [2, 256], se afiseaza un mesaj de eroare.
- Imparte intervalul de valori [0, 255] in y intervale egale.
- Parcurge imaginea si actualizeaza frecventa valorilor de pixel in intervalul corespunzator.
- Determina frecventa maxima si normalizeaza valorile pentru a le reprezenta grafic cu caractere *.
- Afiseaza fiecare interval cu un numar proportional de caractere *.

#### 20. `void rotate_right_pat(...)`
Functia rotate_right_pat roteste cu 90 de grade in sens orar o regiune patratica selectata din imagine.

##### Pentru imaginile alb-negru:
- Aloca memorie pentru o matrice temporara rot de dimensiune n x n.
- Copiaza valorile pixelilor din regiunea selectata in matricea temporara, aplicand rotirea prin rearanjarea pixelilor.
- Copiaza valorile rotite inapoi in imaginea originala.
- Elibereaza memoria matricei temporare.

##### Pentru imaginile color (RGB):
- Procedeaza similar, dar foloseste o matrice temporara de tip pixel pentru a stoca tripletele de valori R, G si B ale pixelilor.

#### 21. `void rotate_left_pat(...)`
Functia `rotate_left_pat` roteste cu 90 de grade in sens antiorar o regiune patratica selectata din imagine.
- Urmeaza acelasi principiu ca `void rotate_right_pat(...)` doar ca in sens opus.

#### 22. `void rotate_entire_matrix_right(...)`
Functia `rotate_entire_matrix_right` roteste intreaga imagine cu 90 de grade in sens orar.

##### Pentru imaginile alb-negru:
- Aloca memorie pentru o noua matrice rot de dimensiune inversata (coloana x linie).
- Copiaza valorile pixelilor in matricea noua, aplicand rotirea.
- Elibereaza memoria matricei vechi si actualizeaza pointerul imaginii cu matricea rotita.

##### Pentru imaginile color (RGB):
- Procedeaza similar, dar foloseste o matrice temporara de tip pixel.

#### 23. `void rotate_entire_matrix_left(...)`
Functia `rotate_entire_matrix_left` roteste intreaga imagine cu 90 de grade in sens antiorar.
- Urmeaza acelasi principiu ca `void rotate_entire_matrix_right(...)` doar ca in sens opus.

#### 24. `void ROTATE(...)`
Functia este interfata principala pentru rotirea imaginilor si gestioneaza rotirea in functie de unghiul specificat de utilizator.
- Daca nu exista nicio imagine incarcata, se afiseaza un mesaj de eroare.
- Daca unghiul specificat nu este un multiplu de 90, se afiseaza un mesaj de eroare.
- Daca regiunea selectata nu este patratica si nu reprezinta intreaga imagine, se afiseaza un mesaj de eroare.
- Calculeaza numarul de pasi necesari pentru a efectua rotirea completa, impartind unghiul specificat la 90.
- Daca rotirea se aplica unei regiuni patratice, apeleaza functiile rotate_right_pat sau rotate_left_pat, in functie de sensul rotirii.
- Daca rotirea se aplica intregii imagini, apeleaza functiile rotate_entire_matrix_right sau rotate_entire_matrix_left.
- Actualizeaza coordonatele selectiei pentru a reflecta noua orientare a imaginii dupa rotire.


#### 25. `void handle_*` functii auxiliare
Aceste functii (`handle_load`, `handle_select`, `handle_save`, etc.) gestioneaza comenzile introduse de utilizator si apeleaza functiile corespunzatoare pentru a executa actiunile dorite.

#### 26. `int main()`
Functia principala care ruleaza un loop infinit pentru a citi si executa comenzile introduse de utilizator.
- Citeste comanda introdusa.
- Verifica prefixul comenzii pentru a determina actiunea dorita si apeleaza functiile auxiliare corespunzatoare.
- Permite urmatoarele comenzi:
  - `LOAD <fisier>` - Incarca o imagine.
  - `SELECT <x1> <y1> <x2> <y2>` - Selecteaza o regiune.
  - `SELECT ALL` - Selecteaza intreaga imagine.
  - `CROP` - Decupeaza imaginea la regiunea selectata.
  - `APPLY <filtru>` - Aplica un filtru pe regiunea selectata.
  - `EQUALIZE` - Egalizeaza histograma imaginii.
  - `HISTOGRAM <x> <y>` - Afiseaza histograma cu un numar specificat de intervale.
  - `ROTATE <unghi>` - Roteste imaginea cu un unghi specificat.
  - `SAVE <fisier> [ascii]` - Salveaza imaginea.
  - `EXIT` - Iese din program si elibereaza memoria.



