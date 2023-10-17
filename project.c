#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if quantity is positive or zero
int check(int quant) {
    if (quant <= 0) {
        return 0;
    } else {
        return quant;
    }
}

struct node {
    int ID;
    char proName[100];
    double prePrice;
    int quantity;
    struct node* next;
    struct node* prev;
};

struct bstNode {
    int ID;
    struct node* productNode;
    struct bstNode* left;
    struct bstNode* right;
};

struct node* head = NULL;
struct bstNode* root = NULL;

// Function to insert products into the BST
struct bstNode* insertBST(struct bstNode* root, int ID, struct node* productNode) {
    if (root == NULL) {
        struct bstNode* newNode = (struct bstNode*)malloc(sizeof(struct bstNode));
        newNode->ID = ID;
        newNode->productNode = productNode;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (ID < root->ID) {
        root->left = insertBST(root->left, ID, productNode);
    } else if (ID > root->ID) {
        root->right = insertBST(root->right, ID, productNode);
    }
    
    return root;
}

// Function to search for a product by ID in the BST
struct node* searchProductByID(struct bstNode* root, int ID) {
    if (root == NULL || root->ID == ID) {
        return (root != NULL) ? root->productNode : NULL;
    }

    if (ID < root->ID) {
        return searchProductByID(root->left, ID);
    } else {
        return searchProductByID(root->right, ID);
    }
}

int display(){
    system("cls");
    int c=0;       //  c for count  products
    struct node *ptr = head;
    printf("Existing products are:\n");
    printf("ID\t\tProduct Name\t\tPrice\t\tQuantity\n");
    while(ptr!=NULL)
    {
        printf("%d\t\t%s\t\t\t%lf\t",ptr->ID,ptr->proName,ptr->prePrice);//    call   check func and pass quantity
        if(check(ptr->quantity)<=0){
            printf("OUT OF STOCK!\n");
        }
        else{
            printf("%d\n",check(ptr->quantity));
        }
        ptr=ptr->next;
        c=c+1;     //  product counter 
    }
    printf("\nTotal products in our store is : %d\n\n\n",c);
    return c;
}

int search(int id){
    int count=1;
    struct node* ptr=head;
    while(ptr!=NULL){
        if(ptr->ID == id){
            break;
        }
        else{
            count++;
            ptr=ptr->next;
        }
    }
    return count;
}

void modify() {
    if (head == NULL) {
        system("cls");
        printf("Product list is empty!!\n");
    } else {
        system("cls");
        printf("Select a product to modify:\n");
        display(); // Display the list of products with their IDs

        int modify_id;
        printf("Enter the ID of the product you want to modify: ");
        scanf("%d", &modify_id);

        struct node *cur = head;
        int pos = 0;
        int count = display(); // Load the number of nodes
        pos = search(modify_id); // Check whether the desired node exists

        if (pos <= count) {
            while (cur->ID != modify_id) {
                cur = cur->next;
            }

            system("cls");
            printf("Product Details for ID %d:\n", cur->ID);
            printf("Name: %s\n", cur->proName);
            printf("Price: %lf\n", cur->prePrice);
            printf("Quantity: %d\n", cur->quantity);

            char modify_name[100];
            double modify_price;
            int modify_quantity;

            printf("Enter new Name: ");
            scanf("%s", modify_name);

            for (int i = 0; i < 100; i++) {
                cur->proName[i] = modify_name[i];
            }

            printf("Enter new Price: ");
            scanf("%lf", &modify_price);
            cur->prePrice = modify_price;

            printf("Enter new Quantity: ");
            scanf("%d", &modify_quantity);
            cur->quantity = modify_quantity;

            system("cls");
            printf("\n<< Product details for ID %d modified >>\n", modify_id);
        } else {
            printf("%d is <<Not found>>\n\n", modify_id);
        }
    }
}

void delete_product() {
    system("cls");
    printf("Total products in cart\n\n");
    display();
    int delete_id;
    struct node *ptr = head;
    struct node *qtr = head;
    printf("\n\nEnter ID to delete that product:\n");
    scanf("%d", &delete_id);

    if (head == NULL) {
        system("cls");
        printf("List is empty\n");
        return;
    }

    int pos = 0; // Default
    int count = display();
    pos = search(delete_id);

    if (pos <= count) {
        while (ptr != NULL) {
            if (ptr->ID == delete_id) {
                if (ptr == head) {
                    head = ptr->next;
                    if (head != NULL) {
                        head->prev = NULL;
                    }
                } else {
                    qtr->next = ptr->next;
                    if (ptr->next != NULL) {
                        ptr->next->prev = qtr;
                    }
                }
                free(ptr);
                system("cls");
                printf("\n<< Product with ID %d is deleted >>\n", delete_id);
                return;
            } else {
                qtr = ptr;
                ptr = ptr->next;
            }
        }
    } else {
        printf("\n<< ID Not found >>\n\n");
    }
}

void create_node() {
    system("cls");
    int id, pro_quant;
    char pro_name[100];
    double pro_price;

    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    struct node *qtr = head; // Add qtr to traverse the list

    printf("\t\tEnter product ID: ");
    scanf("%d", &id);
    ptr->ID = id;

    printf("\t\tEnter product Name: ");
    scanf("%s", pro_name);
    for (int i = 0; i < 100; i++) {
        ptr->proName[i] = pro_name[i];
    }

    printf("\t\tEnter product price: ");
    scanf("%lf", &pro_price);
    ptr->prePrice = pro_price;

    printf("\t\tEnter product quantity: ");
    scanf("%d", &pro_quant);
    ptr->quantity = pro_quant;

    ptr->prev = NULL;
    ptr->next = NULL;

    if (head == NULL) {
        head = ptr; // If the list is empty, set head to the new node
    } else {
        while (qtr->next != NULL) {
            qtr = qtr->next;
        }
        qtr->next = ptr;
        ptr->prev = qtr;
    }

    root = insertBST(root, id, ptr); // Insert into the BST
    system("cls");
    printf("\n\n\n\n\t\tThis product is Inserted!\n\n\n");
}

void insert_at_end(){
    system("cls");
    int id;
    int pro_quant;
    char pro_name[100];
    double pro_price;
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    struct node *qtr=head;
    printf("\t\t\tEnter product ID:-");
    scanf("%d",&id);
    ptr->ID = id;
    printf("\t\t\tEnter product Name:-");
    scanf("%s",pro_name);
    for(int i=0;i<100;i++){
        ptr->proName[i]=pro_name[i];
    }
    printf("\t\t\tEnter product price:-");
    scanf("%lf",&pro_price);
    ptr->prePrice=pro_price;
    printf("\t\t\tEnter product quantity:-");
    scanf("%d",&pro_quant);
        ptr->quantity=pro_quant;
    while(qtr->next!=NULL){
        qtr=qtr->next;
    }
    qtr->next=ptr;
    ptr->prev=qtr;
    ptr->next=NULL;
    root = insertBST(root, id, ptr); // insert into the BST
    system("cls");
    printf("\n\n\t\t\t\tThis product is Inserted !!\n\n\n");
}

void viewProducts() {
    system("cls");
    int c = 0; // c for count products
    struct node *ptr = head;
    printf("Available products are:\n");
    printf("ID\t\tProduct Name\t\tPrice\t\tQuantity\n");
    while (ptr != NULL) {
        printf("%d\t\t%s\t\t\t%lf\t", ptr->ID, ptr->proName, ptr->prePrice);
        if (check(ptr->quantity) <= 0) {
            printf("OUT OF STOCK!\n");
        } else {
            printf("%d\n", check(ptr->quantity));
        }
        ptr = ptr->next;
        c = c + 1; // product counter
    }
    printf("\nTotal products available: %d\n\n\n", c);
}

void purchaseProduct() {
    system("cls");
    int id, quantity;
    viewProducts();
    printf("Enter the ID of the product you want to purchase (0 to cancel): ");
    scanf("%d", &id);

    if (id == 0) {
        return; // Cancel the purchase
    }

    // Search for the product in the BST
    struct node *product = searchProductByID(root, id);

    if (product != NULL) {
        if (product->quantity > 0) {
            printf("Enter the quantity you want to purchase: ");
            scanf("%d", &quantity);

            if (quantity <= 0 || quantity > product->quantity) {
                printf("Invalid quantity. Please enter a valid quantity.\n");
            } else {
                printf("\n\nYou have successfully purchased %d %s.\n", quantity, product->proName);
                product->quantity -= quantity; // Update the quantity in the linked list
            }
        } else {
            printf("Sorry, the product is out of stock.\n");
        }
    } else {
        printf("Product not found.\n");
    }
}

int main() {
    // Initialize root for the BST
    root = NULL;

    int flag, flag1;

    printf("||||||||||||||||||||||||   SmartCart   ||||||||||||||||||||||||\n");
    printf("////////////////////////     Store     \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");
    printf("\n\n\n");

    int id, pro_quant;
    char pro_name[100];
    double pro_price;
    struct node *ptr;

    while (1) {
        int ch;
        flag = 1;
        flag1 = 1;

        printf("\t\tEnter 1 for Shopkeeper portal \n\n\t\tEnter 2 for Customer portal\n\n\t\tEnter 0 for exit\n\n");
        printf("================================================================ ");
        scanf("%d", &ch); // for user choice

        switch (ch) {
            case 1:
                while (1) {
                    int ch2; // for shopkeeper choice
                    printf("\n\t\tEnter 1 for ADD a new product \n\n\t\tEnter 2 to Display all products \n\n\t\tEnter 3 for Modify Existing product\n\n");
                    printf("\t\tEnter 4 for Delete a particular product item\n\n\t\tEnter 0 for exit\n\n");
                    printf("================================================================ ");
                    scanf("%d", &ch2);

                    switch (ch2) {
                        case 1:
                            create_node();
                            break;

                        case 2:
                            system("cls");
                            display();
                            break;

                        case 3:
                            modify();
                            break;

                        case 4:
                            delete_product();
                            break;

                        case 0:
                            printf("Exiting.......\n");
                            flag1 = 0;
                            break;

                        default:
                            system("cls");
                            printf("\t\t<< invalid input >>\n\n");
                            break;
                    }

                    if (flag1 == 0) {
                        break; // Exit the inner loop
                    }
                }

                if (flag1 == 0) {
                    break; // Exit the outer loop
                }
                break;
                case 2:
                
                while (1) {
                    int ch2; // for customer choice
                    printf("\t\tEnter 1 to View products \n\n\t\tEnter 2 to Purchase a product \n\n\t\tEnter 0 for Exit\n\n");
                    printf("================================================================ ");
                    scanf("%d", &ch2);

                    switch (ch2) {
                        case 1:
                            viewProducts();
                            break;

                        case 2:
                            purchaseProduct();
                            break;

                        case 0:
                            printf("Exiting.......\n");
                            flag1 = 0;
                            break;

                        default:
                            system("cls");
                            printf("\t\t<< invalid input >>\n\n");
                            break;
                    }

                    if (flag1 == 0) {
                        break; // Exit the inner loop
                    }
                }

                if (flag1 == 0) {
                    break; // Exit the outer loop
                }
                break;

            case 0:
                printf("Exiting................\n\n");
                exit(0); // Exit the program
                break;

            default:
                system("cls");
                printf("\t\t<< invalid input >>\n\n");
                break;
        }
    }

    return 0;
}
