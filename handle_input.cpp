#include <iostream>
#include <string>

using namespace std;

void teste () {
  std::cout << "Meu deus vamo lá" << std::endl;
};

struct node {
    char data;
    node *prev, *next;
};

class Linked_list {
private:
    node *head,*tail;
public:
    Linked_list() {
        head = NULL;
        tail = NULL;
    };

    void remove_last_node(){
      tail = tail->prev;
      tail->next = NULL;
    }
    
    void add_node() {
        //This is needed because hence linux doesn't support conio.h
        //So i needed a way to get user input without having to wait for the enter key press
        system("stty raw");

        char n;
        while (n != 27 && n != '.'){
          n = getchar();
          cout << n << endl;
          //delete
          if(n == 127 || n == 8){
            remove_last_node();
          }

          //enter
          if(n == 13){
            n = '\n';
          }


          // system("clear");
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
        }
        system("stty cooked");
    };

    void print() {
      tail = head;
      while(tail != NULL){
        cout << tail->data;
        tail = tail->next;
      }
      cout << endl;
    }

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