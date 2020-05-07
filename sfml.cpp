#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

//Essa struct node serve para resumir a estrutura básica
//das listas encadeadas, utilizadas na classe linked_list
struct node {
    char data;
    int char_number;
    node *prev, *next;
};

//Essa é a classe que cuida da lista encadeada que guarda os textos da aplicação
class Linked_list {
private:
    node *head,*tail;
public:
  int charNumber = 1;
  int lineNumber = 0;

    Linked_list() {
        head = NULL;
        tail = NULL;
    };

    //Esse método é o resposável por remover nós, 
    void remove_last_node(){
      charNumber -= 1;
      tail = tail->prev;
      tail->next = NULL;
    }
    
    //O nome desse método é bem auto descritivo. Eu chamo cada caracter na minha lista encadeada de "node"
    //E esse é o método responsável por lidar com a adição de novos nós
    void add_node(char n) {
          //delete
          if(n == 127 || n == 8){
            remove_last_node();
            return;
          }
          
          if(charNumber % 80 == 0){
            charNumber = 0;
            
            node *space = new node;
            space->data = '\n';
            
            space->prev = tail;
            tail->next = space;
            tail = tail->next;
            lineNumber += 1;
          }
          charNumber += 1;

          //enter
          if(n == 13){
            n = '\n';
          }

          node *tmp = new node;
          tmp->data = n;
          tmp->next = NULL;

          if(head == NULL) {
              head = tmp;
              tail = tmp;
          } else {
              tmp->prev = tail;
              tail->next = tmp;
              tail = tail->next;
          }

    };

    //método imprime todos os caracteres contidos na lista encadeada
    void print() {
      tail = head;
      while(tail != NULL){
        cout << tail->data;
        tail = tail->next;
      }
      cout << endl;
    }

    //método que guarda todos os caracteres contidos na lista
    //dentro de uma string e a retorna
    string get_text() {
      string output = "";
      tail = head;
      while(tail != NULL){
        output.push_back(tail->data);
        tail = tail->next;
      }
      output.push_back('\n');
      return output;
    };
};


int main () {
  //Esse método é nativo da biblioteca SFML utilizada para garantir à abertura de uma janela customizável ao invés
  //de ter de usar o console, como é padrão do c++
  sf::RenderWindow window(sf::VideoMode(800, 512), "Editor de texto",  sf::Style::Close | sf::Style::Resize );
  window.setVerticalSyncEnabled(true);
  sf::Color backgroundColor = sf::Color(40, 42, 54);

  //Método para carregar a fonte
  sf::Font font;

  //Configuração de mensagem de erro para caso algo dê errado no carregamento da fonte
  if(!font.loadFromFile("fonts/DejaVuSansMono.ttf")){
    cout << "Error loading pause" << endl;
  };

  sf::Text text;
  sf::Text marker;

  
  Linked_list *list = new Linked_list;

  


  //selecionando as fontes
  text.setFont( font );
  marker.setFont( font );

  string texto = "";
  while(window.isOpen()){
    //allows the user to move the window
    sf::Event evnt;
    

    system("stty raw");
    while(window.pollEvent(evnt)){
      switch(evnt.type){
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::TextEntered:
          if(evnt.text.unicode < 128){
            //input handling
            //Basicamente e o usuário digitar um backspace (ASCII 08)
            //O texto é removido
            if(evnt.text.unicode == 8){
              texto.pop_back();
              list->remove_last_node();
            } 
            //Em todos os outros casos, que não o de exclusão, eu adiciono o caracter à
            //Lista de dados
            else {
              if(texto.length() % 80 == 0){
                texto.push_back('\n');  
              }
              list->add_node(evnt.text.unicode);
              texto.push_back(evnt.text.unicode);
            }
            
            text.setString(texto);
            marker.setString('|');
          }
      }
    }
  window.clear(backgroundColor);
  text.setLetterSpacing(1.f);
  window.draw(text);
  
  marker.setPosition(text.getGlobalBounds().width, text.getGlobalBounds().height);
  marker.setCharacterSize(16);
  window.draw(marker);
  
  text.setCharacterSize(16);
  window.display();
  }

  return 0;
}