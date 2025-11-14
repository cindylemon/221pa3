/**
 * @file            threetree.cpp
 * @author          your CWL
 * @description     Implementation of ThreeTree functions
 *
 * THIS FILE WILL BE SUBMITTED
**/

#include "threetree.h"

/**
 * ThreeTree constructor given tolerance for variance.
**/
ThreeTree::ThreeTree(PNG& imIn, double tol) {
    /* Complete your implementation below */
    int width = imIn.width();
    int height = imIn.height();

    Stats s = Stats(imIn);

    root = BuildTree(s, make_pair(0,0), width, height, tol);
}

/**
 * Helper for the ThreeTree constructor.
**/
Node* ThreeTree::BuildTree(Stats& s, pair<int, int> ul, int w, int h, double tol) {
    /* Replace the line below with your implementation */
    Node* node = new Node(s, ul, w, h);

    // If colour variability of a node is at most the tolerance, then we can simply not construct any children for this node
    if (node->var <= tol) {
        node->A = nullptr;
        node->B = nullptr;
        node->C = nullptr;
        return node;
    }

    // splitting horizontally 
    if (h >= w) {
        int heightA = h/3;
        int heightB = h/3;
        int heightC = h - heightA - heightB;
    
        node->A = BuildTree(s, ul, w, heightA, tol);
        node->B = BuildTree(s, make_pair(ul.first, ul.second + heightA), w, heightB, tol);
        node->C = BuildTree(s, make_pair(ul.first, ul.second + heightA + heightB), w, heightC, tol);

    } else { // split vertically

        int widthA = w/3;
        int widthB = w/3;
        int widthC = w - widthA - widthB;
    
        node->A = BuildTree(s, ul, widthA, h, tol);
        node->B = BuildTree(s, make_pair(ul.first + widthA, ul.second), widthB, h, tol);
        node->C = BuildTree(s, make_pair(ul.first + widthA + widthB, ul.second), widthC, h, tol);

    }

    return node;
}

/**
 * Render ThreeTree and return the resulting image.
**/
PNG ThreeTree::Render() const {
    /* Replace the line below with your implementation */
    return PNG();
}

/**
 * Delete allocated memory.
**/
void ThreeTree::Clear() {
    Clear_Helper(root);
}

/**
 * Copy other tree into this tree object.
**/
void ThreeTree::Copy(const ThreeTree& other) {
    /* Complete your implementation below */

    
}

/**
 * Returns the number of nodes in the tree
**/
int ThreeTree::Size() const {
    return Size_Helper(root);
}

/**
 * Returns the number of leaf nodes in the tree
**/
int ThreeTree::NumLeaves() const {
    return NumLeaves_Helper(root);
}

/**
 * Rearranges the tree contents so that when rendered, the image appears
 * to be rotated 90 degrees clockwise.
 * See threetree.h for specification details.
 *
 * You may want a recursive helper function for this.
**/
void ThreeTree::RotateCW() {
    /* Complete your implementation below */

    
}

/*****************************************************************
* IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN sqtree-private.h, *
* ADD YOUR IMPLEMENTATIONS BELOW                                 *
*****************************************************************/

int ThreeTree::Size_Helper(Node* subroot) const {
    if(subroot == nullptr) return 0;

    return 1 + Size_Helper(subroot->A) + Size_Helper(subroot->B) + Size_Helper(subroot->C);
}

int ThreeTree::NumLeaves_Helper(Node* subroot) const {
    if(subroot == nullptr) return 0;
    if(!subroot->A && !subroot->B && !subroot->C) return 1;

    return NumLeaves_Helper(subroot->A) + NumLeaves_Helper(subroot->B) + NumLeaves_Helper(subroot->C);
}

void ThreeTree::Clear_Helper(Node* subroot) {
    if(subroot == nullptr) return;
    Clear_Helper(subroot->A);
    Clear_Helper(subroot->B);
    Clear_Helper(subroot->C);
    delete subroot;
    subroot = nullptr;
}