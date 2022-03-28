//
//  main.cpp
//  Projekt 1 - sortowanie
//
//  Created by Dawid Strzeszewski on 22/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <unistd.h>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <chrono>



using namespace std;

std::random_device rd;
std::mt19937 g(rd());


//Funkcja printArray służy do wyświetlenie tablicy w standardowym strumieniu wyjściowym
void printArray(int array[], int size)
{
  for (int i = 0; i < size; i++)
    cout << array[i] << " ";
cout << endl;
}


//Funkcja merge pozwala na rozbicie jednej tablicy na dwie podtablice, a następnie scalenie ich w jedną posortowaną
//array[] -> nasza tablica wymagająca posortowania
//l -> indeks pierwszego miejsca tablicy
//q -> indeks środka tablicy
//r -> indeks końca tablicy
void merge(int array[], int l, int q, int r)

{
    //Rozbijamy tablicę na dwie podtablice
      int n1 = q - l + 1;
      int n2 = r - q;
      int LeftArr[n1], RightArr[n2];
    
    //Tworzymy kopię tablic które będziemy z sobą porównywać
      for (int i = 0; i < n1; i++)
        LeftArr[i] = array[l + i];
      for (int j = 0; j < n2; j++)
        RightArr[j] = array[q + 1 + j];

      int i = 0; //Aktualny indeks podtablicy LeftArr[]
      int j = 0; //Aktualny indeks podtablicy RightArr[]
      int k = l; //Aktualny indeks tablicy wynikowej, będący początkowym indeksem tabliy wejściowej


      while (i < n1 && j < n2)
      {
        if (LeftArr[i] <= RightArr[j])
            {
                array[k] = LeftArr[i];
                i++;
            } else
                {
                    array[k] = RightArr[j];
                    j++;
                }
        k++;
      }

      // Te dwie pętle będą miały zastosowanie wtedy, kiedy skończą nam się do wyboru wartości w jednej z tych dwóch tablic
      while (i < n1) {
        array[k] = LeftArr[i];
        i++;
        k++;
      }

      while (j < n2) {
        array[k] = RightArr[j];
        j++;
        k++;
      }
}


void mergeSort(int array[], int l, int r)
{
  if (l < r)
  {
    int m = l + (r - l) / 2; //m -> indeks miejsca w którym dzielimie tablicę na dwie podtablice
      
    mergeSort(array, l, m);
    mergeSort(array, m + 1, r);
    merge(array, l, m, r);
  }
}


//Funkcja pozwalająca na zamianę miejscami dwóch liczb
void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}


int partition(int array[], int left, int right)
{
    
  // Jako pivota ustawiamy element najbardziej wysunięty na prawo
  int pivot = array[right];
  
  // Wskazuje nam na szukany większy element
  int i = (left-1);

  // Każdy element z tablicy porównujemy z naszym pivotem
  for (int j = left; j < right; j++)
  {
    if (array[j] <= pivot)
    {
      // Jeżeli znajdziemy element mniejszy od anszego pivota to zamieniamy go z większym elementem wskazywanym przez i
      i++;
      // zamieniamy element o indeksie i elementem o indeksie j
      swap(&array[i], &array[j]);
    }
  }
  
  // Zamieniamy pivota z większym elementem o indeksie i
  swap(&array[i + 1], &array[right]);
  
  // Zwracamy punkt podziału
  return (i + 1);
}


void quickSort(int array[], int low, int high)
{
  if (low < high)
  {
      
    // znajdujemy takiego pivota aby po lewej były elementy od niego mniejsze a po prawo większe
    int pi = partition(array, low, high);

    // rekursywnie wywołujemy z lewej strony
    quickSort(array, low, pi - 1);

      // rekursywnie wywołujemy z prawej strony
    quickSort(array, pi + 1, high);
  }
}


void heapify(int arr[], int n, int i) {
    // ustawiamy indeksy na trzon i dzieci
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
      largest = left;
  
    if (right < n && arr[right] > arr[largest])
      largest = right;
  
    //kontynuujemy czynność dopóki trzon nie będzie największy
    if (largest != i) {
      swap(arr[i], arr[largest]);
      heapify(arr, n, largest);
    }
  }
  

  void heapSort(int arr[], int n) {
    // Tworzymy max heap
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i);
  
    // Heapsort sam w sobie
    for (int i = n - 1; i >= 0; i--) {
      swap(arr[0], arr[i]);
  
      // Najwyższy element na górze
      heapify(arr, i, 0);
    }
  }

void heapifyIntro(int arr[], int n, int i, int q) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < q + 1 && arr[left] > arr[largest])
      largest = left;
  
    if (right < q + 1 && arr[right] > arr[largest])
      largest = right;
  
    if (largest != i) {
      swap(arr[i], arr[largest]);
      heapifyIntro(arr, n, largest,q);
    }
  }
  
  void heapSortIntro(int arr[], int left, int right)
{
      int n = right - left + 1;
    for (int i = n / 2 + left; i >= left; i--)
      heapifyIntro(arr, n, i, right);
  
    for (int i = right; i >= left; i--) {
      swap(arr[0], arr[i]);
  
      heapifyIntro(arr, i, 0, i);
    }
  }

  
void introSort(int array[], int left, int right)
{
    if (right > left){
    int pivot = array[right];
    if (pivot == *min_element(array + left, array + right) || pivot == *max_element(array + left, array + right))
    {heapSortIntro(array, left,right);
    return;}
    else
    {
        
        if (left < right)
        {
      int pi = partition(array, left, right);
      introSort(array, left, pi - 1);
      introSort(array, pi + 1, right);
        }
    }
    }
}

int* MakeTab(int size, int test, int subtest)
{
    
    int *array = new int[size]; //Stworzenie tablicy o zadeklarowanym rozmiarze
    
    switch (test) {
        case 1:
            for(int i=0; i<size; i++)
                array[i] = i;
            std::shuffle(&array[0], &array[size-1], g);
            break;
            
        case 3:
        {
            int j = 0;
            for (int i = size-1; i>=0; i--)
            {
                array[j] = i;
                j++;
            }
        }
            break;
            
        default:
            break;
    }
    
    switch (subtest)
    {
        case 1:
        {
            for(int i=0; i<size; i++)
                array[i] = i;
            int pivot = round(0.25 * (size));
            std::shuffle(&array[pivot], &array[size], g);
        }
            break;
            
        case 2:
        {
            for(int i=0; i<size; i++)
                array[i] = i;
            int pivot = round(0.5 * (size));
            std::shuffle(&array[pivot], &array[size], g);
        }
            break;
            
        case 3:
        {
            for(int i=0; i<size; i++)
                array[i] = i;
            int pivot = round(0.75 * (size));
            std::shuffle(&array[pivot], &array[size], g);
        }
            break;
            
        case 4:
        {
            for(int i=0; i<size; i++)
                array[i] = i;
            int pivot = round(0.95 * (size));
            std::shuffle(&array[pivot], &array[size], g);
        }
            break;
            
        case 5:
        {
            for(int i=0; i<size; i++)
                array[i] = i;
            int pivot = round(0.99 * (size));
            std::shuffle(&array[pivot], &array[size], g);
        }
            break;
            
        case 6:
        {
            for(int i=0; i<size; i++)
                array[i] = i;
            int pivot = round(0.997 * (size));
            std::shuffle(&array[pivot], &array[size], g);
        }
            break;
            
        default:
            break;
    }
    return array;
}

int main() {

    int tabchoice;
    int testchoice;
    int subtestchoice;
    int sortchoice;
    int size;
    int paczka = 100;
    system("clear");
    cout << "Wybierz rozmiar pojedynczej tablicy z paczki stu tablic dla których zamierzasz dokonać sortowania:" << endl;
    cout << "1 - 10 000 elementów" << endl;
    cout << "2 - 50 000 elemetnów" << endl;
    cout << "3 - 100 000 elementów" << endl;
    cout << "4 - 500 000 elementów" << endl;
    cout << "5 - 1 000 000 elementów" << endl << endl;
    
    cin >> tabchoice;
    
    switch (tabchoice) {
        case 1:
            size = 10000;
            break;
            
        case 2:
            size = 50000;
            break;
            
        case 3:
            size = 100000;
            break;
            
        case 4:
            size = 500000;
            break;
            
        case 5:
            size = 1000000;
            break;
            
        default:
            break;
    }
    
    system("clear");
    
    cout << "Wybrałeś opcję nr " << tabchoice << endl << endl;
    
    cout << "Wybierz typ aktualnego testu efektywności:" << endl << endl;
    cout << "1 - elementy tablicy są całkowicie losowe" << endl;
    cout << "2 - elementy tablicy są częściowo posortowane" << endl;
    cout << "3 - elementy tablicy są posortowane, ale w odwrotnej kolejności" << endl << endl;
    cin >> testchoice;
    system("clear");
    
    
    if (testchoice == 2) {
        cout << "Jaki procent tablicy ma być posortowany?" << endl << endl;
        cout << "1 - 25%" << endl;
        cout << "2 - 50%" << endl;
        cout << "3 - 75%" << endl;
        cout << "4 - 95%" << endl;
        cout << "5 - 99%" << endl;
        cout << "6 - 99,7%" << endl << endl;
        cin >> subtestchoice;
    }
    
    
    cout << "Wybierz rodzaj algorytmu sortowania który chcesz zastosować:" << endl << endl;
    cout << "1 - Mergesort" << endl;
    cout << "2 - Quicksort" << endl;
    cout << "3 - Introsort" << endl;
    cout << "4 - porównanie szybkości wszystkich algorytmów" << endl << endl;
    cin >> sortchoice;
    
    long long czas = 0;
    long long czastmp = 0;
    long long czasQuick = 0;
    long long czasMerge = 0;
    long long czasIntro = 0;
    long long czasHeap = 0;
    
    switch (sortchoice) {
        case 1:
        {
            for (int i = 0; i < paczka; i++)
            {
                int* array = MakeTab(size, testchoice, subtestchoice);
                auto start = std::chrono::high_resolution_clock::now();
                mergeSort(array, 0, size-1);
                auto finish = std::chrono::high_resolution_clock::now();
                czastmp = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
                cout << endl <<  "Czas potrzebny na posortowanie tablicy nr " << i+1 << " wyniósł: " << czastmp << " mikrosekund" << endl << endl;
                czas += std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
            }
            czas /= paczka;
            cout << endl <<  "Średni czas potrzebny na posortowanie wyniósł: " << czas << " mikrosekund" << endl << endl;
        }
            break;
            
        case 2:
        {
            for (int i = 0; i < paczka; i++)
            {
                int* array = MakeTab(size, testchoice, subtestchoice);
                auto start = std::chrono::high_resolution_clock::now();
                quickSort(array, 0, size-1);
                auto finish = std::chrono::high_resolution_clock::now();
                czastmp = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
                cout << endl <<  "Czas potrzebny na posortowanie tablicy nr " << i+1 << " wyniósł: " << czastmp << " mikrosekund" << endl << endl;
                czas += std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
            }
            czas /= paczka;
            cout << endl << "Czas potrzebny na posortowanie wyniósł: " << czas << " mikroosekund" << endl << endl;
        }
            break;
            
        case 3:
        {
            for (int i = 0; i < paczka; i++)
            {
                int* array = MakeTab(size, testchoice, subtestchoice);
                auto start = std::chrono::high_resolution_clock::now();
                introSort(array, 0, size-1);
                auto finish = std::chrono::high_resolution_clock::now();
                czastmp = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
                cout << endl <<  "Czas potrzebny na posortowanie tablicy nr " << i+1 << " wyniósł: " << czastmp << " mikrosekund" << endl << endl;
                czas += std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();

            }
            czas /= paczka;
            cout << endl << "Czas potrzebny na posortowanie wyniósł: " << czas << " mikroosekund" << endl << endl;
        }
            break;
            
        case 4:
        {
            for (int i = 0; i < paczka; i++)
            {
                int* arrayQuick = MakeTab(size, testchoice, subtestchoice);
                int arrayMerge[size];
                int arrayIntro[size];
                int arrayHeap[size];
                for (int i = 0; i < size; i++)
                {
                    arrayMerge[i] = arrayQuick[i];
                    arrayIntro[i] = arrayQuick[i];
                    arrayHeap[i] = arrayQuick[i];
                }
                auto start = std::chrono::high_resolution_clock::now();
                quickSort(arrayQuick, 0, size-1);
                auto finish = std::chrono::high_resolution_clock::now();
                czastmp = std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
                cout << endl <<  "Czas potrzebny na posortowanie tablicy nr " << i+1 << " dla quicksorta wyniósł: " << czastmp << " mikrosekund" << endl << endl;
                czasQuick += std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count();
                
                
                auto start2 = std::chrono::high_resolution_clock::now();
                mergeSort(arrayMerge, 0, size-1);
                auto finish2 = std::chrono::high_resolution_clock::now();
                czastmp = std::chrono::duration_cast<std::chrono::microseconds>(finish2-start2).count();
                cout << endl <<  "Czas potrzebny na posortowanie tablicy nr " << i+1 << " dla mergesorta wyniósł: " << czastmp << " mikrosekund" << endl << endl;
                czasMerge += std::chrono::duration_cast<std::chrono::microseconds>(finish2-start2).count();
                
                auto start3 = std::chrono::high_resolution_clock::now();
                introSort(arrayIntro, 0, size-1);
                auto finish3 = std::chrono::high_resolution_clock::now();
                czastmp = std::chrono::duration_cast<std::chrono::microseconds>(finish3-start3).count();
                cout << endl <<  "Czas potrzebny na posortowanie tablicy nr " << i+1 << " dla introsorta wyniósł: " << czastmp << " mikrosekund" << endl << endl;
                czasIntro += std::chrono::duration_cast<std::chrono::microseconds>(finish3-start3).count();
                
                auto start4 = std::chrono::high_resolution_clock::now();
                heapSort(arrayHeap, size);
                auto finish4 = std::chrono::high_resolution_clock::now();
                czastmp = std::chrono::duration_cast<std::chrono::microseconds>(finish4-start4).count();
                cout << endl <<  "Czas potrzebny na posortowanie tablicy nr " << i+1 << " dla heapsorta wyniósł: " << czastmp << " mikrosekund" << endl << endl;
                czasHeap += std::chrono::duration_cast<std::chrono::microseconds>(finish4-start4).count();
            }

            czasQuick /= paczka;
            czasMerge /= paczka;
            czasIntro /= paczka;
            czasHeap /= paczka;
            cout << endl << "Średni czas potrzebny na posortowanie dla quicksorta wyniósł: " << czasQuick << " mikrosekund" << endl;
            cout << endl << "Średni czas potrzebny na posortowanie dla mergesorta wyniósł: " << czasMerge << " mikrosekund" << endl;
            cout << endl << "Średni czas potrzebny na posortowanie dla heapsorta wyniósł: " << czasHeap << " mikrosekund" << endl;
            cout << endl << "Średni czas potrzebny na posortowanie dla introsorta wyniósł: " << czasIntro << " mikrosekund" << endl << endl;

    
        }

            
        default:
            break;
    }
    
    return 0;
}

