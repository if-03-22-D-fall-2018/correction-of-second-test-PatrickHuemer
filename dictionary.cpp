/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			dictionary.cpp
 * Author:			P. Bauer
 * Due Date:		November 25, 2012
 * ----------------------------------------------------------
 * Description:
 * Implementation of dictionary.h.
 * ----------------------------------------------------------
 */
#include "dictionary.h"
#include <stdlib.h>
#include "general.h"
#include <strings.h>

typedef struct NodeImplementation* Node;
struct NodeImplementation{
  const char* word;
  Node next;
};

struct DictionaryImplementation{
  Node head;
  int length;
  bool isCalledByIterating;
};

 Dictionary 	new_dictionary (){
   Dictionary dictionary = (Dictionary)malloc(sizeof(DictionaryImplementation*));
   dictionary->head = 0;
   dictionary->length = 0;
   dictionary->isCalledByIterating=false;
   return dictionary;
 }

 void 	delete_dictionary (Dictionary dictionary){
   Node current = dictionary->head;
   while (current != 0) {
     Node toDelete = current;
     current = current->next;
     sfree(toDelete);
   }
   sfree(dictionary);
 }

 void 	add (Dictionary dict, const char *word){
   if (is_in_dict(dict,word)) return;

   Node current = dict->head;
   Node toAdd = (Node)malloc(sizeof(NodeImplementation));
   toAdd->word = word;
      if (dict->head == 0) {
        dict->head = toAdd;
      }
      else{
        while (current->next != 0) {
          current = current->next;
        }
        current->next = toAdd;
      }
      dict->length++;
      toAdd->next = 0;
 }

 int 	get_size (Dictionary dict){
   return dict->length;
 }

 bool 	is_in_dict (Dictionary dict, const char *word){
   Node current = dict->head;
   while (current != 0) {
     if (strcasecmp(word, current->word)==0) {
       return true;
     }
     current= current->next;
   }
   return false;
 }

 void 	start_iterating (Dictionary dict){
   dict->isCalledByIterating = true;
 }

 bool 	has_next (Dictionary dict){
   if (dict->head != 0&&dict->isCalledByIterating==true) {
     return true;
   }
   return false;
 }

 const char * 	get_next_entry (Dictionary dict){
   if (has_next(dict)==true) {
     const char* word = dict->head->word;
     dict->head = dict->head->next;
     return word;
   }
   return 0;
 }

 void 	insert_sorted (Dictionary dict, const char *word){
   if (is_in_dict(dict,word)) return;

   Node current = dict->head;
   Node toAdd = (Node)malloc(sizeof(NodeImplementation));
   toAdd->word = word;
   toAdd->next = 0; //next auf null um ende zu kennzeichnen

   if (dict->head == 0) {
     dict->head = toAdd;
   }
   else if(strcasecmp(word, dict->head->word)<0){ //neues else if um head im fall zu ändern
     toAdd->next = dict->head;
     dict->head = toAdd;
   }
   else{
     while (current->next != 0 && strcasecmp(word, current->next->word)>0) {
       current=current->next;
     }
     if (current->next == 0) { // if und else getauscht, falsche reihenfolge
       current->next = toAdd;
     }
     else{
       toAdd->next = current->next;
       current->next = toAdd;
     } // if gelöscht
   }
   dict->length++;
 }
