#include <stdio.h>
#include <stdlib.h>

// Node to represent a term in the polynomial
typedef struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
} Node;

// Function to create a new node with given coefficient and exponent
Node* createNode(int coeff, int exp) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) 
	{
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->coefficient = coeff;
    newNode->exponent = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a term into the polynomial
void insertTerm(Node** poly, int coeff, int exp) 
{
    Node* newNode = createNode(coeff, exp);
    if (*poly == NULL) 
	{
        *poly = newNode;
    } 
	else 
	{
        Node* current = *poly;
        while (current->next != NULL) 
		{
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to display a polynomial
void displayPolynomial(Node* poly) 
{
    while (poly != NULL) 
	{
        printf("%dx^%d", poly->coefficient, poly->exponent);
        poly = poly->next;
        if (poly != NULL) 
		{
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to add two polynomials
Node* addPolynomials(Node* poly1, Node* poly2) 
{
    Node* result = NULL;
    while (poly1 != NULL || poly2 != NULL) 
	{
        int coeff1 = (poly1 != NULL) ? poly1->coefficient : 0;
        int coeff2 = (poly2 != NULL) ? poly2->coefficient : 0;
        int sumCoeff = coeff1 + coeff2;

        int exp1 = (poly1 != NULL) ? poly1->exponent : 0;
        int exp2 = (poly2 != NULL) ? poly2->exponent : 0;
        int maxExp = (exp1 > exp2) ? exp1 : exp2;

        insertTerm(&result, sumCoeff, maxExp);

        if (poly1 != NULL)
		{
			poly1 = poly1->next;
		}
        if (poly2 != NULL) 
        {
			poly2 = poly2->next;
		}
    }
    return result;
}

// Function to subtract two polynomials
Node* subtractPolynomials(Node* poly1, Node* poly2) 
{
    Node* result = NULL;
    while (poly1 != NULL || poly2 != NULL) 
	{
        int coeff1 = (poly1 != NULL) ? poly1->coefficient : 0;
        int coeff2 = (poly2 != NULL) ? poly2->coefficient : 0;
        int diffCoeff = coeff1 - coeff2;

        int exp1 = (poly1 != NULL) ? poly1->exponent : 0;
        int exp2 = (poly2 != NULL) ? poly2->exponent : 0;
        int maxExp = (exp1 > exp2) ? exp1 : exp2;

        insertTerm(&result, diffCoeff, maxExp);

        if (poly1 != NULL) 
		{
			poly1 = poly1->next;
		}
        if (poly2 != NULL) 
		{
			poly2 = poly2->next;
		}
    }
    return result;
}

// Function to free memory allocated for a polynomial
void freePolynomial(Node* poly) 
{
    Node* current = poly;
    while (current != NULL) 
	{
        Node* nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main() 
{
    Node* poly1 = NULL;
    Node* poly2 = NULL;
    Node* resultAdd = NULL;
    Node* resultSubtract = NULL;
    int coeff, exp, terms;

    printf("Enter details for the first polynomial:\n");
    printf("Enter the number of terms: ");
    scanf("%d", &terms);
    for (int i = 0; i < terms; i++) 
	{
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly1, coeff, exp);
    }

    printf("Enter details for the second polynomial:\n");
    printf("Enter the number of terms: ");
    scanf("%d", &terms);
    for (int i = 0; i < terms; i++) 
	{
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        insertTerm(&poly2, coeff, exp);
    }

    printf("\nFirst Polynomial: ");
    displayPolynomial(poly1);

    printf("\nSecond Polynomial: ");
    displayPolynomial(poly2);

    resultAdd = addPolynomials(poly1, poly2);
    printf("\nResult of Addition:\n");
    displayPolynomial(resultAdd);

    resultSubtract = subtractPolynomials(poly1, poly2);
    printf("\nResult of Subtraction:\n");
    displayPolynomial(resultSubtract);

    // Free allocated memory
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(resultAdd);
    freePolynomial(resultSubtract);

    return 0;
}

