/* treeForm.c for assignment 4 on logical formulas
 *
 * This recognizes and makes syntax trees for the following grammar:
 *
 * <atom>     ::=  'T' | 'F' | <identifier> | '(' <formula> ')'
 * <literal>  ::=  <atom> | '~' <atom>
 * <formula>  ::=  <literal> { '&' <literal> }
 *
 */

#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include <assert.h>

#include "scanner.h"
#include "treeForm.h"

/* The acceptCharacter function takes a pointer to a token list and a character.
 * It checks whether the first token in the list is a Symbol with the given character.
 * When that is the case, it returns 1 and moves the pointer to the rest of the token list.
 * Otherwise it yields 0 and the pointer remains unchanged.
 */

int acceptCharacter(List *lp, char c) {
    if (*lp != NULL && (*lp)->tt == Symbol && ((*lp)->t).symbol == c ) {
        *lp = (*lp)->next;
        return 1;
    }
    return 0;
}

FormTree newFormTreeNode(TokenType tt, Token t, FormTree tL, FormTree tR) {
    FormTree new = malloc(sizeof(FormTreeNode));
    assert (new != NULL);
    new->tt = tt;
    new->t = t;
    new->left = tL;
    new->right = tR;
    return new;
}

void freeTree(FormTree t) {
    if (t == NULL) {
        return;
    }
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}

int treeIdentifier(List *lp, FormTree *t) {
    if (*lp != NULL && (*lp)->tt == Identifier ) {
        *t = newFormTreeNode(Identifier, (*lp)->t, NULL, NULL);
        *lp = (*lp)->next;
        return 1;
    } else if (*lp != NULL && (*lp)->tt != Identifier && (*lp)->tt != Symbol) {
        *lp = (*lp)->next;
        if (*lp != NULL && (*lp)->tt == Identifier ) {
            *t = newFormTreeNode(Identifier, (*lp)->t, NULL, NULL);
            *lp = (*lp)->next;
            return 1;
        }
    }
    return 0;
}

// <atom>  ::=  'T' | 'F' | <identifier> | '(' <biimplication> ')'
int treeAtom(List *lp, FormTree *t) {
    if (acceptCharacter(lp,'T')) {
        Token tok;
        tok.symbol = 'T';
        *t = newFormTreeNode(Symbol, tok, NULL, NULL);
        return 1;
    }
    if (acceptCharacter(lp,'F')) {
        Token tok;
        tok.symbol = 'F';
        *t = newFormTreeNode(Symbol, tok, NULL, NULL);
        return 1;
    }
    if (treeIdentifier(lp,t)) {
        return 1;
    }
    if (acceptCharacter(lp,'(') && biimplication(lp,t) && acceptCharacter(lp,')') ) {
        return 1;
    }
    return 0;
}

// <literal>  ::=  <atom> | '~' <atom>
int treeLiteral(List *lp, FormTree *t) {
    if (treeAtom(lp,t)) {
        return 1;
    }
    if (acceptCharacter(lp,'~')) {
        FormTree tL = NULL;
        if (treeAtom(lp, &tL)) {
            Token tok;
            tok.symbol = '~';
            *t = newFormTreeNode(Symbol, tok, tL, NULL);
            return 1;
        }
        freeTree(tL);
    }
    return 0;
}

// <formula>  ::=  <literal> { '&' <literal> }
int treeFormula(List *lp, FormTree *t) {
    if ( !treeLiteral(lp,t) ) {
        return 0;
    }
    while ( acceptCharacter(lp,'&') ) {
        FormTree tL = *t;
        FormTree tR = NULL;
        if ( !treeLiteral(lp,&tR) ) {
            freeTree(tR);
            return 0;
        }
        Token tok;
        tok.symbol = '&';
        *t = newFormTreeNode(Symbol, tok, tL, tR);
    } /* no '&', so we reached the end of conjunction */
    return 1;
}

// <disjunction>  ::=  <formula> { '|' <formula> }
int treeDisjunction(List *lp, FormTree *t) {
    if ( !treeFormula(lp,t) ) {
        return 0;
    }
    while ( acceptCharacter(lp,'|') ) {
        FormTree tL = *t;
        FormTree tR = NULL;
        if ( !treeFormula(lp,&tR) ) {
            freeTree(tR);
            return 0;
        }
        Token tok;
        tok.symbol = '|';
        *t = newFormTreeNode(Symbol, tok, tL, tR);
    }
    return 1;
}

// <implication>  ::=  <disjuntion> { '->' <disjuntion> }
int implication(List *lp, FormTree *t) {
    if ( !treeDisjunction(lp,t) ) {
        return 0;
    }
    if (acceptCharacter(lp,'-')) {
        if (acceptCharacter(lp, '>')) {
            FormTree tL = *t;
            FormTree tR = NULL;
            if ( !treeDisjunction(lp,&tR) ) {
                freeTree(tR);
                return 0;
            }
            Token tok;
            tok.symbol = '-';
            *t = newFormTreeNode(Symbol, tok, tL, tR);
        } else {
            return 0;
        }
    }
    return 1;
}

// <biimplication>  ::=  <implication> { '<->' <implication> }
int biimplication(List *lp, FormTree *t) {
    if ( !implication(lp,t) ) {
        return 0;
    }
    if ( acceptCharacter(lp,'<')) {
        if ( acceptCharacter(lp, '-') &&  acceptCharacter(lp, '>')) {
            FormTree tL = *t;
            FormTree tR = NULL;
            if ( !implication(lp,&tR) ) {
                freeTree(tR);
                return 0;
            }
            Token tok;
            tok.symbol = '<';
            *t = newFormTreeNode(Symbol, tok, tL, tR);
        } else {
            return 0;
        }
    }
    return 1;
}

// recursive function to find the maximum depth of the tree
int complexityTree(FormTree t) {
    if (t == NULL) {
        return 0;
    } else {
        int left = complexityTree(t->left);
        int right = complexityTree(t->right);
        if (left > right) {
            return (left+1);
        } else {
            return (right+1);
        }
    }
}

void printTree(FormTree t) {
    if (t == NULL) {
        return;
    }
    switch (t->tt) {
        case Symbol:
            switch (t->t.symbol) {
                case 'T':
                case 'F':
                    printf("%c",t->t.symbol);
                    break;
                case '~':
                    printf("(~");
                    printTree(t->left);
                    printf(")");
                    break;
                case '-':
                    printf("(");
                    printTree(t->left);
                    printf(" -> ");
                    printTree(t->right);
                    printf(")");
                    break;
                case '<':
                    printf("(");
                    printTree(t->left);
                    printf(" <-> ");
                    printTree(t->right);
                    printf(")");
                    break;
                default:
                    printf("(");
                    printTree(t->left);
                    printf(" %c ",t->t.symbol);
                    printTree(t->right);
                    printf(")");
                    break;
            }
            break;
        case Identifier:
            printf("%s", t->t.identifier);
            break;
    }
}

void simplify(FormTree t) {
    if (t == NULL) {
        return;
    }
    switch (t->tt) {
        case Symbol:
            switch (t->t.symbol) {
                case 'T':
                case 'F':
                    break;
                case '~':
                    simplify(t->left);
                    if ((t->left)->tt == Symbol) {
                        if ((t->left)->t.symbol == 'T') {
                            t->t.symbol = 'F';
                        } else if ((t->left)->t.symbol == 'F') {
                            t->t.symbol = 'T';
                        } else if ((t->left)->t.symbol == '~' && ((t->left)->left)->tt == Identifier) {
                            t->tt = Identifier;
                            t->t.identifier = ((t->left)->left)->t.identifier;
                        }
                    }
                    break;
                case '&':
                    simplify(t->left);
                    simplify(t->right);
                    if ((t->left)->tt == Symbol && (t->right)->tt == Identifier) {
                        if ((t->left)->t.symbol == 'T') {
                            t->tt = Identifier;
                            t->t.identifier = (t->right)->t.identifier;
                        } else if ((t->left)->t.symbol == 'F') {
                            t->t.symbol = 'F';
                        }
                    } else if ((t->left)->tt == Identifier && (t->right)->tt == Symbol) {
                       if ((t->right)->t.symbol == 'T') {
                            t->tt = Identifier;
                            t->t.identifier = (t->left)->t.identifier;
                        } else if ((t->right)->t.symbol == 'F') {
                            t->t.symbol = 'F';
                        }
                    }
                    break;
                case '|':
                    simplify(t->left);
                    simplify(t->right);
                    if ((t->left)->tt == Symbol && (t->right)->tt == Identifier) {
                        if ((t->left)->t.symbol == 'T') {
                            t->t.symbol = 'T';
                        } else if ((t->left)->t.symbol == 'F') {
                            t->tt = Identifier;
                            t->t.identifier = (t->right)->t.identifier;
                        }
                    } else if ((t->left)->tt == Identifier && (t->right)->tt == Symbol) {
                       if ((t->right)->t.symbol == 'T') {
                            t->t.symbol = 'T';
                        } else if ((t->right)->t.symbol == 'F') {
                            t->tt = Identifier;
                            t->t.identifier = (t->left)->t.identifier;
                        }
                    }
                    break;
                case '-':
                    simplify(t->left);
                    simplify(t->right);
                    if ((t->left)->tt == Symbol && (t->right)->tt == Identifier) {
                        if ((t->left)->t.symbol == 'T') {
                            t->tt = Identifier;
                            t->t.identifier = (t->right)->t.identifier;
                        } else if ((t->left)->t.symbol == 'F') {
                            t->t.symbol = 'T';
                        }
                    } else if ((t->left)->tt == Identifier && (t->right)->tt == Symbol) {
                       if ((t->right)->t.symbol == 'T') {
                            t->t.symbol = 'T';
                        } else if ((t->right)->t.symbol == 'F') {
                            t->t.symbol = '~';
                        }
                    }
                    break;
                case '<':
                    simplify(t->left);
                    simplify(t->right);
                    if ((t->left)->tt == Symbol && (t->right)->tt == Identifier) {
                        if ((t->left)->t.symbol == 'T') {
                            t->tt = Identifier;
                            t->t.identifier = (t->right)->t.identifier;
                        } else if ((t->left)->t.symbol == 'F') {
                            t->t.symbol = '~';
                            (t->left)->tt = Identifier;
                            (t->left)->t.identifier = (t->right)->t.identifier;
                        }
                    } else if ((t->left)->tt == Identifier && (t->right)->tt == Symbol) {
                       if ((t->right)->t.symbol == 'T') {
                            t->tt = Identifier;
                            t->t.identifier = (t->left)->t.identifier;
                        } else if ((t->right)->t.symbol == 'F') {
                            t->t.symbol = '~';
                        }
                    }
                    break;
                default:
                    break;
            }
            break;
        case Identifier:
            break;
    }
}
