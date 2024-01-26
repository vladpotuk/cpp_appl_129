#include "LinkedList.h"

int main() {
    LinkedList<int> intList;

    try {
        intList.AddToHead(1);
        intList.AddToTail(2);
        intList.AddToTail(3);

        std::cout << "Original List: ";
        intList.Show();

        intList.DeleteFromHead();
        intList.DeleteFromTail();

        std::cout << "List after deletions: ";
        intList.Show();

        intList.InsertAtPosition(10, 1);
        intList.InsertAtPosition(20, 0);
        intList.InsertAtPosition(30, 3);

        std::cout << "List after insertions: ";
        intList.Show();

        intList.DeleteAtPosition(1);
        intList.DeleteAtPosition(0);
        intList.DeleteAtPosition(2);

        std::cout << "List after deletions at positions: ";
        intList.Show();

        int searchValue = 20;
        Node<int>* searchResult = intList.Search(searchValue);
        if (searchResult) {
            std::cout << "Element " << searchValue << " found at position: " << searchResult << std::endl;
        }
        else {
            std::cout << "Element " << searchValue << " not found." << std::endl;
        }

        int replaceOldValue = 2;
        int replaceNewValue = 99;
        int replaceCount = intList.Replace(replaceOldValue, replaceNewValue);
        if (replaceCount != -1) {
            std::cout << "Replaced " << replaceCount << " occurrences of " << replaceOldValue
                << " with " << replaceNewValue << std::endl;
            std::cout << "List after replacements: ";
            intList.Show();
        }
        else {
            std::cout << "Element " << replaceOldValue << " not found for replacement." << std::endl;
        }

        std::cout << "List before reversal: ";
        intList.Show();

        intList.Reverse();

        std::cout << "List after reversal: ";
        intList.Show();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
