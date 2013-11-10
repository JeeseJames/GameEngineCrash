#if !defined (LISTARRAYID_H)
#define LISTARRAYID_H

#include "String.h"
#include "ListArrayIterator.h"
using namespace CSC2110;

template < class T >
class ListArrayID
{
   private:
      String* list_key;

      int max_size;
      T** items;
      int sz;

      void arrayResize(int new_max_size);

   public:
      ListArrayID(String* key);
      ~ListArrayID();

      String* getKey();
      static int compare_items(ListArrayID<T>* la1, ListArrayID<T>* la2);
      static int compare_keys(String* id, ListArrayID<T>* la);

      bool isEmpty();
      int size();
      void removeAll();
      T* get(int index);
      void add(int index, T* item);
      void add(T* item);
      void remove(int index);
      void set(int index, T* item);
      ListArrayIterator<T>* iterator();
      T** toArray();
};

template < class T >
int ListArrayID<T>::compare_items(ListArrayID<T>* la1, ListArrayID<T>* la2)
{
   String* key_1 = la1->getKey();
   String* key_2 = la2->getKey();
   int key_compare = String::compare(key_1, key_2);
   return key_compare;
}

template < class T >
int ListArrayID<T>::compare_keys(String* key, ListArrayID<T>* la)
{
   String* key_1 = key;
   String* key_2 = la->getKey();
   int key_compare = String::compare(key_1, key_2);
   return key_compare;
}

template < class T >
String* ListArrayID<T>::getKey()
{
   return list_key;
}

template < class T >
ListArrayID<T>::ListArrayID(String* key)
{
   max_size = 10;
   items = new T*[max_size];
   sz = 0;

   list_key = key;
}

template < class T >
ListArrayID<T>::~ListArrayID()
{
   delete list_key;
   delete[] items;
}

template < class T >
bool ListArrayID<T>::isEmpty()
{
   return (sz == 0);
}

template < class T >
int ListArrayID<T>::size()
{
   return sz;
}

template < class T >  //1-based
T* ListArrayID<T>::get(int index)
{
   T* item = NULL;

   if (index >= 1 && index <= sz) 
   {  
      item = items[index - 1];
   }

   return item;
}

template < class T >
void ListArrayID<T>::add(T* item)
{
   add(sz + 1, item);  //add the item to the end of the array list
}

template < class T >
void ListArrayID<T>::add(int index, T* item)
{
   if (index < 1 || index > sz + 1)
   {
      return;
   }

   //need more room in the array list
   if (sz == max_size) 
   {
      arrayResize(2*max_size);
   }  
 
   for (int i = sz; i >= index; i--)
   { 
      items[i] = items[i - 1];
   }

   items[index - 1] = item;
   sz++;
}

template < class T >
void ListArrayID<T>::remove(int index)
{
   if (index < 1 || index > sz)
   {
      return;
   }

   for (int i = index; i < sz; i++)
   {
      items[i - 1] = items[i];
   }

   items[sz - 1] = NULL;
   sz--;
}

template < class T >
ListArrayIterator<T>* ListArrayID<T>::iterator()
{
   ListArrayIterator<T>* iter = new ListArrayIterator<T>(items, sz);
   return iter;
}

template < class T >
void ListArrayID<T>::set(int index, T* item)
{
   //could use other methods already written, but this is more efficient
   if (index >= 1 && index <= sz) 
   {
      items[index - 1] = item;  //overwrite contents at that location
   } 
}

template < class T >
void ListArrayID<T>::arrayResize(int new_max_size)
{
   max_size = new_max_size;
   T** temp = new T*[max_size];

   for (int i = 0; i < sz; i++)
   {
      temp[i] = items[i];
   }

   delete[] items;
   items = temp;
}

template < class T >
void ListArrayID<T>::removeAll()
{
   delete[] items;

   max_size = 10;
   items = new T*[max_size];
   sz = 0;
}

template < class T >
T** ListArrayID<T>::toArray()
{
   int num_items = size();
   T** to_array = new T*[num_items];
   for (int i = 0; i < num_items; i++)
   {
      to_array[i] = items[i];
   }
   return to_array;
}

#endif
