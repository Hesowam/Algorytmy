#include <iostream>
#include "List.h"
#include <time.h>
#include <format>

using namespace std;

struct Product {
    string label;
    double price;
};

int main() {
    List<Product> *productList = new List<Product>();

    cout << "Start adding and deleting objects on the list \t\n\n";
    for (int o = 1; o < 6; o ++) {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; ++i) {
            Product product;

            product.price = rand() % 2000 + 1;
            product.label = "New Product";

            productList->addBack(product);
        }
        clock_t t2 = clock();

        cout << n << "\t objects were added to the list in\t" << 1000.0 * (t2 - t1) / CLOCKS_PER_SEC << "ms\n";

        t1 = clock();
        for (int i = 0; i<n/2; i++) {
            productList->remove(i);
        }
        t2 = clock();

        cout << n/2 << "\t objects were founded and removed to the list in\t" << 1000.0 * (t2 - t1) / CLOCKS_PER_SEC << "ms\n";
    }
    cout << "\nThere are " << productList->length() << " items on the list";
    productList->clear();
    productList->string();

    { // Checking the methods of adding the last element to the list, updating an element by index and getting an element from the list
        Product tmp_product;

        tmp_product.price = 33.50;
        tmp_product.label = "Apple";

        productList->addBack(tmp_product);

        cout << endl << productList->get(0).label << " " << productList->get(0).price;

        tmp_product.price = 22.3;
        tmp_product.label = "Watermelon";

        productList->update(0, tmp_product);

        cout << endl << productList->get(0).label << " " << productList->get(0).price;
    }

    {
        Product tmp_product;

        tmp_product.price = 33.5;
        tmp_product.label = "Apple";
        for (int i = 0; i < 10; ++i) {
            productList->addBack(tmp_product);
        }

        productList->string();

        productList->removeLast();
        productList->removeFirst();
        productList->remove(5);

        cout   << "\nThe list after deleting objects";
        productList->string();

        productList->addFront(tmp_product);
        productList->addBack(tmp_product);
        productList->add(7, tmp_product);

        cout   << "\nThe list after adding objects";
        productList->string();
    }



}
