#include <stdio.h>
#include <stdlib.h>

/*
   tree.c
   Ejemplo simple de árbol binario de búsqueda (BST) en C.
   El código está comentado en español y explica paso a paso las operaciones.
*/

/* 1) Estructura del nodo */
struct Node {
    int key;               // Valor almacenado en el nodo
    struct Node *left;     // Puntero al hijo izquierdo
    struct Node *right;    // Puntero al hijo derecho
};

/* 2) Crear un nuevo nodo (reserva memoria y asigna valores) */
struct Node* create_node(int key) {
    // Reservamos memoria para un nuevo nodo
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Error: memoria insuficiente\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* 3) Insertar una clave en el árbol BST
   - Si el árbol está vacío (root == NULL), creamos y retornamos un nuevo nodo.
   - Si la clave es menor que la del nodo actual, insertamos en el subárbol izquierdo.
   - Si la clave es mayor o igual, insertamos en el subárbol derecho.
   Esta función es recursiva y retorna la (posible) nueva raíz del subárbol.
*/
struct Node* insert(struct Node* root, int key) {
    if (root == NULL) {
        // Caso base: posición encontrada, crear nuevo nodo
        return create_node(key);
    }

    if (key < root->key) {
        // Insertar en el subárbol izquierdo
        root->left = insert(root->left, key);
    } else {
        // Insertar en el subárbol derecho
        root->right = insert(root->right, key);
    }

    // Retornar la raíz sin cambios (esta llamada no rebalancea)
    return root;
}

/* 4) Buscar una clave en el BST (recursivo)
   - Si el nodo actual es NULL, no existe.
   - Si la clave coincide con node->key, la encontramos.
   - Si es menor, buscamos a la izquierda; si es mayor, a la derecha.
*/
struct Node* search(struct Node* root, int key) {
    if (root == NULL) return NULL; // No encontrado
    if (key == root->key) return root; // Encontrado
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

/* 5) Recorridos del árbol (traversals)
   a) Inorder: izquierda, raíz, derecha (para BST: salida ordenada ascendente)
   b) Preorder: raíz, izquierda, derecha
   c) Postorder: izquierda, derecha, raíz (útil para liberar memoria)
*/

void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->right);
    printf("%d ", root->key);
    inorder(root->left);
}

void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

/* 6) Liberar memoria del árbol (postorden) */
void free_tree(struct Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/* 7) Función main: demuestra el uso del BST
   - Crea un árbol vacío
   - Inserta varios valores
   - Muestra los recorridos
   - Busca un par de claves de ejemplo
   - Libera la memoria
*/
int main(void) {
    struct Node* root = NULL; // Empezamos con un árbol vacío

    // Insertar claves de ejemplo. El orden de inserción produce el siguiente árbol:
    //         76
    //        /  \
    //      33    80
    //     /  \  /  \
    //   10  20 50  12

    int keys[] = {76, 33, 80, 10, 20, 50, 12};
    size_t n = sizeof(keys) / sizeof(keys[0]);
    for (size_t i = 0; i < n; ++i) {
        root = insert(root, keys[i]);
    }

    // Mostrar recorridos
    printf("Inorder (orden ascendente): ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    // Buscar un valor existente y uno no existente
    int to_find1 = 10;
    int to_find2 = 25;

    struct Node* found1 = search(root, to_find1);
    if (found1 != NULL) {
        printf("Clave %d encontrada en el árbol.\n", to_find1);
    } else {
        printf("Clave %d NO encontrada en el árbol.\n", to_find1);
    }

    struct Node* found2 = search(root, to_find2);
    if (found2 != NULL) {
        printf("Clave %d encontrada en el árbol.\n", to_find2);
    } else {
        printf("Clave %d NO encontrada en el árbol.\n", to_find2);
    }

    // Liberar memoria
    free_tree(root);
    root = NULL;

    return 0;
}
