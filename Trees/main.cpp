/**
 * @author Albert Villanueva Kosoy Grup C
*/

/* EXERCICI 5 */
/*
 __________________________________________________________________
|                       |                      |                   | 
| OPERATION             | BST TREE             | AVL TREE          | 
|_______________________|______________________|___________________|
|                       |                      |                   | 
| SMALL TREE INSERTION  |  6 milliseconds      |  3 milliseconds   |
|_______________________|______________________|___________________|
|                       |                      |                   | 
| LARGE TREE INSERTION  |  131 milliseconds    |  38 milliseconds  |
|_______________________|______________________|___________________|
|                       |                      |                   | 
| SMALL TREE SEARCH     |  0 milliseconds      |  0 milliseconds   |
|_______________________|______________________|___________________|
|                       |                      |                   | 
| LARGE TREE SEARCH     |  0 milliseconds      |  0 milliseconds   |
|_______________________|______________________|___________________|

BST TREE

In small trees, insertion is faster than in large trees and search is equally efficient.
Insert operations take longer because BST operations have O(log2 n) in the best case 
and O(n) in the worst case.

The time for search operations is not recorded in milliseconds.

AVL TREE

In small trees, insertion time is less than in large trees and search is equally efficient.
Compared to the BST tree, the time for insert operations in files of different sizes in the AVL tree
is less because the complexity of its operations is O(log2 n).

The time for search operations is not recorded in milliseconds.

Differences between the two trees are in the file ArbreAVL.h
*/

#include <iostream>
#include "NodeTree.h"
#include "BST.h"
#include "Artist.h"
#include "CercadorArtistes.h"
#include "ABT.h"
#include "CercadorArtistesAVL.h"
#include <chrono>
#include <list>
using namespace std;


/**
 * Prova de l'exercici 1 amb enters (BST)
*/
void casDeProvaExercici1() {
    cout << " ------------- cas de prova exercici 1 ----------- " << endl;
    BST<int, int> tree1;
    int testKeys[] = {2, 0, 8, 45, 76, 5, 6, 3, 40};
    int testValues[] = {5, 5, 1, 88, 99, 6, 12, 9, 11};
    for (int i = 0; i < 9; i++) {
        tree1.insereix(testKeys[i], testValues[i]);
    }

    cout << "preordre={ "; tree1.imprimeixPreordre(); cout << "}" << endl;
    cout << "inordre={ "; tree1.imprimeixInordre(); cout << "}" << endl;
    cout << "postordre={ "; tree1.imprimeixPostordre(); cout << "}" << endl;
    cout << " Conte clau 45 " << tree1.conteClau(45) << endl;
    cout << " Conte clau 37 " << tree1.conteClau(37) << endl;
    cout << " Conte clau 76 " << tree1.conteClau(76) << endl;
    cout << " Conte clau 2 " << tree1.conteClau(2) << endl << endl;

    BST<int, int> tree2(tree1);
    cout << "postordre copia ={ "; tree2.imprimeixPostordre(); cout << "}" << endl;
    cout << "preordre copia ={ "; tree2.imprimeixPreordre(); cout << "}" << endl << endl;

    tree2.arbreMirall();
    cout << "preordre arbre mirall 1 ={ "; tree2.imprimeixPreordre(); cout << "}" << endl;
    tree2.arbreMirall();
    cout << "preordre arbre mirall 2 ={ "; tree2.imprimeixPreordre(); cout << "}" << endl << endl;

    list<NodeTree<int, int>*> llista = tree1.obteFullesArbre(true);
    cout << "obteFullesArbre(esq)={ ";
    for (NodeTree<int, int>* n : llista) {
        cout << n->getKey() << " ";
    }
    cout << "}" << endl << endl;

    list<NodeTree<int, int>*> llista2 = tree1.obteFullesArbre(false);
    cout << "obteFullesArbre(dreta)={ ";
    for (NodeTree<int, int>* n : llista2) {
        cout << n->getKey() << " ";
    }
    cout << "}" << endl << endl;
    cout << " ------------- FI cas de prova exercici 1 ----------- " << endl;
}
/**
 * Cas de prova amb enters de l'exercici 2 (Cercador BST)
*/
void casDeProvaExercici2() {
 cout << " ------------- cas de prova prova exercici 2 ----------- " <<
endl;

 // Crear una instància del cercador d'artistes
 CercadorArtistes cercador;
 // Afegir artistes des d'un fitxer
 try {
    // Poso la ruta completa perquè no s'obre amb el nom
 cercador.afegeixArtistes("Data/spanishArtists.csv");
 } catch (const invalid_argument& e) {
 cerr << "Error: " << e.what() << endl;
 return;
 }
 // Mostrar l'altura de l'arbre BST
 cout << "Altura de l'arbre BST: " << cercador.height() << endl;
 // Mostrar l'artista amb un ID específic
 cout << "Artista amb ID 1370: " << cercador.mostrarArtista(1370) << endl;
 // Comprovar si un artista amb un ID específic existeix
 int artistID = 4893;
 if (cercador.buscarArtista(artistID)) {
 cout << "L'artista amb ID " << artistID << " existeix." << endl;
 } else {
 cout << "L'artista amb ID " << artistID << " no existeix." << endl;
 }
 // Mostrar l'arbre BST ordenat
 cout << "Arbre BST ordenat:" << endl;
 cercador.imprimirOrdenat(); /*imprimirOrdenat()*/
// Quants artistes amb més playcount
 cout << "Quants artistes amb mes de 100000 reproduccions :" << endl;
 cout << cercador.buscarRecompteArtistes(100000) << endl;
 // Obtenir tots els artistes d'un estil específic
 string estil = "folk";
 list<int> artistesRock = cercador.obtenirArtistesPerEstil(estil);
 cout << "Artistes d'estil Rock (IDs): ";
 for (int id : artistesRock) {
 cout << id << " ";
 }
 cout << endl;
 cout << " ------------- Fi cas de prova prova exercici 2 ----------- " <<
endl;
}

/**
 * Menu de l'exercici 2 (Cercador BST)
*/
void mainExercici2(){
    CercadorArtistes cercador;
    int option;

    do {
        cout << " ------------- Menu Exercici 2 ----------- " << endl;
        cout << "\nMenú:\n";
        cout << "1. Entra dades amb un fitxer.\n";
        cout << "2. Mostrar l’arbre segons l’ID en ordre creixent.\n";
        cout << "3. Buscar nombre elements de \"cercaArtists.csv\" en el cercador.\n";
        cout << "4. Visualitzar per pantalla la profunditat de l'arbre.\n";
        cout << "5. Buscar artista per ID.\n";
        cout << "6. Mostarar artista per ID.\n";
        cout << "7. Buscar recompte d’artistes que tenen més playcount.\n";
        cout << "8. Obtindre tots els artistes d'un estil específic.\n";
        cout << "9. Sortir.\n";
        cout << "Introduïu la vostra opció: ";
        cin >> option;

        switch (option) {
            
            case 1:{
            /**
             * Entrar les dades d'un fitxer
            */
                cout << "Quin fitxer vols (P/G)?";
                string tamany;
                cin >> tamany;

                chrono::steady_clock::time_point begin = chrono::steady_clock::now();
                try{
                    if(tamany == "p" || tamany == "P"){ // Faig servir la ruta completa de l'arxiu perquè no em funciona amb el nom
                        cercador.afegeixArtistes("Data/spanishArtists.csv");
                    }
                    else if(tamany == "g" || tamany == "G"){
                        cercador.afegeixArtistes("Data/usArtists.csv");
                    }
                    else{
                        cout<< "Introdueix \"p\" o \"g\" per escullir entre un arxiu petit o gran: ";
                    }
                }
                catch(const exception& e){
                    cerr << e.what() << '\n';
                }
                cout<< "Arxiu afegit." <<endl;
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                cout << "Temps transcorregut: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms." << endl;
                break;
            }
            case 2:{
            /**
             * Imprimir l'arbre inordre amb l'opció de continuar cada 40 artistes
            */
                cercador.imprimirOrdenat();
                break;
            }
            case 3:{
            /**
             * Comptar el nombre d'artistes de cercaArtists.csv presents en el arxiu escollit 
            */
                ifstream fitxer; fitxer.open("Data/cercaArtists.csv");
                int comptador = 0;

                if (!fitxer.is_open()) {
                    cerr << "Error: Unable to open file cercaArtists.csv "<< endl;
                }
                chrono::steady_clock::time_point begin = chrono::steady_clock::now();
                string line, header;
                getline(fitxer,header, '\n');
                while (getline(fitxer, line)) {
                    if (line.empty()) {
                        continue; 
                    }

                    istringstream ss(line);
                    string id;

                    getline(ss, id, ',');
                    int ID = stoi(id);
                    if(cercador.buscarArtista(ID)) comptador += 1;
                }
                fitxer.close();
                cout << "Nombre d'artistes de \"cercaArtists.csv\" trobats en l'arxiu obert: " << comptador << endl;
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                cout << "Temps transcorregut: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms." << endl;
                break;
                
                }
            case 4:{
            /**
             * Mostra l'alçada de l'arbre 
            */
                cout << "Alçada de l'arbre: " << cercador.height() << "\n";
                break;
            }
            case 5:{
            /**
             * Busca si l'artista es troba en l'arxiu mitjançant l'ID
            */
                int ArtistaID;
                cout << "Introduïu l'ID de l'artista: ";
                cin >> ArtistaID;
                if (cercador.buscarArtista(ArtistaID)) {
                    cout << "Artista trobat\n";
                } else {
                    cout << "Artista no trobat\n";
                }
                break;
                }
            case 6:
            /**
             * Mostra l'arxiu que té l'ID entrat per pantalla
            */
            {int ArtistaID;
                cout << "Introduïu l'ID de l'artista: ";
                cin >> ArtistaID;
                cout << cercador.mostrarArtista(ArtistaID);
                break;
            } 
            case 7:{
            /**
             * Mostra els artistes amb un nombre de reproduccions igual o major que el nombre entrat per pantalla
            */
                int playcount;
                cout << "Introduïu el nombre de reproduccions: ";
                cin >> playcount;
                cout << "Nombre d'artistes amb més de " << playcount << " reproduccions: " << cercador.buscarRecompteArtistes(playcount) << "\n";
                break;
                }
            case 8:{
            /**
             * Mostra per pantalla una llista d'artistes que tenen associat l'estil intrduït
            */
                string estil;
                cout << "Introduïu l'estil: ";
                cin >> estil;
                cout << "Artistes amb estil " << estil << ":\n";
                for (int id : cercador.obtenirArtistesPerEstil(estil)) {
                    cout << id << "\n";
                }
                cout<<endl;
                break;
                }
            case 9:{
                /**
                 * Opció per sortir del programa
                */
                cout << "Sortint...\n";
                break;
            }
            default:{
                cout << "Opció invàlida. Si us plau, torneu-ho a intentar.\n";
                break;
            }
        }
    } while (option!= 9);
}


/**
 * Prova de l'exercici 3 amb enters (AVL)
*/
void casDeProvaExercici3_2023_2024() {
    cout << " ------------- cas de prova exercici 3 ----------- " << endl;
    ABT<int, int> tree1;
    int testKeys[] = {2, 0, 8, 45, 76, 5, 6, 3, 40};
    int testValues[] = {5, 5, 1, 88, 99, 6, 12, 9, 11};
    for (int i = 0; i < 9; i++) {
        tree1.insereixAVL(testKeys[i], testValues[i]);
    }

    cout << "preordre={ "; tree1.imprimeixPreordre(); cout << "}" << endl;
    cout << "inordre={ "; tree1.imprimeixInordre(); cout << "}" << endl;
    cout << "postordre={ "; tree1.imprimeixPostordre(); cout << "}" << endl;
    cout << " Conte clau 45 " << tree1.conteClau(45) << endl;
    cout << " Conte clau 37 " << tree1.conteClau(37) << endl;
    cout << " Conte clau 76 " << tree1.conteClau(76) << endl;
    cout << " Conte clau 2 " << tree1.conteClau(2) << endl << endl;

    ABT<int, int> tree2(tree1);
    cout << "postordre copia ={ "; tree2.imprimeixPostordre(); cout << "}" << endl;
    cout << "preordre copia ={ "; tree2.imprimeixPreordre(); cout << "}" << endl << endl;

    tree2.arbreMirall();
    cout << "preordre arbre mirall 1 ={ "; tree2.imprimeixPreordre(); cout << "}" << endl;
    tree2.arbreMirall();
    cout << "preordre arbre mirall 2 ={ "; tree2.imprimeixPreordre(); cout << "}" << endl << endl;

    list<NodeTree<int, int>*> llista = tree1.obteFullesArbre(true);
    cout << "obteFullesArbre(esq)={ ";
    for (NodeTree<int, int>* n : llista) {
        cout << n->getKey() << " ";
    }
    cout << "}" << endl << endl;

    list<NodeTree<int, int>*> llista2 = tree1.obteFullesArbre(false);
    cout << "obteFullesArbre(dreta)={ ";
    for (NodeTree<int, int>* n : llista2) {
        cout << n->getKey() << " ";
    }
    cout << "}" << endl << endl;
    cout << " ------------- FI cas de prova exercici 3 ----------- " << endl;
}
/**
 * Prova de l'exercici 4 amb enters (Cercador AVL)
*/
void casDeProvaExercici4() {
    cout << " ------------- cas de prova prova exercici 4 ----------- " <<
    endl;

    // Crear una instància del cercador d'artistes
    CercadorArtistesAVL cercadorAVL;
    // Afegir artistes des d'un fitxer
    try {
        cercadorAVL.afegeixArtistes("Data/spanishArtists.csv");
    } catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        return;
    }
    // Mostrar l'altura de l'arbre BST
    cout << "Altura de l'arbre AVL: " << cercadorAVL.height() << endl;
    // Mostrar l'artista amb un ID específic
    cout << "Artista amb ID 1370: " << cercadorAVL.mostrarArtista(1370) << endl;
    // Comprovar si un artista amb un ID específic existeix
    int artistID = 4893;
    if (cercadorAVL.buscarArtista(artistID)) {
        cout << "L'artista amb ID " << artistID << " existeix." << endl;
    } else {
        cout << "L'artista amb ID " << artistID << " no existeix." << endl;
    }
    // Mostrar l'arbre BST ordenat
    cout << "Arbre AVL ordenat:" << endl;
    cercadorAVL.imprimirOrdenat(); /* afegir al TAD */
    // Quants artistes amb més playcount
    cout << "Quants artistes amb mes de 100000 reproduccions :" << endl;
    cout << cercadorAVL.buscarRecompteArtistes(100000) << endl;
    // Obtenir tots els artistes d'un estil específic
    string estil = "folk";
    list<int> artistesRock = cercadorAVL.obtenirArtistesPerEstil(estil);
    cout << "Artistes d'estil Rock (IDs): ";
    for (int id : artistesRock) {
    cout << id << " ";
    }
    cout << endl;
    cout << " ------------- Fi cas de prova prova exercici 4 ----------- " <<
    endl;
}

/**
 * Menu de l'exercici 4 (Cercador AVL)
*/
void mainExercici4(){
    CercadorArtistesAVL cercador;
    int option;

    do {
        cout << " ------------- Menu Exercici 4 ----------- " << endl;
        cout << "\nMenú:\n";
        cout << "1. Entra dades amb un fitxer.\n";
        cout << "2. Mostrar l’arbre segons l’ID en ordre creixent.\n";
        cout << "3. Buscar nombre elements de \"cercaArtists.csv\" en el cercador.\n";
        cout << "4. Visualitzar per pantalla la profunditat de l'arbre.\n";
        cout << "5. Buscar artista per ID.\n";
        cout << "6. Mostarar artista per ID.\n";
        cout << "7. Buscar recompte d’artistes que tenen més playcount.\n";
        cout << "8. Obtindre tots els artistes d'un estil específic.\n";
        cout << "9. Sortir.\n";
        cout << "Introduïu la vostra opció: ";
        cin >> option;

        switch (option) {
            
            case 1:{
            /**
             * Entrar les dades d'un fitxer
            */
                cout << "Quin fitxer vols (P/G)?";
                string tamany;
                cin >> tamany;

                chrono::steady_clock::time_point begin = chrono::steady_clock::now();
                try{
                    if(tamany == "p" || tamany == "P"){ // Faig servir la ruta completa de l'arxiu perquè no em funciona amb el nom
                        cercador.afegeixArtistes("Data/spanishArtists.csv");
                    }
                    else if(tamany == "g" || tamany == "G"){
                        cercador.afegeixArtistes("Data/usArtists.csv");
                    }
                    else{
                        cout<< "Introdueix \"p\" o \"g\" per escullir entre un arxiu petit o gran: ";
                    }
                }
                catch(const exception& e){
                    cerr << e.what() << '\n';
                }
                cout<< "Arxiu afegit." <<endl;
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                cout << "Temps transcorregut: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms." << endl;
                break;
            }
            case 2:{
            /**
             * Imprimir l'arbre inordre amb l'opció de continuar cada 40 artistes
            */
                cercador.imprimirOrdenat();
                break;
            }
            case 3:{
            /**
             * Comptar el nombre d'artistes de cercaArtists.csv presents en el arxiu escollit 
            */
                ifstream fitxer; fitxer.open("Data/cercaArtists.csv");
                int comptador = 0;

                if (!fitxer.is_open()) {
                    cerr << "Error: Unable to open file cercaArtists.csv "<< endl;
                }
                chrono::steady_clock::time_point begin = chrono::steady_clock::now();
                string line, header;
                getline(fitxer,header, '\n');
                while (getline(fitxer, line)) {
                    if (line.empty()) {
                        continue; 
                    }

                    istringstream ss(line);
                    string id;

                    getline(ss, id, ',');
                    int ID = stoi(id);
                    if(cercador.buscarArtista(ID)) comptador += 1;
                }
                fitxer.close();
                cout << "Nombre d'artistes de \"cercaArtists.csv\" trobats en l'arxiu obert: " << comptador << endl;
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                cout << "Temps transcorregut: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms." << endl;
                break;
                
                }
            case 4:{
            /**
             * Mostra l'alçada de l'arbre 
            */
                cout << "Alçada de l'arbre: " << cercador.height() << "\n";
                break;
            }
            case 5:{
            /**
             * Busca si l'artista es troba en l'arxiu mitjançant l'ID
            */
                int ArtistaID;
                cout << "Introduïu l'ID de l'artista: ";
                cin >> ArtistaID;
                if (cercador.buscarArtista(ArtistaID)) {
                    cout << "Artista trobat\n";
                } else {
                    cout << "Artista no trobat\n";
                }
                break;
                }
            case 6:
            /**
             * Mostra l'arxiu que té l'ID entrat per pantalla
            */
            {int ArtistaID;
                cout << "Introduïu l'ID de l'artista: ";
                cin >> ArtistaID;
                cout << cercador.mostrarArtista(ArtistaID);
                break;
            } 
            case 7:{
            /**
             * Mostra els artistes amb un nombre de reproduccions igual o major que el nombre entrat per pantalla
            */
                int playcount;
                cout << "Introduïu el nombre de reproduccions: ";
                cin >> playcount;
                cout << "Nombre d'artistes amb més de " << playcount << " reproduccions: " << cercador.buscarRecompteArtistes(playcount) << "\n";
                break;
                }
            case 8:{
            /**
             * Mostra per pantalla una llista d'artistes que tenen associat l'estil intrduït
            */
                string estil;
                cout << "Introduïu l'estil: ";
                cin >> estil;
                cout << "Artistes amb estil " << estil << ":\n";
                for (int id : cercador.obtenirArtistesPerEstil(estil)) {
                    cout << id << "\n";
                }
                cout<<endl;
                break;
                }
            case 9:{
                /**
                 * Opció per sortir del programa
                */
                cout << "Sortint...\n";
                break;
            }
            default:{
                cout << "Opció invàlida. Si us plau, torneu-ho a intentar.\n";
                break;
            }
        }
    } while (option!= 9);
}

int main(){
    /* Exercici1 */
    casDeProvaExercici1(); 

    /* Exercici 2 */
    casDeProvaExercici2();
    mainExercici2();

    /* Exercici 3 */
    casDeProvaExercici3_2023_2024();

    /* Exercici4 */
    casDeProvaExercici4();
    mainExercici4();
}