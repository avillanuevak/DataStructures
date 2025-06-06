#ifndef CERCADORARTISTES_H
#define CERCADORARTISTES_H
#include "BST.h"
#include "Artist.h"
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
using namespace std;

class CercadorArtistes: protected BST<int, Artist>{
 public:
 CercadorArtistes();

 void afegeixArtistes(string filename);
 void insereixArtista(int ArtistaID, string name, string gender, string country,
 string styles, int counts);
 string mostrarArtista(int ArtistaID)const;
 bool buscarArtista(int ArtistaID);
 int buscarRecompteArtistes(int playcount);
 int height() const;
 list<int> obtenirArtistesPerEstil(const string estil);
 
 void imprimirOrdenat()const;

 private:
 void mostrarArtistesInordreAux(NodeTree<int,Artist>* n, int &counter);
 void auxRecompte(NodeTree<int, Artist>* n, int& num, int playcount);
 void auxEstil(NodeTree<int, Artist>* n, string estil, list<int>& llista);
 void auxImprimirOrdenat(NodeTree<int,Artist>* n, int num) const;

};

CercadorArtistes::CercadorArtistes():BST<int, Artist> (){}

/**
 * Insereix l'artista cridant a la funció d'insereix de l'arbre BST
*/
void CercadorArtistes::insereixArtista(int ArtistaID, string name, string gender, string country, string styles, int counts){
    Artist a(ArtistaID, name, gender, country, styles, counts);
    BST<int,Artist>::insereix(ArtistaID, a);
}
/**
 * Afageix els artistes des d'un arxiu
*/
void CercadorArtistes::afegeixArtistes(std::string filename) {
        std::ifstream fitxer(filename);
        if (!fitxer.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
        }

        std::string line, header;
        getline(fitxer,header,'\n');
        while (std::getline(fitxer, line)) {
            if (line.empty()) {
                continue; 
            }

            std::istringstream ss(line);
            string id, name, gender, country, styles, playcount;

            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, gender, ',');
            std::getline(ss, country, ',');
            std::getline(ss, styles, ',');
            std::getline(ss, playcount, '\n');

            int artistID = stoi(id);
            int artistPlaycount = stoi(playcount);
            insereixArtista(artistID, name, gender, country, styles, artistPlaycount);
        
        }
        fitxer.close();
    }

/**
 * Mostrar l'artista
 * @return string amb la info del artista
 * */                                                   
string CercadorArtistes::mostrarArtista(int ArtistaID)const{
    return (cercar(ArtistaID)? ArtistaID + "::" + this->valorDe(ArtistaID).toString() + "\n" : "No s'a trobat l'artista");
}
/**
 * Buscar l'artista
 * @return bool si exixteix l'artista
*/
bool CercadorArtistes::buscarArtista(int ArtistaID){
    NodeTree<int, Artist>* node = cercar(ArtistaID);
    if (node == nullptr) {
        return false;
    }
    return true;
}
/**
 * Busca el recompte d'artistes amb un recompte major o igual
 * @return recompte d'artistes
*/
int CercadorArtistes::buscarRecompteArtistes(int playcount){
    int num = 0;
    auxRecompte(this->arrel, num, playcount);
    return num;
}

/**
 * Auxiliar void a buscarRecompteArtistes
*/
void CercadorArtistes::auxRecompte(NodeTree<int, Artist>* n, int& num, int playcount){
    if (n->getValue().getPlaycount() >= playcount){
        num++;
    }
    if (n->teEsquerra()) auxRecompte(n->getLeft(), num, playcount);
    if (n->teDreta()) auxRecompte(n->getRight(), num, playcount);
}

/**
 * Mètode que retorna l'alçada de l'arbre BST cridant a la funció de la classe BST
 * @return int altura de l'arbre BST
*/
int CercadorArtistes::height() const{
    return this->BST<int, Artist>::altura();
}

/**
 * Mètodes Obtenir artistes per estil
 * @return list<int> artistes amb l'estil entrat
*/
list<int> CercadorArtistes::obtenirArtistesPerEstil(const string estil){
    list<int> llista;
    if(!this->buida()){
        auxEstil(this->arrel, estil, llista);
    }
    return llista;
}

void CercadorArtistes::auxEstil(NodeTree<int, Artist>* n, string estil, list<int>& llista){
    if(n != nullptr){
    if (n->getValue().getStyles().find("|"+estil) != std::string::npos
        || n->getValue().getStyles().find(estil+",") != std::string::npos
        || n->getValue().getStyles().find(estil+"|") != std::string::npos){
        llista.push_back(n->getKey());
    }
    if (n->teEsquerra()) auxEstil(n->getLeft(), estil, llista);
    if (n->teDreta()) auxEstil(n->getRight(), estil, llista);
    }
}

/**
 * Mètodes per Imprimir ordenat per pantalla amb limitació de 40 elements
*/
void CercadorArtistes::imprimirOrdenat() const{
    if (this->arrel) auxImprimirOrdenat(this->arrel, 0);
}

void CercadorArtistes::auxImprimirOrdenat(NodeTree<int,Artist>* n, int num) const{
    if (n->teEsquerra()){
        auxImprimirOrdenat(n->getLeft(), num);
    }
    cout << n->getKey() << "::" << n->getValue().toString() << "\n";
    num++;
    if (num % 40 == 0){
        char c;
        do{
            cout << "\nVols continuar? (s/n) "; cin >> c;
            c = tolower(c);
        }while (c != 'n' && c!='s');
        if (c == 'n') return;
    }
    if (n->teDreta()){
        auxImprimirOrdenat(n->getRight(), num);
    }
}

#endif