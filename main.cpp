#include <iostream>
#include <cstring>
#include <windows.h>

using namespace std;

const int MAX_NAME_LEN = 30;
const int K = 3;

struct Car {
    unsigned int id;
    char brand[MAX_NAME_LEN];
    char model[MAX_NAME_LEN];
    double cost;
    void car_out() {
        cout << id << "\t" << brand << "\t" << model << "\t" << cost << " USD" << endl;
    }
};

void swap_char(char a[], char b[], int size) {
    char temp;
    for (int i = 0; i < size; i++) {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void swap(Car &C1, Car &C2) {
    unsigned int temp_id = C1.id;
    C1.id = C2.id;
    C2.id = temp_id;

    swap_char(C1.brand, C2.brand, MAX_NAME_LEN);
    swap_char(C1.model, C2.model, MAX_NAME_LEN);
    double temp_cost = C1.cost;
    C1.cost = C2.cost;
    C2.cost = temp_cost;
}

struct element {
    Car element_list;
    element *next;
};

class List {
private:
    element *header;
public:
    List() { header = NULL; }
    void add(Car x) {
        element *p = new element;
        p->element_list = x;
        p->next = header;
        if (header == NULL) header = p;
    }
    void print() {
        element *p = header;
        int k = 0;
        while (p != NULL) {
            cout << k++ << ": ";
            p->element_list.car_out();
            p = p->next;
        }
        if (k == 0) cout << "empty List" << endl;
    }
    void selectionSort(int key) {
        if (header == NULL) return;
        element *current = header;
        while (current != NULL) {
            element *min = current;
            element *temp = current->next;
            while (temp != NULL) {
                bool swap_needed = false;
                if (key == 1 && strcmp(temp->element_list.brand, min->element_list.brand) < 0) swap_needed = true;
                else if (key == 2 && temp->element_list.cost < min->element_list.cost) swap_needed = true;
                else if (key == 3 && temp->element_list.id < min->element_list.id) swap_needed = true;
                if (swap_needed) min = temp;
                temp = temp->next;
            }
            if (min != current) swap(current->element_list, min->element_list);
            current = current->next;
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    List list;
    Car cars[K];
    for (int i = 0; i < K; i++) {
        cout << "Car #" << i + 1 << ":\n";
        cars[i].id = i + 1;
        cout << "Brand? "; cin >> cars[i].brand;
        cout << "Model? "; cin >> cars[i].model;
        cout << "Cost? "; cin >> cars[i].cost;
        cout << endl;
        list.add(cars[i]);
    }

    cout << "\nData in order of creation:\n";
    cout << "Index\tID\tBrand\tModel\tCost\n";
    list.print();

    int choice;
    cout << "\nSelect sorting order:\n";
    cout << "0 in previous order\n";
    cout << "1 sorted by brand\n";
    cout << "2 sorted by cost\n";
    cout << "3 sorted by factory number\n";
    cout << "Your choice: ";
    cin >> choice;

    if (choice != 0) list.selectionSort(choice);
    cout << "\nSorted data:\n";
    cout << "Index\tID\tBrand\tModel\tCost\n";
    list.print();

    return 0;
}