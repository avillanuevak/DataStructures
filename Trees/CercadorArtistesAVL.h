/**
 * @author Albert Villanueva Kosoy Grup C
*/

#include <iostream>
#include <list>
#include "BST.h"
#include "ABT.h"
#include "Artist.h"
#include <fstream>

using namespace std;
class CercadorArtistesAVL: public ABT<int, Artist>{
    public:
    CercadorArtistesAVL();

    void afegeixArtistes(string filename); // Recorre un arxiu (0(log n)) i crida a insereix artista (0(log2 n))
    void insereixArtista(int ArtistaID, string name, string gender, string country,
    string styles, int counts); // Crida a insereix -> 0(log2 n) 
    string mostrarArtista(int ArtistaID)const; // 0(n) -> mostra cada artista
    bool buscarArtista(int ArtistaID); //0(n)
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

/**
 * Constructor sense paràmetres de la class CercadorArtistesAVL
*/
CercadorArtistesAVL::CercadorArtistesAVL():ABT<int, Artist>() {}

/**
 * Insereix l'artista cridant a la funció d'insereix de l'arbre AVL
*/
void CercadorArtistesAVL::insereixArtista(int ArtistID, string name, string gender, string country, string styles, int counts){
    Artist a(ArtistID, name, gender, country, styles, counts);
    ABT<int,Artist>::insereixAVL(ArtistID, a);
}

/**
 * Afageix els artistes des d'un arxiu
*/
void CercadorArtistesAVL::afegeixArtistes(std::string filename) {
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

            int artistID = stoi(id), artistPlaycount = stoi(playcount);
            insereixArtista(artistID, name, gender, country, styles, artistPlaycount);
        
        }
        fitxer.close();
    }

/**
 * Mostrar l'artista
 * @return string amb la info del artista
 * */                                                   
string CercadorArtistesAVL::mostrarArtista(int ArtistID)const{
    return (cercar(ArtistID)? ArtistID + "::" + this->valorDe(ArtistID).toString() + "\n" : "No s'a trobat l'artista");
}

/**
 * Buscar l'artista
 * @return bool si exixteix l'artista
*/
bool CercadorArtistesAVL::buscarArtista(int ArtistID){
    NodeTree<int, Artist>* node = cercar(ArtistID);
    if (node == nullptr) {
        return false;
    }
    return true;
}
/**
 * Busca el recompte d'artistes amb un recompte major o igual
 * @return recompte d'artistes
*/
int CercadorArtistesAVL::buscarRecompteArtistes(int playcount){
    int num = 0;
    auxRecompte(this->arrel, num, playcount);
    return num;
}

/**
 * Auxiliar void a buscarRecompteArtistes
*/
void CercadorArtistesAVL::auxRecompte(NodeTree<int, Artist>* n, int& num, int playcount){
    if (n->getValue().getPlaycount() >= playcount){
        num++;
    }
    if (n->teEsquerra()) auxRecompte(n->getLeft(), num, playcount);
    if (n->teDreta()) auxRecompte(n->getRight(), num, playcount);
}

/**
 * Mètode que retorna l'alçada de l'arbre BST cridant a la funció de la classe ArbreBST
 * @return int altura de l'arbre BST
*/
int CercadorArtistesAVL::height() const{
    return this->BST<int, Artist>::altura();
}

/**
 * Mètodes Obtenir artistes per estil
 * @return list<int> artistes amb l'estil entrat
*/
list<int> CercadorArtistesAVL::obtenirArtistesPerEstil(const string estil){
    list<int> llista;
    if(!this->buida()){
        auxEstil(this->arrel, estil, llista);
    }
    return llista;
}

void CercadorArtistesAVL::auxEstil(NodeTree<int, Artist>* n, string estil, list<int>& llista){
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
void CercadorArtistesAVL::imprimirOrdenat() const{
    if (this->arrel) auxImprimirOrdenat(this->arrel, 0);
}

void CercadorArtistesAVL::auxImprimirOrdenat(NodeTree<int,Artist>* n, int num) const{
    if (n->teEsquerra()){
        auxImprimirOrdenat(n->getLeft(), num);
    }
    cout << n->getKey() << " ";
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