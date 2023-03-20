#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#define NAME_LEN 50

typedef struct {
    long id;
    char name[NAME_LEN];
    double price;
    int stock;
} Product;

typedef struct {
    long id;
    Product *products;
    // allows static size allocation after finishing the order
    int numProducts;
    float total;
} Order;

Product findProductByID(Product* products, int listSize, long targetId) {
    // TODO: prevent empty products
    for (int i = 0; i < listSize; i++) {
        if (products[i].id == targetId) {
            return products[i];
        }
    }
    // Return a default value if the struct is not found
    Product result = {-1, "", 0.0, 0};
    return result;
}

void sendPostRequest(char* url) {
    return;
}

int main() {
    int choice;
    long productId;
    int quantity;
    double total = 0.0;
    Order order = { 1, NULL, 0 };

    // Use a hardcoded list instead of any type of DB lookup
    // Ain't nobody got time fo' dat!.mp4 -> https://youtu.be/bFEoMO0pc7k
    Product allProducts[] = {
        {1, "Apple", 10.0, 20},
        {2, "Banana", 10.0, 20},
        {3, "Pineapple", 10.0, 20},
        {4, "Bleach", 10.0, 20},
        {5, "Burek", 10.0, 20},
        {6, "WC Cleaner", 10.0, 20},
    };

    printf("=========================\n");
    printf("Welcome to POS terminal\n");
    printf("=========================\n");

    while (choice != 4) {
        printf("\nEnter your choice:\n");
        printf("1 - Quit the program\n");
        printf("2 - Print current order\n");
        printf("3 - Add product to order\n");
        printf("4 - Finish order\n");
        int result = scanf("%d", &choice);

        if (result != 1) {
            printf("Error: Invalid input. Please enter a number.\n");
            fflush(stdin);
            continue;
        } else {
            switch (choice) {
                case 1:
                    printf("Quitting the program...");
                    exit(0);
                case 2:
                    printf("Printing current order...\n");
                    printf("Order ID: %ld\n", order.id);
                    printf("Products:\n");
                    for (int i = 0; i < order.numProducts; i++) {
                        printf("  ID: %ld, Quantity: %d, Price: %.2f\n", 
                            order.products[i].id, order.products[i].stock, order.products[i].price);
                    }
                    break;
                case 3:
                    // TODO: implement timeout
                    // TODO: implement button timeout/button debounce
                    printf("Enter product ID: ");
                    result = scanf("%ld", &productId);
                    if (result != 1) {
                        printf("Error: Invalid input. Please enter a number.\n");
                        fflush(stdin);
                        continue;
                    }

                    printf("Enter quantity: ");
                    result = scanf("%d", &quantity);
                    if (result != 1) {
                        printf("Error: Invalid input. Please enter a number.\n");
                        fflush(stdin);
                        continue;
                    }

                    // Add the product to the order here
                    if (order.products == NULL) {
                        order.products = (Product *) malloc(sizeof(Product));
                    } else {
                        order.products = (Product *) realloc(order.products, 
                                                            (order.numProducts + 1) * sizeof(Product));
                    }
                    // TODO: replace 6 with calculated size
                    Product foundProduct = findProductByID(allProducts, 6, productId);
                    printf("ID: %d", foundProduct.id);
                    if (foundProduct.id != -1) {
                        order.products[order.numProducts].id = foundProduct.id;
                        order.products[order.numProducts].stock = quantity;
                        order.products[order.numProducts].price = foundProduct.price;
                        // TODO: fix this
                        // order.products[order.numProducts].name = foundProduct.name;
                        // allows static size allocation after finishing the order
                        order.numProducts++;
                    }
                    else {
                        printf("Error: Product not found!\n");
                        fflush(stdin);
                        continue;
                    }
                    
                    break;
                case 4:
                    printf("Finishing order...\n");
                    total = 0;
                    // Print the order and total amount due here
                    // TODO: implement multiple instances of same product must pool amount
                    // before determining if there is enough stock
                    printf("Order ID: %ld\n", order.id);
                    printf("Products:\n");
                    for (int i = 0; i < order.numProducts; i++) {
                        if (
                                findProductByID(allProducts, 6, order.products[i].id).stock
                                <
                                order.products[i].stock
                            ) {
                            printf("Error: Not enough stock for product %ld.\n", order.products[i].id);
                            continue;
                        } else {
                            printf("  ID: %ld, Quantity: %d, Price: %.2f\n", order.products[i].id, order.products[i].stock, order.products[i].price);
                            total += order.products[i].price * order.products[i].stock;
                            // TODO: decrease total stock
                        }
                    }
                    printf("Total amount due: %.2f\n", total);
                    order.total = total;
                    // 
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
                    break;
            }
        }
        
        
    }
    return 0;
}