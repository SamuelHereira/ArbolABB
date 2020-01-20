#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int value;
	struct Node * left;
	struct Node * right;
} TREE;

/* 
 Crea e inserta los nodos en el arbol
*/
TREE* createNode( int value ) 
{
	TREE *tree;
	tree = malloc( sizeof( TREE ) );
	tree->value = value;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
} 

void insertNode( TREE ** tree, int value ) 
{
	if( *tree == NULL ) {
		*tree = createNode( value );
	} else {
		if ( value < (*tree)->value ) {
			insertNode( &(*tree)->left, value );
		} else if(value > (*tree)->value ) {
			insertNode( &(*tree)->right, value );
		}
	}
}

/* 
 Retorna la altura del arbol
*/

int treeHeight( const TREE * tree ) 
{
	if( tree == NULL ) {
		return 0;
	} else {
		int leftHeight = treeHeight( tree->left );
		int rightHeight = treeHeight( tree->right );
		if( leftHeight > rightHeight ) 
			return ++leftHeight;
		else 
			return ++rightHeight;
	}
}

/* 
int haveChildrens( const TREE * tree, int value ) {
	if( tree == NULL ) {
		return 0;
	} else {
		if( value == tree->value ) {
			if(  )
		}
	}
}
*/
int isLeaf( const TREE * tree, int value ) {
	if( tree == NULL ) {
		printf("Arbol vacio\n");
	} else {
		if( value == tree->value ) {
			if( tree->left == NULL && tree->right == NULL) {
				return 1;
			} else {
				return 0;
			}
		} else if( value < tree->value ) {
			if( tree->left != NULL ) {
				return isLeaf( tree->left, value );
			} else {
				printf("Nodo inexistente: %d\n", value);
				return 0;
			}	
		} else {
			if( tree->right != NULL ) {
				return isLeaf( tree->right, value );
			} else {
				printf("Nodo inexistente: %d\n", value);
				return 0;
			}
		}
	}
}

TREE * findFather( TREE * tree, int value ) 
{
	
	if( ( tree->left && tree->left->value == value ) || tree->right && tree->right->value == value )  {
		return tree;
	} else {
		if( value < tree->value ) {
			findFather( tree->left, value );
		} else if( value > tree->value ) {
			findFather( tree->right, value );
		}
	}
}


TREE * findNode( TREE * tree, int value ) {

	if( tree->value == value ) {
		return tree;
	} else {
		if( value < tree->value ) {
			findNode( tree->left, value );
		} else if(value > tree->value) {
			findNode( tree->right, value );
		}
	}

}

int isLeafaNode( TREE * tree ) {
	if( tree->left == NULL && tree->right == NULL) {
		return 1;
	} else {
		return 0;
	}
}

TREE * findSuccessor( TREE * RightSubTree ) {

	if( RightSubTree->left == NULL ) {
		return RightSubTree;
	} else {
		return findSuccessor( RightSubTree->left );
	}
}

TREE * findPredecessor( TREE * leftSubTree ) {

	if( leftSubTree->right == NULL ) {
		return leftSubTree;
	} else {
		return findPredecessor( leftSubTree->right );
	}
}




void replaceNode( TREE * node, TREE * secondNode )
{
	if( node->value > secondNode->value ) {
		secondNode->right = node->right;
		if( node->left && node->left == secondNode ) {
			if( isLeafaNode(secondNode) ) {
				secondNode->left = NULL;
			} 
			
		} else {
			
			secondNode->left = node->left;
		}

	} else {
		
		secondNode->left = node->left;

		if( node->right && node->right == secondNode ) {
			if( isLeafaNode(secondNode) ) {
				secondNode->right = NULL;
			} 
					
		} else {

			secondNode->right = node->right;
		}
	}


	

	*node = *secondNode;
	
}

/*
	ELIMINAR NODO
*/

void deleteNode( TREE ** tree, int value )
{
	if( *tree == NULL ) {
		printf("ARBOL VACIO\n");
	} else {
		if( (*tree)->value	== value ) {
			
			if( isLeafaNode(*tree) ) {
				*tree = NULL;
			} else {
				TREE * successor = findSuccessor( (*tree)->right );
				TREE * successorFather = findFather( *tree, successor->value );
				if( successor->value != (*tree)->right->value ) {
					successorFather->left = successor->right;
				}
				replaceNode( *tree, successor );
			}

			
			
			
			
		} else {

			TREE * node = findNode( *tree, value );
			printf("encontre nodo: %d\n", node->value);
			TREE * nodeFather = findFather( *tree, node->value );
			printf("si encontre padre: %d\n", nodeFather->value);
			
			if ( isLeaf( *tree, node->value ) ) {
				if ( nodeFather->left && nodeFather->left->value == node->value ) {
					nodeFather->left = NULL;
				} else if ( nodeFather->right && nodeFather->right->value == node->value ) {
					nodeFather->right = NULL;
				}
			} else {
				TREE * replacement;
				if ( node->right ) {
					replacement = findSuccessor( node->right );
				} else {
					replacement = findPredecessor( node->left );
				}
				printf("el reemplazo: %d\n", replacement->value );
				replaceNode( node, replacement );
			}
			
			
			//TREE * successor = findSuccessor( node );
			//TREE * successorFather = findFather( *tree, successor );

			//printf("NODO: %d\nPADRE NODO: %d\nSUCESOR: %d\nPADRE SUCESOR: %d", node->value, nodeFather->value, successor->value, successorFather->value );



		}
	}
}



/* 
	BUSCAR NODO
*/

int searchNode( const TREE * tree, int value )
{
	if( tree == NULL ) {
		printf("Arbol vacio\n");
	} else {
		if( value == tree->value ) {
			printf("Nodo encontrado: %d\n", tree->value);
			return 1;
		} else if( value < tree->value ) {
			if( tree->left != NULL ) {
				return searchNode( tree->left, value );
			} else {
				printf("Nodo inexistente: %d\n", value);
				return 0;
			}	
		} else {
			if( tree->right != NULL ) {
				return searchNode( tree->right, value );
			} else {
				printf("Nodo inexistente: %d\n", value);
				return 0;
			}
		}
	}
}


/*
	RECORRIDOS
*/
void preOrder( const TREE * tree ) 
{
	if( tree == NULL) {
		printf("");
	} else {
		printf("%d ", tree->value );
		preOrder( tree->left );
		preOrder( tree->right );
	}
}

void inOrder( const TREE * tree ) 
{
	if( tree == NULL) {
		printf("");
	} else {
		inOrder( tree->left );
		printf("%d ", tree->value );
		inOrder( tree->right );
	}
} 


void postOrder( const TREE * tree ) 
{
	if( tree == NULL) {
		printf("");
	} else {
		postOrder( tree->left );
		postOrder( tree->right );
		printf("%d ", tree->value );
		
	}
}

/*
	MAIN
*/

int main()
{
	TREE * tree = NULL;
	insertNode( &tree , 44 );
	insertNode( &tree , 47 );
	insertNode( &tree , 49 );
	insertNode( &tree , 54 );
	insertNode( &tree , 65 );
	insertNode( &tree , 67 );
	insertNode( &tree , 98 );
	
	

	preOrder( tree );
	printf("\n");
	inOrder ( tree );
	printf("\n");
	postOrder ( tree );
	printf("\n");
	
	printf( "La altura del arbol es: %d\n", treeHeight( tree ) );
	
	printf("\neliminando 54\n");
	deleteNode( &tree, 54 );
	inOrder ( tree );
	printf("\n");
	
	printf("\neliminando 49\n");
	deleteNode( &tree, 49 );
	inOrder ( tree );
	printf("\n");

	printf("\neliminando 44\n");
	deleteNode( &tree, 44 );
	inOrder ( tree );
	printf("\n");

	printf("\neliminando 47\n");
	deleteNode( &tree, 47 );
	inOrder ( tree );
	printf("\n");

	printf("\neliminando 67\n");
	deleteNode( &tree, 67 );
	inOrder ( tree );
	printf("\n");

	printf("\neliminando 98\n");
	deleteNode( &tree, 98 );
	inOrder ( tree );
	printf("\n");

	printf("\neliminando 65\n");
	deleteNode( &tree, 65 );
	inOrder ( tree );
	printf("\n");

	printf("\neliminando 65\n");
	deleteNode( &tree, 65 );
	inOrder ( tree );
	printf("\n");

	return 0;

}
