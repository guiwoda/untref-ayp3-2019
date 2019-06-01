/**
 * Estructura de un nodo.
 * Cada nodo tiene referencias a los nodos de izquierda y derecha.
 * Además, en árboles AA, cada nodo sabe también su nivel.
 */
typedef struct nodo {
    // Valor del nodo
    int valor;
    // Nivel del nodo en el árbol
    int nivel;
    struct nodo
            // Nodo a la izquierda (menor)
            *izq,
            // Nodo a la derecha (mayor)
            *der;
} Nodo;

/**
 * Estructura de un árbol AA.
 * La raíz del árbol puede cambiar a medida que se opera, al balancear el árbol
 * a través de torsión y división.
 */
typedef struct {
    // Nodo raíz del árbol
    Nodo *raiz;
    // Nodo de ayuda para comparaciones
    Nodo *nullnode;
    // Nodo de ayuda para proceso de eliminación
    Nodo *eliminado;
    // Último nodo del árbol
    Nodo *ultimo;
} Arbol;

/**
 * Constructor de árboles.
 * @return un árbol inicializado.
 */
Arbol *crearArbol();

/**
 * Destructor de árboles.
 * @param arbol el árbol a talar.
 */
void eliminarArbol(Arbol *arbol);

/**
 * Inserta un valor en el árbol.
 * @param arbol dónde insertar el valor
 * @param valor qué valor insertar
 */
void insertar(Arbol *arbol, int valor);

/**
 * Elimina un nodo del árbol por valor.
 * @param arbol dónde eliminar el nodo
 * @param valor qué valor buscar para eliminar
 */
void eliminar(Arbol *arbol, int valor);

/**
 * Busca un elemento en el árbol por valor.
 * @param arbol dónde buscar.
 * @param valor qué valor buscar
 * @return el nodo encontrado o {@code NULL}.
 */
Nodo* buscar(Arbol *arbol, int valor);

/**
 * Recorre el árbol en pre-order, llamando al callback en cada elemento.
 * @param callback la función que llamar en cada elemento.
 */
void preOrder(Arbol *arbol, void (*callback)(Nodo*));

/**
 * Recorre el árbol en in-order, llamando al callback en cada elemento.
 * @param callback la función que llamar en cada elemento.
 */
void inOrder(Arbol *arbol, void (*callback)(Nodo*));

/**
 * Recorre el árbol en post-order, llamando al callback en cada elemento.
 * @param callback la función que llamar en cada elemento.
 */
void postOrder(Arbol *arbol, void (*callback)(Nodo*));
