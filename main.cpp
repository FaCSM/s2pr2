#include <iostream>
#include <ctime>
using namespace std;

struct listItem {
    listItem *prev;
    listItem *next;
    int data;
};

listItem *CreateDefiniteList(int &length) {
    listItem *curr = 0, *next = 0;
    while (true) {
        cout << "Enter list length: ";
        if (cin >> length) {
            if (length <= 0) {
                cout << "Invalid value entered, try again\n\n";
                cin.clear();
                cin.ignore();
                continue;
            }
            break;
        } else {
            cout << "Invalid value entered, try again\n\n";
            cin.clear();
            cin.ignore();
            length = 0;
            continue;
        }
    }
    for (unsigned i = 1; i <= length; ++i) {
        curr = new listItem;
        curr->data = rand() % 100;
        curr->next = next;
        if (next) {
            next->prev = curr;
        }
        next = curr;
    }
    curr->prev = 0;
    return curr;
}

listItem *CreateIndefiniteList(int &length) {
    listItem *curr = 0, *next = 0;
    for (int i = 1;; i++) {
        curr = new listItem;
        cout << "Enter the value " << i << " of the element (from the end): ";
        if (cin >> curr->data) {
            cin.clear();
            cin.ignore();
            length++;
        } else {
            if (i == 1) {
                cout << "Invalid value entered, try again\n\n";
                cin.clear();
                cin.ignore();
                continue;
            } else {
                cout << "Invalid value entered, list creation stopped\n\n";
                cin.clear();
                cin.ignore();
                delete curr;
                curr->prev = 0;
                return next;
            }
        }
        curr->next = next;
        if (next) {
            next->prev = curr;
        }
        next = curr;
    }
}

listItem *AddElement(listItem *&list, int &length) {
    int pos = 0;
    listItem *item = new listItem;
    cout << "Enter the value of the item and its position in the list\n";
    while (true) {
        cout << "value: ";
        if (cin >> item->data) {
            cin.clear();
            cin.ignore();
            break;
        } else {
            cout << "\nInvalid value entered, try again\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    while (true) {
        cout << "Position: ";
        if (cin >> pos) {
            if (pos >= length) {
                pos = length;
                cout << "The item will be inserted at the end of the list\n";
                cin.clear();
                cin.ignore();
                break;
            }
            if (pos <= 1) {
                pos = 1;
                cout << "The item will be inserted at the top of the list\n";
                cin.clear();
                cin.ignore();
                break;
            }
            break;
        } else {
            cout << "Invalid value entered, try again\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    cout << '\n';
    if (pos == 1) {
        list->prev = item;
        item->prev = 0;
        item->next = list;
        list = item;
        length++;
        return item;
    }
    listItem *curr = list;
    if (pos == length) {
        for (int i = 1; i <= length; i++) {
            if (pos == i) {
                curr->next = item;
                item->next = 0;
                item->prev = curr;
                length++;
                return list;
            }
            curr = curr->next;
        }
    }
    for (int i = 1; i <= length; i++) {
        if (pos == i) {
            item->next = curr;
            item->prev = curr->prev;
            curr->prev->next = item;
            curr->prev = item;
            length++;
            return list;
        }
        curr = curr->next;
    }
}

int SwapElements(listItem *&list, int &length) {
    listItem *curr = list;
    int first, second;
    struct listItem *firstEl, *secondEl;
    firstEl = secondEl = curr;
    while (true) {
        cout << "Enter the position of the first element: ";
        if (cin >> first) {
            if (first < 1 || first > length) {
                cout << "The element with this position does not exist, enter the value again\n\n";
                cin.clear();
                cin.ignore();
                continue;
            }
            break;
        } else {
            cout << "Invalid value entered, try again\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    while (true) {
        cout << "Enter the position of the second element: ";
        if (cin >> second) {
            if (second < 1 || second > length) {
                cout << "The element with this position does not exist, enter the value again\n\n";
                cin.clear();
                cin.ignore();
                continue;
            }
            cout << '\n';
            break;
        } else {
            cout << "Invalid value entered, try again\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    if (first > second) {
        swap(first, second);
    }
    for (int i = 1; i < first; i++) {
        firstEl = firstEl->next;
    }
    secondEl = firstEl;
    for (; first < second; first++) {
        secondEl = secondEl->next;
    }
    swap(firstEl->data, secondEl->data);
}

int DeleteElementByValue(listItem *&list, int &length) {
    int element = 0;
    while (true) {
        cout << "Enter the value of the element: ";
        if (cin >> element) {
            cin.clear();
            cin.ignore();
            break;
        } else {
            cout << "Invalid value entered, try again\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    listItem *curr = list;
    for (int i = 1; i <= length; i++) {
        if (curr->data == element) {
            cout << "The element with the value " << element << " has been deleted\n\n";
            if (curr->next) {
                curr->next->prev = curr->prev;
            }
            if (curr->prev) {
                curr->prev->next = curr->next;
            }
            delete curr;
            length--;
            return 0;
        } else {
            curr = curr->next;
        }
    }
    cout << "The element with the value " << element << " was not found\n\n";
    return 0;
}

int DeleteElementByPosition(listItem *&list, int &length) {
    int position = 0;
    while (true) {
        cout << "Enter the item position: ";
        if (cin >> position) {
            if (position < 1 || position > length) {
                cout << "There is no element with this position\n\n";
                cin.clear();
                cin.ignore();
                return 0;
            }
            cin.clear();
            cin.ignore();
            break;
        } else {
            cout << "Invalid value entered, try again\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    listItem *curr = list;
    for (int i = 1;; i++) {
        if (position == i) {
            if (curr->next) {
                curr->next->prev = curr->prev;
            }
            if (curr->prev) {
                curr->prev->next = curr->next;
            }
            delete curr;
            length--;
            cout << "The element at the position " << position << " has been deleted\n\n";
            return 0;
        }
        curr = curr->next;
    }
}

int GetElementByValue(listItem *&list, int &length) {
    int element = 0;
    while (true) {
        cout << "Enter the value of the element: ";
        if (cin >> element) {
            cin.clear();
            cin.ignore();
            break;
        } else {
            cout << "Invalid value entered, try again\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    listItem *curr = list;
    for (int i = 1; i <= length; i++) {
        if (curr->data == element) {
            cout << "The element with the value " << element << " was found at the " << i << " position \n\n";
            return 0;
        } else {
            curr = curr->next;
        }
    }
    cout << "Element with value " << element << " not found\n\n";
    return 0;
}

int GetElementByPosition(listItem *&list, int &length) {
    int position = 0;
    while (true) {
        cout << "Enter the position of the element: ";
        if (cin >> position) {
            if (position < 1 || position > length) {
                cout << "There is no element with this position\n\n";
                cin.clear();
                cin.ignore();
                return 0;
            }
            cin.clear();
            cin.ignore();
            break;
        } else {
            cout << "Invalid value entered, try again\n\n";
            cin.clear();
            cin.ignore();
            continue;
        }
    }
    listItem *curr = list;
    for (int i = 1;; i++) {
        if (position == i) {
            cout << "Element at position " << position << " has value " << curr->data << "\n\n";
            return 0;
        }
        curr = curr->next;
    }
}

void OutputList(listItem *&list) {
    struct listItem *curr = list;
    while (true) {
        cout << curr->data << ' ';
        if (curr->next) {
            curr = curr->next;
        } else { break; }
    }
    cout << endl;
}

void DeleteList(int &length, listItem *list) {
    listItem *curr = list, *next = 0;
    for (int i = 1; i <= length; i++) {
        next = curr->next;
        delete curr;
        curr = next;
    }
    length = 0;
}

void DeleteMassive(int &length) {
    int *arr = new int[length];
    delete[] arr;
}

int main() {
    unsigned short number_of_task;
    int length = 0;
    listItem *list;

    while (true) {
        cout << "\nHow do you want to create a doubly linked list?\n"
                "1. Set the dimension, random values\n"
                "2. Set values, dimension by their number \n\n"
                "Number:";
        cin >> number_of_task;
        switch (number_of_task) {
            case 1: {
                DeleteList(length, list);
                list = CreateDefiniteList(length);
                OutputList(list);
                break;
            }
            case 2: {
                DeleteList(length, list);
                unsigned int start_time = clock();
                list = CreateIndefiniteList(length);
                unsigned int end_time = clock();
                unsigned int search_time = end_time - start_time;
                cout << "Execution time: " << search_time << " milliseconds\n\n";
                OutputList(list);
                break;
            }
            default: {
                cout << "Invalid value entered, try again\n";
                cin.clear();
                cin.ignore();
                continue;
            }
        }
        break;
    }
    while (true) {
        cout << "\nSelect the task number you want to access:\n"
                "1. Creating a list with random values\n"
                "2. Creating a list with fixed values \n"
                "3. Adding an item to the list \n"
                "4. Deleting an item by value \n"
                "5. Deleting an element by position \n"
                "6. Exchanging elements \n"
                "7. Getting an element by value \n"
                "8. Getting an element by index \n"
                "9. IDZ (Deleting the list and array)\n"
                "To return to the previous menu, enter 0\n\n"
                "Number: ";
        cin >> number_of_task;

        switch (number_of_task) {
            case 1: {
                DeleteList(length, list);
                list = CreateDefiniteList(length);
                OutputList(list);
                break;
            }
            case 2: {
                DeleteList(length, list);
                unsigned int start_time = clock();
                list = CreateIndefiniteList(length);
                unsigned int end_time = clock();
                unsigned int search_time = end_time - start_time;
                cout << "Execution time: " << search_time << " milliseconds\n\n";
                OutputList(list);
                break;
            }
            case 3: {
                unsigned int start_time = clock();
                list = AddElement(list, length);
                unsigned int end_time = clock();
                unsigned int search_time = end_time - start_time;
                cout << "Execution time: " << search_time << " milliseconds\n\n";
                OutputList(list);
                break;
            }
            case 4: {
                unsigned int start_time = clock();
                DeleteElementByValue(list, length);
                unsigned int end_time = clock();
                unsigned int search_time = end_time - start_time;
                cout << "Execution time: " << search_time << " milliseconds\n\n";
                OutputList(list);
                break;
            }
            case 5: {
                unsigned int start_time = clock();
                DeleteElementByPosition(list, length);
                unsigned int end_time = clock();
                unsigned int search_time = end_time - start_time;
                cout << "Execution time: " << search_time << " milliseconds\n";
                OutputList(list);
                break;
            }
            case 6: {
                SwapElements(list, length);
                OutputList(list);
                break;
            }
            case 7: {
                unsigned int start_time = clock();
                GetElementByValue(list, length);
                unsigned int end_time = clock();
                unsigned int search_time = end_time - start_time;
                cout << "Execution time: " << search_time << " milliseconds\n";
                break;
            }
            case 8: {
                unsigned int start_time = clock();
                GetElementByPosition(list, length);
                unsigned int end_time = clock();
                unsigned int search_time = end_time - start_time;
                cout << "Execution time: " << search_time << " milliseconds\n";
                break;
            }
            case 9: {
                unsigned int start_time = clock();
                DeleteMassive(length);
                unsigned int end_time = clock();
                unsigned int search_time = end_time - start_time;
                cout << "Time to delete a dynamic array: " << search_time << " milliseconds\n\n";

                start_time = clock();
                DeleteList(length, list);
                end_time = clock();
                search_time = end_time - start_time;
                cout << "Time to delete a doubly linked list: " << search_time << " milliseconds\n\n";

                break;
            }
            default: {
                cout << "\nThere is no task with this number\n";
                break;
            }
        }
    }
}
