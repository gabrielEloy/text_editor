#include <iostream>
#include <cstddef>
#include <fstream> 

using namespace std;

struct node {
    char data;
    int number;
    node *prev, *next;
};

class Char_list  {
private:
    node *head,*tail;
public:
    int char_count;
    bool continue_input;

    Char_list() {
        head = NULL;
        tail = NULL;
        char_count = 1;
        continue_input = true;
    };

    //Esse método é o resposável por remover nós, 
    void remove_last_node(){
      if(char_count > 0){
        char_count -= 1;
        tail = tail->prev;
        tail->next = NULL;
      }
    }
    
    //O nome desse método é bem auto descritivo. Eu chamo cada caracter na minha lista encadeada de "node"
    //E esse é o método responsável por lidar com a adição de novos nós
    void add_node(char n) {
          //delete
          if(n == 127 || n == 8){
            remove_last_node();
            return;
          }
          
          if(char_count >= 5){
            char_count = 0;
            
            node *space = new node;
            space->data = '\n';
            
            space->prev = tail;
            tail->next = space;
            tail = tail->next;
            continue_input = false;
            
          }
          char_count += 1;

          //enter
          // if(n == 13){
          //   n = '\n';
          // }

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

struct line {
  line *prev, *next;
  Char_list char_list;
  int number;
};

class Line_list {
  private:
    line *head,*tail, *current;
  public: 
    int line_number;

    Line_list(){
      head = NULL;
      tail = NULL;
      current = NULL;
      
      line_number = 1;
    }
    
    void create_line(){
      line *tmp = new line;
      tmp->next = NULL;

      if(head == NULL) {
        head = tmp;
        tail = tmp;
        current = tmp;
      } else {
        tmp->prev = tail;
        tail->next = tmp;
        tail = tail->next;
        tail = current;
      }
    }
    
    void add_node(char n){
      cout << n << endl;
        if(tail->char_list.continue_input){
          tail->char_list.add_node(n);
        } else {
          create_line();
        }
    }
};



int main() {
  Line_list content;

  content.add_node('m');
  content.add_node('i');
  content.add_node('s');
  content.add_node('s');
  content.add_node('i');
  content.add_node('s');
  content.add_node('s');
  content.add_node('i');
  content.add_node('p');
  content.add_node('i');
}